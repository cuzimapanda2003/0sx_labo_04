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
unsigned long previousMillis2 = 0;
const long interval1 = 500;
const long interval2 = 100;

int previousDistance = -1;
int lastSteps = 0;

int maxSpeed = 500;
int maxAccel = 100;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  lcd.print("2168637");
  lcd.setCursor(0, 1);
  lcd.print("labo4");
  delay(2000);

  myStepper.setMaxSpeed(maxSpeed);
  myStepper.setAcceleration(maxAccel);
}

void loop() {
  dist();
  }

void dist() {
  unsigned long currentMillis = millis();
  float degree;

  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;
    int distance = hc.dist();
    float steps = map(distance, 30, 60, 0, 2048);


    if (distance != previousDistance) {

      lcd.setCursor(6, 0);
      lcd.print("                ");
      lcd.setCursor(0, 0);
      lcd.print("dist = ");
      lcd.setCursor(8, 0);
      lcd.print(distance);


      lcd.setCursor(6, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);

      if (distance < 30) {
        lcd.print("obj  : ");
        lcd.setCursor(7, 1);
        lcd.print("trop pret");
      } else if (distance > 60) {
        lcd.print("obj  : ");
        lcd.setCursor(7, 1);
        lcd.print("trop loin");
      } else {
        degree = (steps / 2048) * 360;
        lcd.print("Deg  : ");
        lcd.setCursor(7, 1);
        lcd.print(degree);





        if (distance > previousDistance) {

          myStepper.moveTo(lastSteps + steps);
        } else if (distance < previousDistance) {

          myStepper.moveTo(lastSteps - steps);
        }


        while (myStepper.distanceToGo() != 0) {
          myStepper.run();
        }


        lastSteps = myStepper.currentPosition();
      }


      previousDistance = distance;
    }
  }
}

