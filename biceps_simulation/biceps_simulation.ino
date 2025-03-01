// Define pins for the stepper motor
const int IN1 = 8;  // Connect to ULN2003 IN1
const int IN2 = 9;  // Connect to ULN2003 IN2
const int IN3 = 10; // Connect to ULN2003 IN3
const int IN4 = 11; // Connect to ULN2003 IN4

// Define pin for the push button
const int buttonPin = 7; // Connect to push button

// Define the step sequence for unipolar stepper (4 steps)
int stepSequence[4][4] = {
  {1, 0, 0, 0},  // Step 1
  {0, 1, 0, 0},  // Step 2
  {0, 0, 1, 0},  // Step 3
  {0, 0, 0, 1}   // Step 4
};

// Define the number of steps per revolution for the motor
const int stepsPerRevolution = 131; // Adjust based on your motor specs

// Define a delay for motor speed (smaller delay = faster speed)
const int stepDelay = 5; // Adjust for desired speed (milliseconds)

// Variable to track the current position of the motor
int currentPosition = 0;

void setup() {
  // Set motor pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Set button pin as input
  pinMode(buttonPin, INPUT_PULLUP); // Use internal pull-up resistor

  // Initialize all motor pins to LOW
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  // Read the state of the button
  bool buttonPressed = digitalRead(buttonPin) == LOW;

  if (buttonPressed && currentPosition < stepsPerRevolution) {
    // Rotate clockwise if the button is pressed
    rotateMotorOneStep(true);
    currentPosition++;
  } else if (!buttonPressed && currentPosition > 0) {
    // Rotate counterclockwise to return to position X
    rotateMotorOneStep(false);
    currentPosition--;
  }
}

// Function to rotate the motor
void rotateMotorOneStep(bool clockwise) {
  for (int step = 0; step < 4; step++) {
    // Determine step index based on direction
    int stepIndex = clockwise ? step : 3 - step;

    // Set motor pins based on step sequence
    digitalWrite(IN1, stepSequence[stepIndex][0]);
    digitalWrite(IN2, stepSequence[stepIndex][1]);
    digitalWrite(IN3, stepSequence[stepIndex][2]);
    digitalWrite(IN4, stepSequence[stepIndex][3]);

    delay(stepDelay); // Wait before moving to the next step
  }
}
