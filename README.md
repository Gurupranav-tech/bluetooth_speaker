# ESP32 Bluetooth Audio Receiver with OLED Display
![GitHub Created At](https://img.shields.io/github/created-at/Gurupranav-tech/bluetooth_speaker)
![GitHub contributors](https://img.shields.io/github/contributors/Gurupranav-tech/bluetooth_speaker)
![GitHub License](https://img.shields.io/github/license/Gurupranav-tech/bluetooth_speaker)

This project demonstrates how to use an ESP32 as a Bluetooth A2DP sink to receive audio, output it via I2S, and display song metadata (title and artist) on an OLED screen.

## Features

- Bluetooth A2DP sink for streaming audio.
- I2S output for audio playback.
- OLED display (128x64) showing the current song title and artist name.
- Scrolling text functionality for long metadata entries.

## Components Used

1. **ESP32**
2. **OLED Display** (SSD1306, 128x64 resolution, SPI interface)
3. **I2S-Compatible Audio Output Device** (e.g., DAC or amplifier)
4. **Speaker**

## Libraries Required

Ensure the following libraries are installed in your Arduino IDE or PlatformIO environment:

- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
- [ESP32 Arduino I2S](https://github.com/espressif/arduino-esp32)
- [ESP32 A2DP Library](https://github.com/pschatzmann/ESP32-A2DP)

## Pin Configuration

### OLED Display (SSD1306)

| Signal     | Pin on ESP32 |
| ---------- | ------------ |
| MOSI (DIN) | GPIO 23      |
| CLK (SCK)  | GPIO 18      |
| DC         | GPIO 15      |
| CS         | GPIO 4       |
| RESET      | GPIO 19      |

### I2S Audio Output

| Signal           | Pin on ESP32 |
| ---------------- | ------------ |
| Bit Clock (SCK)  | GPIO 5       |
| Word Select (WS) | GPIO 25      |
| Serial Data Out  | GPIO 26      |

## Setup Instructions

1. **Hardware Connections**:

   - Connect the OLED display to the ESP32 using the specified pins.
   - Wire the I2S output to a DAC or amplifier connected to your speaker.

2. **Software Setup**:

   - Install the required libraries in your development environment.
   - Clone this repository and open the `.ino` file.
   - Upload the code to your ESP32.

3. **Bluetooth Pairing**:
   - Power on the ESP32.
   - Search for a Bluetooth device named `MyMusic` on your phone or other devices.
   - Pair and start playing audio. The metadata should appear on the OLED screen.

## Code Structure

### Main Components

- **OLED Initialization**: The OLED is set up with SPI communication and displays the song title and artist name.
- **I2S Configuration**: Configures the I2S interface for stereo audio output.
- **Bluetooth A2DP Sink**: Handles Bluetooth connection and retrieves metadata.
- **Scrollable Text**: Implements scrolling for long text entries to fit the display.

### Metadata Callback

The `avrc_metadata_callback` function processes song metadata:

- Updates the song title and artist name.
- Allocates memory dynamically to store the metadata.

### Display Logic

The `loop` function:

- Clears the display.
- Renders the song title and artist name with scrolling text support.
- Refreshes the display every 100ms.

## Future Enhancements

- Add album art or playback progress visualization on the OLED screen.
- Support additional metadata fields like album name or playback duration.
- Optimize memory usage and scrolling performance.

## Troubleshooting

- **OLED Not Displaying**:

  - Check connections and ensure the SSD1306 library is properly installed.
  - Verify SPI pin configurations.

- **No Audio Output**:

  - Ensure the I2S pins are connected to a compatible DAC or amplifier.
  - Check the Bluetooth connection.

- **Metadata Not Updating**:
  - Confirm that the audio source supports AVRCP metadata.
