#include <Button.h>
Button btn1(2);
Button btn2(3);
Button btn3(4);
Button btn4(5);

unsigned long currentMillis, prevMillis;
boolean routine = true;
//--------------------------
//         MENU SET
const int NBMENU = 6;
int pulsePrecision = 20; //menu 1
int pulseIntervalCourt = 33; //menu 2
int pulseIntervalLong = 99; //menu 3
int pulseNumber = 5; //menu 4
int waveDelay = 1500; //menu5
String shem = "01001"; //menu 6

int shemIndex = 0;
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
//=================================
//           FUNCTIONS
void Dong(int interval) {
  Serial.print("HIGH -- ");
  delay(pulsePrecision);
  Serial.println("LOW");
  delay(interval);
}
void Routine() {
  for (int i = 0; i < pulseNumber ; i++) {
    Serial.print(i);
    if (shem.charAt(i) == '0') {
      Serial.print(" |court| ");
      Dong(pulseIntervalCourt);
    } else {
      Serial.print(" |long| ");
      Dong(pulseIntervalLong);
    }
  }
  Serial.println();
}
//=================================
//           L00P
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
    currentMillis = millis();
    if (currentMillis - prevMillis >= waveDelay) {
      prevMillis = currentMillis;
      Routine();
    }
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
          currentMillis = millis();
          if(currentMillis-prevMillis>=200){
            while(btn1.pressed()){
              pulseIntervalLong--;
            }
          }
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
          shem.remove(pulseNumber + 1);
          delay(2);
        } else if (btn2.pressed()) {
          pulseNumber ++;
          shem += String(random(0, 1));
          delay(2);
        }
        Serial.print("Nombre de pulsation : ");
        Serial.println(pulseNumber);
        break;
      case 5:
        if (btn1.pressed()) {
          waveDelay --;
          delay(2);
        } else if (btn2.pressed()) {
          waveDelay ++;
          delay(2);
        }
        Serial.print("Waves delay : ");
        Serial.println(waveDelay / 1000);
        break;
      case 6:
        Serial.print("shemIndex ");
        Serial.print(shemIndex);
        Serial.print(" : ");
        Serial.println(shem.charAt(shemIndex));
        if (btn1.pressed()) {
          shem.setCharAt(shemIndex, '0');
          delay(2);
        } else if (btn2.pressed()) {
          shem.setCharAt(shemIndex, '1');
          delay(2);
        } else if (btn3.pressed()) {
          shemIndex ++;
          if (shemIndex > shem.length()-1) {
            menu = 1;
            shemIndex = 0;            
          }
        }
        break;
    }
  }
}
