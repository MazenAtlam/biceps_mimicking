// Define pins for the stepper motor
const int IN1 = 8;  // Connect to ULN2003 IN1
const int IN2 = 9;  // Connect to ULN2003 IN2
const int IN3 = 10; // Connect to ULN2003 IN3
const int IN4 = 11; // Connect to ULN2003 IN4

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

void setup() {
  // Set motor pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initialize all pins to LOW
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  // Rotate the motor clockwise for one revolution
  Serial.println("Clockwise");
  rotateMotor(stepsPerRevolution, true); // Rotate clockwise
  delay(500);

  // Rotate the motor counterclockwise for one revolution
  Serial.println("Counterclockwise");
  rotateMotor(stepsPerRevolution, false); // Rotate counterclockwise
  delay(500);
}

// Function to rotate the motor
void rotateMotor(int steps, bool clockwise) {
  for (int i = 0; i < steps; i++) {
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
}
