#include <Stepper.h>
#include <Bounce2.h> 

const int eauPin = 9;
const int ice_teaPin = 10;
const int siropPin = 8;

const int limitSwitch = A0; 

const int stepPin = 2;
const int dirPin = 3;

const int nombreDePas = 800;
const int vitesse = 200;

Stepper stepper(nombreDePas, stepPin, dirPin);
Bounce debouncer_limitSwitch = Bounce(); 

bool isLimitSwitchPressed = false;
bool isMotorMoving = false;

unsigned long previousMillis = 0; 
const long intervalS = 1200; 
const long intervalI = 6700; 
const long intervalE = 12500; 

void setup() {
  pinMode(eauPin, OUTPUT);
  pinMode(ice_teaPin, OUTPUT);
  pinMode(siropPin, OUTPUT);

  pinMode(limitSwitch, INPUT_PULLUP); 

  Serial.begin(9600);
  delay(1500); 

  stepper.setSpeed(vitesse); 
  
  debouncer_limitSwitch.attach(limitSwitch);
  debouncer_limitSwitch.interval(5); 

  isLimitSwitchPressed = digitalRead(limitSwitch) == LOW;

  stepper.setSpeed(vitesse);
  stepper.step(-1);
  isMotorMoving = true;
  while (!isLimitSwitchPressed) {
    debouncer_limitSwitch.update();
    isLimitSwitchPressed = debouncer_limitSwitch.read() == LOW;
    stepper.step(-1);
    delay(5);
  }
  isMotorMoving = false;
}

void distribuerEau() {
  unsigned long currentMillis = millis();
  while (millis() - currentMillis < intervalE) {
    stepper.step(nombreDePas);
  }

  delay(700);

  digitalWrite(eauPin, HIGH);
  delay(2000);
  digitalWrite(eauPin, LOW);

  delay(2000);

  currentMillis = millis();
  while (millis() - currentMillis < intervalE) {
    stepper.step(-nombreDePas);
  }
}

void distribuerIceTea() {
  unsigned long currentMillis = millis();
  while (millis() - currentMillis < intervalI) {
    stepper.step(nombreDePas);
  }

    delay(700);

  digitalWrite(ice_teaPin, HIGH);
  delay(2000);
  digitalWrite(ice_teaPin, LOW);

  delay(2000);

  currentMillis = millis();
  while (millis() - currentMillis < intervalI) {
    stepper.step(-nombreDePas);
  }
}

void distribuerSirop() {
  unsigned long currentMillis = millis();
  while (millis() - currentMillis < intervalS) {
    stepper.step(nombreDePas);
  }

    delay(700);

  digitalWrite(siropPin, HIGH);
  delay(2000);
  digitalWrite(siropPin, LOW);

  delay(2000);

  currentMillis = millis();
  while (millis() - currentMillis < intervalS) {
    stepper.step(-nombreDePas);
  }
}

void loop() {
  debouncer_limitSwitch.update();
  
  if (!isLimitSwitchPressed && !isMotorMoving) {
    isMotorMoving = true;
    while (!isLimitSwitchPressed) {
      stepper.step(1);
      isLimitSwitchPressed = digitalRead(limitSwitch) == LOW;
    }
    stepper.setSpeed(vitesse);
    stepper.step(1);
    isMotorMoving = false;
  }

  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == '1') {
      distribuerSirop();
    } else if (command == '2') {
      distribuerIceTea();
    } else if (command == '3') {
      distribuerEau();
    }
  }

  delay(100);
}
