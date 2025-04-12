#include <HCSR04.h>
#include <AccelStepper.h>
#include <LCD_I2C.h>

#define MOTOR_INTERFACE_TYPE 4

#define IN_1 31
#define IN_2 33
#define IN_3 35
#define IN_4 37

enum dist { TROP_PRES,
            TROP_LOIN,
            MILIEU };
dist DIST = TROP_LOIN;

AccelStepper myStepper(MOTOR_INTERFACE_TYPE, IN_1, IN_3, IN_2, IN_4);

#define TRIGGER_PIN 3
#define ECHO_PIN 2

LCD_I2C lcd(0x27, 16, 2);

HCSR04 hc(TRIGGER_PIN, ECHO_PIN);

unsigned long previousMillis1 = 0;
const long interval1 = 500;

int previousDistance = -1;
int distance;
long targetPosition = 0;
long previousTarget = -1;
float degree;

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
  myStepper.run(); 
  dist();         
}

void dist() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;

    distance = hc.dist();

    if (distance < 30) {
      DIST = TROP_PRES;
    } else if (distance > 60) {
      DIST = TROP_LOIN;
    } else {
      DIST = MILIEU;
    }


    if (distance != previousDistance) {
      affichage();

      switch (DIST) {
        case TROP_PRES:
          affichageTropPres();
          break;

        case TROP_LOIN:
          affichageLoin();
          break;

        case MILIEU:
         
          targetPosition = map(distance, 30, 60, 0, 1024);

          
          if (targetPosition != previousTarget) {
            myStepper.moveTo(targetPosition);
            previousTarget = targetPosition;
          }

          affichageMilieu(targetPosition);
          break;
      }
    }

    previousDistance = distance;
  }
}

void affichage() {
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print("dist = ");
  lcd.print(distance);
  lcd.print(" cm");

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
}

void affichageTropPres() {
  lcd.print("obj  : trop pres");
}

void affichageLoin() {
  lcd.print("obj  : trop loin");
}

void affichageMilieu(long steps) {
  degree = (steps / 2048.0) * 360.0;
  lcd.print("Deg  : ");
  lcd.print(degree, 1);
}