#include <NewPing.h> // Include NewPing library

// Define ultrasonic sensor pins and max distance
#define trigPin 9
#define echoPin 10
#define MAX_DISTANCE 200 // Max distance we want to measure (in cm)

NewPing sonar(trigPin, echoPin, MAX_DISTANCE); // Initialize NewPing

// Define motor control pins
#define leftMotor1 2
#define leftMotor2 3
#define rightMotor1 4
#define rightMotor2 5
#define ENA 6
#define ENB 7

// Define speed of the motors
int motorSpeed = 200; // Value between 0-255

void setup() {
  // Set motor pins as output
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Initialize serial communication
  Serial.begin(9600);
}

void moveForward() {
  analogWrite(ENA, motorSpeed); // Speed control for left motor
  analogWrite(ENB, motorSpeed); // Speed control for right motor

  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
}

void moveLeft() {
  analogWrite(ENA, motorSpeed); // Left motor at full speed
  analogWrite(ENB, motorSpeed / 2); // Slow down right motor

  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH); // Move right motor in reverse
}

void moveRight() {
  analogWrite(ENA, motorSpeed / 2); // Slow down left motor
  analogWrite(ENB, motorSpeed); // Right motor at full speed

  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH); // Move left motor in reverse
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
}

void stopBot() {
  analogWrite(ENA, 0); // Stop left motor
  analogWrite(ENB, 0); // Stop right motor
}

void loop() {
  int distance = sonar.ping_cm(); // Get distance in cm
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 20) {
    // No obstacle in front, move forward
    moveForward();
  } else if (distance > 10 && distance <= 20) {
    // Obstacle is near, move left
    moveLeft();
    delay(500); // Adjust delay to control how long it moves left
  } else {
    // Very close obstacle, stop
    stopBot();
    delay(500);
    moveRight(); // Try moving right to avoid
    delay(500);
  }

  delay(100); // Small delay between sensor readings
}
