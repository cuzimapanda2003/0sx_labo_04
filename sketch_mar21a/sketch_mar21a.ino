#include <HCSR04.h>

#include <AccelStepper.h>

#include <LCD_I2C.h>

#define MOTOR_INTERFACE_TYPE 4

#define IN_1 8
#define IN_2 9
#define IN_3 10
#define IN_4 11

AccelStepper myStepper(MOTOR_INTERFACE_TYPE, IN_1, IN_3, IN_2, IN_4);

#define TRIGGER_PIN 3
#define ECHO_PIN 2

LCD_I2C lcd(0x27, 16, 2);

HCSR04 hc(TRIGGER_PIN, ECHO_PIN);

unsigned long previousMillis1 = 0;
const long interval1 = 50;


void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.print("2168637");
  lcd.setCursor(0, 1);
  lcd.print("labo4");
  delay(2000);
}





void loop() {

}




void dist() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;
    float distance = hc.dist();
  }
}