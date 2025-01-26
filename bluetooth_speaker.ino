#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI 23
#define OLED_CLK 18
#define OLED_DC 15
#define OLED_CS 4
#define OLED_RESET 19
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#include "ESP_I2S.h"
#include "BluetoothA2DPSink.h"
#include "ScrollableText.h"

const uint8_t I2S_SCK = 5;    /* Audio data bit clock */
const uint8_t I2S_WS = 25;    /* Audio data left and right clock */
const uint8_t I2S_SDOUT = 26; /* ESP32 audio data output (to speakers) */
I2SClass i2s;

BluetoothA2DPSink a2dp_sink(i2s);

// Global Song stats
char* song_name = nullptr;
char* artist_name = nullptr;
ScrollableText scrollable_song_name{ &song_name, 15, 8 };
ScrollableText scrollable_artist_name{ &artist_name, 35, 4 };

void setup() {
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println("SSD1306 Allocation Failed");
    for (;;)
      ;
  }

  Serial.println("Oled Display initialized successfully");

  display.setTextWrap(false);

  display.display();
  delay(500);
  display.clearDisplay();

  i2s.setPins(I2S_SCK, I2S_WS, I2S_SDOUT);
  if (!i2s.begin(I2S_MODE_STD, 44100, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO, I2S_STD_SLOT_BOTH)) {
    Serial.println("Failed to initialize I2S!");
    while (1)
      ;
  }
  a2dp_sink.set_avrc_metadata_attribute_mask(ESP_AVRC_MD_ATTR_TITLE | ESP_AVRC_MD_ATTR_ARTIST | ESP_AVRC_MD_ATTR_ALBUM | ESP_AVRC_MD_ATTR_PLAYING_TIME);
  a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
  a2dp_sink.start("MyMusic");
}

void avrc_metadata_callback(uint8_t id, const uint8_t* text) {
  if (id == ESP_AVRC_MD_ATTR_TITLE) {
    if (song_name) free(song_name);
    char* _song_name = (char*)text;
    song_name = (char*)malloc((strlen(_song_name) + 1) * sizeof(char));
    strcpy(song_name, _song_name);
    song_name[strlen(_song_name)] = '\0';
  }
  if (id == ESP_AVRC_MD_ATTR_ARTIST) {
    if (artist_name) free(artist_name);
    char* _artist_name = (char*)text;
    artist_name = (char*)malloc((strlen(_artist_name) + 1) * sizeof(char));
    strcpy(artist_name, _artist_name);
    artist_name[strlen(_artist_name)] = '\0';
  }
}

void loop() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  scrollable_song_name.render(display);
  display.setTextSize(1);
  scrollable_artist_name.render(display);

  display.display();
  delay(100);
}