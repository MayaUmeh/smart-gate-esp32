#include <ESP32Servo.h>

#define SERVO_PIN 18
#define PIR_PIN 23
#define BUTTON_PIN 19

#define OPEN_ANGLE 90
#define CLOSED_ANGLE 0
#define OPEN_TIME 10000
#define DEBOUNCE_TIME 50

Servo gateServo;

bool gateOpen = false;
unsigned long openTime = 0;

// PIR state tracking
bool lastPirState = LOW;
bool pirEvent = false;

// Button debounce
bool lastButtonReading = HIGH;
bool buttonState = HIGH;
unsigned long lastDebounceTime = 0;

//  prevents repeated spam
bool extendUsed = false;

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  gateServo.attach(SERVO_PIN);
  gateServo.write(CLOSED_ANGLE);

  Serial.println("Smart Gate Ready");
}

void loop() {

  // PIR Detection
  bool pirNow = digitalRead(PIR_PIN);

  if (pirNow == HIGH && lastPirState == LOW) {
    Serial.println("PIR Triggered");
    pirEvent = true;
  }

  lastPirState = pirNow;

  // button debounces
  bool reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > DEBOUNCE_TIME) {
    buttonState = reading;
  }

  lastButtonReading = reading;

  bool buttonEvent = (buttonState == LOW);

  // handles triggers
  if (pirEvent || buttonEvent) {

    if (!gateOpen) {
      Serial.println("Gate Opening");
      gateServo.write(OPEN_ANGLE);
      gateOpen = true;
      extendUsed = false;   // reset
    }
    else {
      if (!extendUsed) {
        Serial.println("Gate already open - extending time");
        extendUsed = true;
      }
    }

    openTime = millis();

    // resets
    pirEvent = false;
  }

  //closes gate
  if (gateOpen && millis() - openTime > OPEN_TIME) {
    Serial.println("Gate Closing");
    gateServo.write(CLOSED_ANGLE);
    gateOpen = false;
    extendUsed = false;
  }
}