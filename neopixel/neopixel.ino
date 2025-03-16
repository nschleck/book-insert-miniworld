/* 
This code controls the dynamic elements of the book insert miniworld.
Includes night/day LED lighting cycle, flickering flame LEDs, and power control
*/

#include <Adafruit_NeoPixel.h>
#include <Ramp.h>
//#include <EEPROM.h>

// Setup Neopixel vars
  const int ledPin = 9;
  const int ledCount = 2;
  const int led = 1; // strip index

  ramp R_ramp;
  // Green LED channel not used
  ramp B_ramp;
  ramp W_ramp;

  Adafruit_NeoPixel strip(ledCount, ledPin, NEO_RGBW + NEO_KHZ800);

void setup() {
  strip.begin();
  Serial.begin(9600);
  
  //initialize daytime
  rampToRGBW(10, 0, 0, 100, "1. day", 1000);
  delay(10000);

}

void loop() {
  // day/night cycle
    rampToRGBW(40, 0, 55, 30, "2. sunset", 5000);
    rampToRGBW(10, 0, 50, 10,  "3. dusk",   2000);
    rampToRGBW(0, 0, 5, 2, "4. night",  5000);
    delay(10000);

    rampToRGBW(20, 0, 20, 20, "5. dawn",   5000);
    rampToRGBW(55, 0, 55, 55, "6. sunrise",2000);
    Serial.println();
    rampToRGBW(10, 0, 5, 100, "1. day",    5000);
    delay(10000);

}

void rampToRGBW(int r, int g, int b, int w, String label, int rampDur){
    // time dilation constant
    float tau = 1.5;

    R_ramp.go(r, rampDur * tau); 
    B_ramp.go(b, rampDur * tau); 
    W_ramp.go(w, rampDur * tau); 

    while (R_ramp.isRunning() && B_ramp.isRunning() && W_ramp.isRunning()){
      strip.setPixelColor(led, R_ramp.update(), 0, B_ramp.update(), W_ramp.update());
      strip.show();
    }

    Serial.println(label);
}