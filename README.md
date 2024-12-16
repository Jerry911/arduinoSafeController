# Arduino Code for Simple Keypad Lock with TM1637 Display and Relay Control

## Overview

This Arduino sketch allows you to create a simple keypad lock system. The system consists of several pushbuttons, a TM1637 7-segment display to show the entered code, and a relay to trigger a device (such as a door lock or any other electrical appliance). The user is required to enter a 4-digit code by pressing the buttons, and if the correct code is entered, the relay will be triggered for a short period (0.5 seconds). If the wrong code is entered, the display will flash the incorrect code several times.

## Features

- **9 Buttons for Input**: The system uses 9 buttons to input digits for the code.
- **TM1637 Display**: A 4-digit 7-segment display is used to show the entered code.
- **Relay Control**: A relay is triggered if the correct code is entered, allowing you to control an external device (like a door lock).
- **Wrong Code Handling**: The system flashes the wrong code on the display if an incorrect code is entered multiple times.
- **Debounce Handling**: A debounce mechanism ensures accurate button presses.

## Components Required

- **Arduino Board** (e.g., Arduino Uno)
- **TM1637 4-Digit Display**
- **9 Pushbuttons**
- **Relay Module**
- **Jumper Wires**
- **Breadboard**

## Pin Configuration

- **Buttons**: The buttons are connected to pins 4 to 12. These are configured as `INPUT_PULLUP`, so ensure you use the internal pull-up resistors.
- **TM1637 Display**: The display uses pins 2 (CLK) and 3 (DIO).
- **Relay**: The relay is connected to pin 13.

## Code Explanation

### Constants and Pin Definitions

- `buttonPins[]`: Array defining the pins connected to the pushbuttons.
- `correctCode[]`: The correct 4-digit code that must be entered to trigger the relay.
- `relayPin`: Pin connected to the relay.
- `timesToFlashOnWrongCode`: The number of times the wrong code will flash on the display if entered incorrectly.
- `delayOnFlash`: The delay between flashing the wrong code.

### `setup()`

- Sets up the button pins as inputs with internal pull-up resistors.
- Initializes the TM1637 display and sets its brightness.
- Clears the display initially.

### `loop()`

- Monitors the buttons for presses.
- When a button is pressed, it stores the corresponding digit and displays the entered digit.
- Once 4 digits are entered, it checks if the entered code matches the correct code.
  - If the code matches, the relay is triggered.
  - If the code does not match, the wrong code flashes on the display multiple times.
- After the check, the entered code is cleared, and the system is ready for the next attempt.

### `getEnteredCode()`

- Converts the entered code array into a single integer for display and comparison purposes.

### `flashDisplay()`

- Flashes the wrong code on the display multiple times to notify the user of an incorrect entry.

### `triggerRelay()`

- Activates the relay for 0.5 seconds, simulating the unlocking of a device.

### `checkCode()`

- Compares the entered code with the predefined correct code and returns `true` if they match, otherwise `false`.

## Wiring Diagram

1. **Buttons**: Connect each button to the respective pin (from 4 to 12) and ground.
2. **TM1637 Display**: Connect the CLK and DIO pins to pins 2 and 3 on the Arduino.
3. **Relay**: Connect the relay control pin to pin 13 on the Arduino.

## How to Use

1. **Upload the Code**: Upload the code to your Arduino board using the Arduino IDE.
2. **Enter Code**: Press the buttons corresponding to the digits of the code. For example, pressing button 5 will enter the digit `5`.
3. **Trigger Relay**: If you enter the correct 4-digit code (`0, 0, 0, 0` in this example), the relay will be activated for 0.5 seconds.
4. **Wrong Code**: If you enter an incorrect code, the display will flash the incorrect code several times.
5. **Reset**: After a correct or incorrect entry, the system resets, and you can enter a new code.

## Customization

- **Change the Correct Code**: Modify the `correctCode[]` array to set your desired 4-digit code.
- **Adjust Relay Time**: You can change the time the relay stays on by modifying the `relayTimeToKeepOn` variable.
- **Button Configuration**: You can modify the `buttonPins[]` array if you want to use different pins for the buttons.
- **Display Settings**: Adjust the brightness of the TM1637 display using the `display.setBrightness()` function.

## Troubleshooting

- **Buttons Not Responding**: Ensure that the buttons are wired correctly and that the internal pull-up resistors are enabled by using `INPUT_PULLUP`.
- **Display Issues**: Verify that the CLK and DIO pins are correctly connected to the TM1637 display.
- **Relay Not Triggering**: Ensure the relay is wired correctly to the relay control pin and that it is compatible with your external device.

## License

This project is open-source and available under the [GNU General Public License v3.0](LICENSE).

---

For more detailed instructions and further modifications, feel free to explore the code and adapt it to your own needs!
