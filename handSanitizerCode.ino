#include <Servo.h>

const int trigPin = 7;      // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6;      // Echo Pin of Ultrasonic Sensor
const int greenLEDPin = 8;  // Green LED Pin
const int redLEDPin = 9;    // Red LED Pin
const int powerSwitchPin = 10; // Power switch Pin

Servo Myservo;

void setup() {
  Serial.begin(9600); // Starting Serial Terminal
  Myservo.attach(5);  // Signal Pin of Servo
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(powerSwitchPin, INPUT_PULLUP); // Internal pull-up resistor to keep the pin HIGH when the switch is open

  Serial.print("  Distance    ");
  Serial.print("  Measurement  ");
  delay(1000);
  delay(1000);
  Serial.print("Made By :");
  Serial.print(" OverAll Technical Gyan");
  delay(2000);
}

void loop() {
  // Check if the power switch is ON
  if (digitalRead(powerSwitchPin) == LOW) {
    long duration, cm;
    pinMode(trigPin, OUTPUT);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    cm = microsecondsToCentimeters(duration);

    Serial.print("Distance:");
    Serial.print(cm);
    Serial.print("cm");
    delay(100);

    if (cm >= 20) {
      Myservo.write(0);
      digitalWrite(greenLEDPin, HIGH); // Green LED ON
      digitalWrite(redLEDPin, LOW);   // Red LED OFF
    } else {
      Myservo.write(90);
      digitalWrite(greenLEDPin, LOW);  // Green LED OFF
      digitalWrite(redLEDPin, HIGH);   // Red LED ON
    }

    Serial.println();
    delay(100);
  } else {
    // If the power switch is OFF, turn off LEDs and servo
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(redLEDPin, LOW);
    Myservo.write(0);
  }
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}
