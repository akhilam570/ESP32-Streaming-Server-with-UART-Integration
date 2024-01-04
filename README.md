# ESP32 Streaming Server with UART Integration

This project implements an ESP32-based MJPEG streaming server using the ESPAsyncWebServer library for AI-Thinker ESP32-CAM and ESP-EYE modules. Additionally, UART communication is used for data exchange.

## Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/software)
- ESP32 board support for Arduino ([installation guide](https://github.com/espressif/arduino-esp32))
- Required Arduino libraries: `ESPAsyncWebServer`, `ESPAsyncTCP`, `WiFi`, and `CameraWebServer`

## Installation

1. Open Arduino IDE.
2. Install the required libraries using the Library Manager.
3. Set up the ESP32 board support.

## Configuration

- Update Wi-Fi credentials (`ssid` and `password`) in the `setup` function.
- Update Blynk token (`blynkToken`) in the `initBlynk` function.
- Adjust UART pins (`uartRxPin` and `uartTxPin`) according to your ESP32 board.
- Customize camera configuration in the `initCamera` function.

## Usage

1. Connect ESP32 to Wi-Fi.
2. Upload the code to your ESP32 board.
3. Open the Serial Monitor to view debug information.
4. Access the MJPEG stream at `http://<ESP32_IP>/stream` in a web browser.
5. Use Blynk app for additional functionality.

## UART Communication

- Connect the ESP32 UART TX pin to the RX pin of the device you want to communicate with.
- Connect the ESP32 UART RX pin to the TX pin of the device.
- Adjust UART settings in the `initUART` function.

## Acknowledgments

- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [ESP32 CameraWebServer example](https://github.com/espressif/esp32-camera)
