// Include the libraries
#include <TM1637Display.h>

// Define the connections pins
const int buttonPins[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13}; // Pins connected to buttons
const int numButtons = 9; // The amount of buttons
const int debounceDelay = 50; // 50 ms debounce delay

// Correct sequence
const int mainCode[] = {0, 0, 0, 0};
const int emergencyCode[] = {1, 1, 1, 1};
const int codeLength = sizeof(mainCode) / sizeof(mainCode[0]);
int enteredCode[codeLength]; // Array to store entered code
int enteredIndex = 0; // Tracks the number of digits entered

// Relay settings
const int mainLockRelayPin = A0;
const int emergencyLockRelayPin = A1;
int relayTimeToKeepOn = 500; // Keep the relay on for 0.5 second

// Display connection pins
#define CLK 2
#define DIO 3
TM1637Display display(CLK, DIO); // Create an instance of the TM1637Display

// Additional Settings
int timesToFlashOnWrongCode = 3; // When wrong code is entered, flash it on the display
int delayOnFlash = 500; // Delay between clearing the display and showing the wrong code

void setup() {
  // Initialize button pins
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP); // Enable internal pull-up resistors
  }

  pinMode(mainLockRelayPin, OUTPUT);
  pinMode(emergencyLockRelayPin, OUTPUT);
  digitalWrite(mainLockRelayPin, LOW);
  digitalWrite(emergencyLockRelayPin, LOW);

  display.setBrightness(7);  // Set the display brightness (0-7)
  display.clear(); // Clear the display

  // Clear the enteredCode array
  for (int i = 0; i < codeLength; i++) {
    enteredCode[i] = 0;
  }
  
  delay(1000); // Add a delay to allow all pins to stabilize
};


void loop() {
  // Check for button presses
  for (int i = 0; i < numButtons; i++) {
    if (digitalRead(buttonPins[i]) == LOW) { // Button pressed
      delay(debounceDelay); // Debounce delay
      if (digitalRead(buttonPins[i]) == LOW) {
        while (digitalRead(buttonPins[i]) == LOW); // Wait for release
        enteredCode[enteredIndex] = i;
        enteredIndex++;
        //Print the entered code on the display
        display.showNumberDec(enteredCode[enteredIndex - 1], true, 1, enteredIndex-1);
      }
    }
  }

  // Check if 4 digits have been entered
  if (enteredIndex == codeLength) {
    if (checkCode(mainCode)) {
      triggerMainLockRelay();
      delay(5000);
    }
    else if (checkCode(emergencyCode)) {
      triggerEmergencyLockRelay();
      delay(5000);
    }else{
      flashDisplay();
    }

    // Reset for the next attempt
    enteredIndex = 0;
    display.clear();
  }
}

// Get the value of the enteredCode array as one integer e.g. 0000
int getEnteredCode(){
  int code = 0;
  for (int i = 0; i < codeLength; i++) {
    code = code * 10 + enteredCode[i]; // Shift left and add current digit
  }
  
  return code;
}

// Flash the entered number x amount of times
void flashDisplay(){
  int code = getEnteredCode();

  for(int j = 0; j<timesToFlashOnWrongCode; j++){
      delay(delayOnFlash);
      display.clear();
      delay(delayOnFlash);
      display.showNumberDec(code, true);
  }

  delay(500);
}

void triggerMainLockRelay(){
  digitalWrite(mainLockRelayPin, HIGH);
  delay(relayTimeToKeepOn); 
  digitalWrite(mainLockRelayPin, LOW);
}

void triggerEmergencyLockRelay(){
  digitalWrite(emergencyLockRelayPin, HIGH);
  delay(relayTimeToKeepOn); 
  digitalWrite(emergencyLockRelayPin, LOW);
}
  
// Function to check if the entered code matches the correct code
bool checkCode(const int *codeToCheck) {
  for (int i = 0; i < codeLength; i++) {
    if (enteredCode[i] != codeToCheck[i]) {
      return false; // Code doesn't match
    }
  }
  return true; // Code matches
}
