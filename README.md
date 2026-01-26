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

- **Buttons**: The buttons are connected to pins 4 to 13. These are configured as `INPUT_PULLUP`, so ensure you use the internal pull-up resistors.
- **TM1637 Display**: The display uses pins 2 (CLK) and 3 (DIO).
- **Relay**: The main relay is connected to pin A0 and the second emergency relay is connected to pin A1.

## Code Explanation

### Constants and Pin Definitions

- `buttonPins[]`: Array defining the pins connected to the pushbuttons.
- `mainCode[]`: The correct 4-digit code that must be entered to trigger the relay A0.
- `emergencyCode[]`: The correct 4-digit code that must be entered to trigger the relay A1.
- `mainLockRelayPin`: Pin connected to the main relay.
- `emergencyLockRelayPin`: Pin connected to the emergency relay.
- `timesToFlashOnWrongCode`: The number of times the wrong code will flash on the display if entered incorrectly.
- `delayOnFlash`: The delay between flashing the wrong code.
- `maxWrongAttempts`: The maximum wrong code can be entered after which the system locks.
- `lockoutTime`: The duration in milliseconds for which the system locks and no longer accepts input.
- `wrongAttempts`: Counter to keep track of the wrong attempts.
- `isLocked`: Flag to know if the system is locked or not

### `setup()`

- Sets up the button pins as inputs with internal pull-up resistors.
- Sets up A0 and A1 as output pints for the relays and sets them to LOW (off)
- Initializes the TM1637 display and sets its brightness.
- Clears the display initially.

### `loop()`

- Checks if the system is locked and displays a countdown timer if so. When the timer reaches 0 the system is unlocked.
- Monitors the buttons for presses (even when the system is locked).
- When a button is pressed, it stores the corresponding digit and displays the entered digit.
- Once 4 digits are entered, it checks if the entered code matches the main code or the emergency code.
  - If the code matches the main code the main relay is triggered (if the system is not locked).
  - If the code matches the emergency code the emergency relay is triggered and the system is unlocked (even when the system is locked).
  - If the code does not match (and the system is not locked), the wrong code flashes on the display multiple times and the wrong attempt counter is incremented.
- After the check, the entered code is cleared, and the system is ready for the next attempt.

### `getEnteredCode()`

- Converts the entered code array into a single integer for display and comparison purposes.

### `flashDisplay()`

- Flashes the wrong code on the display multiple times to notify the user of an incorrect entry.

### `triggerMainLockRelay()`

- Activates the main relay for 0.5 seconds, simulating the unlocking of a device.

### `triggerEmergencyLockRelay()`

- Activates the emergency relay for 0.5 seconds, simulating the unlocking of a device.

### `checkCode(const int *codeToCheck)`

- Compares the entered code with the predefined correct code and returns `true` if they match, otherwise `false`.

### `lockSystem()`

- Flags the system as locked and starts to show a countdown timer.
- The emergency code can still be entered to unlock the system.

### `unlockSystem()`

- Flags the system as unlocked so input can be given again.

## Wiring Diagram

1. **Buttons**: Connect each button to the respective pin (from 4 to 13) and ground.
2. **TM1637 Display**: Connect the CLK and DIO pins to pins 2 and 3 on the Arduino.
3. **Main Relay**: Connect the main relay control pin to pin A0 on the Arduino.
4. **Emergency Relay**: Connect the emergency relay control pin to pin A1 on the Arduino.

![Connection schema](https://github.com/Jerry911/arduinoSafeController/blob/main/Pinout/Sketch.png)

![Buttons example](https://raw.githubusercontent.com/Jerry911/arduinoSafeController/refs/heads/main/Pinout/IMG20260115154511.jpg)

![Operation example](https://github.com/Jerry911/arduinoSafeController/blob/bf7f693cd85926087363f9f141bec9fbba1f759e/Pinout/example.gif)

## How to Use

1. **Upload the Code**: Upload the code to your Arduino board using the Arduino IDE.
2. **Enter Code**: Press the buttons corresponding to the digits of the code. For example, pressing button 5 will enter the digit `5`.
3. **Trigger Main Relay**: If you enter the correct 4-digit code (`0, 0, 0, 0` in this example), the main relay will be activated for 0.5 seconds.
4. **Trigger Emergency Relay**: If you enter the correct 4-digit code (`1, 1, 1, 1` in this example), the emergency relay will be activated for 0.5 seconds.
5. **Wrong Code**: If you enter an incorrect code, the display will flash the incorrect code several times.
6. **Reset**: After a correct or incorrect entry, the system resets, and you can enter a new code.
7. **Lock**: After X wrong attempts the system will lock up and display a countdown timer.
8. **Unlock**: Wait for the countdown timer to finish or enter the emergency code.

## Customization

- **Change the Correct Code**: Modify the `mainCode[]` array to set your desired 4-digit code.
- **Change the Emegerency Code**: Modify the `emergencyCode[]` array to set your desired 4-digit code.
- **Adjust Relay Time**: You can change the time the relay stays on by modifying the `relayTimeToKeepOn` variable.
- **Button Configuration**: You can modify the `buttonPins[]` array if you want to use different pins for the buttons.
- **Display Settings**: Adjust the brightness of the TM1637 display using the `displayBrightness` variable.
- **Adjust Maximum Wrong Attempts**: Adjust the maximum wrong attempts before the system locks by changing the `maxWrongAttempts` variable.
- **Adjust System Lock Time**: Adjust the time the system locks by changing the `lockoutTime` variable.

## Troubleshooting

- **Buttons Not Responding**: Ensure that the buttons are wired correctly and that the internal pull-up resistors are enabled by using `INPUT_PULLUP`.
- **Display Issues**: Verify that the CLK and DIO pins are correctly connected to the TM1637 display.
- **Relay Not Triggering**: Ensure the relay is wired correctly to the relay control pin and that it is compatible with your external device.
- **Compilation error: TM1637Display.h: No such file or directory**:
This error means the TM1637 display library is not installed (or not found) in your Arduino environment.
Fix: Install the TM1637Display library
Method 1: Arduino Library Manager (recommended)
Open Arduino IDE
Go to Sketch → Include Library → Manage Libraries…
In the search box, type TM1637
Install “TM1637Display” by Avishay Orpaz
Restart the Arduino IDE
Compile again.

## License

This project is open-source and available under the [GNU General Public License v3.0](LICENSE).

---

For more detailed instructions and further modifications, feel free to explore the code and adapt it to your own needs!
