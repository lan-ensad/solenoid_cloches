#include <Button.h>
Button btn1(2);
Button btn2(3);
Button btn3(4);
Button btn4(5);

boolean routine = true;

//--------------------------
//          MENU SET
const int NBMENU = 5;
int pulsePrecision = 20; //menu 1
int pulseIntervalCourt = 33; //menu 2
int pulseIntervalLong = 99; //menu 3
int pulseNumber = 5; //menu 4
int pulseWaveDelay = 15; //menu5
/**
 * TODO
 * implémenter les shémas pour set 
 * l'interval entre chaque pulse
 */
//int shemNumber; //menu 6

int menu  = 0;
int val = 0;

void setup() {
  btn1.begin();
  btn2.begin();
  btn3.begin();
  btn4.begin();
  while (!Serial) { }; // for Leos
  Serial.begin(9600);
}

void Routine() {
  int pulseWave[pulseNumber];
  for (int i = 0; i < pulseNumber; i++) {
    Serial.print(i);
    Serial.print(" - ");
  }
  Serial.println();
}

void loop() {
  //---------------------------
  //   TRIGGER MENU | ->(DANS LE MENU) | ROUTINE
  if (btn3.pressed()) {
    routine = false;
    menu++;
    if (menu > NBMENU) {
      menu = 1;
    } else if (menu < 1) {
      menu = NBMENU;
    }
  } else if (btn4.pressed()) {
    routine = true;
    Serial.println("GOOOO");
  }

  //---------------------------
  //     DANS LA ROUTINE
  if (routine) {
    Routine();
    delay(2000);
  }

  //---------------------------
  //      DANS LE MENU
  else {
    switch (menu) {
      case 1:
        if (btn1.pressed()) {
          pulsePrecision --;
          delay(2);
        } else if (btn2.pressed()) {
          pulsePrecision ++;
          delay(2);
        }
        Serial.print("Pulse Precision : ");
        Serial.println(pulsePrecision);
        break;
      case 2:
        if (btn1.pressed()) {
          pulseIntervalCourt --;
          delay(2);
        } else if (btn2.pressed()) {
          pulseIntervalCourt ++;
          delay(2);
        }
        Serial.print("Pulse Interval Court: ");
        Serial.println(pulseIntervalCourt);
        break;
      case 3:
        if (btn1.pressed()) {
          pulseIntervalLong --;
          delay(2);
        } else if (btn2.pressed()) {
          pulseIntervalLong ++;
          delay(2);
        }
        Serial.print("Pulse Interval Long : ");
        Serial.println(pulseIntervalLong);
        break;
      case 4:
        if (btn1.pressed()) {
          pulseNumber --;
          delay(2);
        } else if (btn2.pressed()) {
          pulseNumber ++;
          delay(2);
        }
        Serial.print("Nombre de pulsation : ");
        Serial.println(pulseNumber);
        break;
      case 5:
        if (btn1.pressed()) {
          pulseWaveDelay --;
          delay(2);
        } else if (btn2.pressed()) {
          pulseWaveDelay ++;
          delay(2);
        }
        Serial.print("Nombre de pulsation : ");
        Serial.println(pulseWaveDelay);
        break;
    }
  }
}
