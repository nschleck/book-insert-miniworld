#include <EEPROM.h>

const int FETPin1 = 9;
const int FETPin2 = 10;
const int btnPin = 2;

bool btnOn;

int value;
int randomDelay;

void setup() {
  Serial.begin(9600);

  pinMode(FETPin1, OUTPUT);
  pinMode(FETPin2, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
}

void loop() {
  btnOn = digitalRead(btnPin);
  if(btnOn){
    analogWrite(FETPin2, 0);
    flickerLED(FETPin1);
  } else {
    analogWrite(FETPin1, 0);
    flickerLED(FETPin2);
  }

  // delay(500);

  // basic loop
    // while (value < 255){
    //   analogWrite(switchPin, value);
    //   delay(10);
    //   value++;
    // }

    // while (value > 0){
    //   analogWrite(switchPin, value);
    //   delay(10);
    //   value--;
    // }
    // delay(1000);

  // faster + random
    // while (value < 200){
    //   randomDelay = random(10);

    //   if (randomDelay == 7){
    //     break;
    //   }

    //   analogWrite(switchPin, value);
    //   delay(randomDelay+5);
    //   value++;
    // }

    // while (value > 50){
    //   randomDelay = random(10);

    //   if (randomDelay == 7){
    //     break;
    //   }

    //   analogWrite(switchPin, value);
    //   delay(randomDelay+5);
    //   value--;
    // }


}

void flickerLED(int pin) {
  analogWrite(pin, random(80) + 175);
  delay(random(100));
}
