# ESPNOW-Communication

This project demonstrates the use of ESP-NOW protocol on the ESP8266 microcontroller. Two ESP8266 boards communicate wirelessly, where one acts as a controller to send commands based on button presses, and the other responds by controlling motors or LEDs.

## Features
- Send directional commands (`F`, `B`, `L`, `R`) to control motors using buttons.
- Implements real-time communication using ESP-NOW.
- Handles multiple buttons on GPIO pins.

## Components
- **ESP8266 modules**
- **Buttons** connected to various GPIO pins.
- **Motors/LEDs** controlled based on the received command.

## Usage

1. **Transmitter**: Upload the code in `code 2` to the ESP8266 that will act as a remote control.
2. **Receiver**: Upload the code in `code 1` to the ESP8266 that controls motors or LEDs.
3. Press buttons on the transmitter to send commands wirelessly via ESP-NOW.

## Wiring

### Transmitter
Connect buttons to the following GPIOs:
- GPIO16, GPIO5, GPIO4, GPIO0, GPIO2, GPIO14, GPIO12, GPIO13

### Receiver
Control motors/LEDs on the following GPIOs:
- GPIO5 (left forward), GPIO4 (left back), GPIO14 (right forward), GPIO16 (right back)
