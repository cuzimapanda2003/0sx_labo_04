#include <HCSR04.h>

#include <AccelStepper.h>

#include <LCD_I2C.h>

#define MOTOR_INTERFACE_TYPE 4

#define IN_1 8
#define IN_2 9
#define IN_3 10
#define IN_4 11

AccelStepper myStepper(MOTOR_INTERFACE_TYPE, IN_1, IN_3, IN_2, IN_4);

#define TRIGGER_PIN 21
#define ECHO_PIN 20

LCD_I2C lcd(0x27, 16, 2);

HCSR04 hc(TRIGGER_PIN, ECHO_PIN);

void setup() {
  Serial.begin(9600);
}

void loop() {
dist();
}

void dist(){
  float distance = hc.dist();
  Serial.print("Distance:");
  Serial.println(distance);
  delay(100);



}