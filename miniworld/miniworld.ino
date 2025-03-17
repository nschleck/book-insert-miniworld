/* 
This code controls the dynamic elements of the book insert miniworld.
Includes night/day LED lighting cycle, flickering flame LEDs, and power control
*/

// TODO integrate flame flicker LEDs
  // make non-blocking flicker functions
  // separate flicker instances for different LEDs
// TODO smooth out low-light color ramps
// TODO make on-demand RGBW testing function 
// TODO incorporate power switch / EEPROM state memory


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
  
  // initialize daytime
  rampToRGBW(10, 0, 0, 100, "1. day", 1000, LINEAR);


}

void loop() {
  // day/night cycle
    delay(10000);
    rampToRGBW(40, 0, 55, 30, "2. sunset", 5000, CUBIC_IN);
    rampToRGBW(10, 0, 50, 10,  "3. dusk",   2000, LINEAR);
    rampToRGBW(0, 0, 5, 2, "4. night",  5000, CUBIC_OUT);

    delay(10000);
    rampToRGBW(20, 0, 20, 20, "5. dawn",   5000, CUBIC_IN);
    rampToRGBW(55, 0, 55, 55, "6. sunrise",2000, LINEAR);
    Serial.println();
    rampToRGBW(10, 0, 5, 100, "1. day",    5000, CUBIC_OUT);


  // Manual input RGBW channels
    // int r;
    // int b;
    // int w;

    // r = getUserColorChannel("Red");
    // b = getUserColorChannel("Blue");
    // w = getUserColorChannel("White");

    // Serial.print("Custom Ramp to ");
    // Serial.print(r);
    // Serial.print(", 0, ");
    // Serial.print(b);
    // Serial.print(", ");
    // Serial.println(w);
    // rampToRGBW(r, 0, b, w, "...Ramp Complete", 3000);
    // Serial.println();
    // delay(1000);

  // ramp style testing
    // R_ramp.go(100, 3000, EXPONENTIAL_IN);
    // while(R_ramp.isRunning()){
    //   Serial.print("Value:");
    //   Serial.print(R_ramp.update());
    //   Serial.print(",");
    //   Serial.print("BoundLow:");
    //   Serial.print(0);
    //   Serial.print(",");
    //   Serial.print("BoundHigh:");
    //   Serial.println(100);
    //   delay(5);
    // }

    // R_ramp.go(10, 3000, EXPONENTIAL_OUT);
    // while(R_ramp.isRunning()){
    //   Serial.print("Value:");
    //   Serial.print(R_ramp.update());
    //   Serial.print(",");
    //   Serial.print("BoundLow:");
    //   Serial.print(0);
    //   Serial.print(",");
    //   Serial.print("BoundHigh:");
    //   Serial.println(100);
    //   delay(5);
    // }

}

int getUserColorChannel(String color){
  int colorVal;
  Serial.print(color);
  Serial.println(" color value?");
  while (!(Serial.available())) {
  }

  colorVal = Serial.parseInt();
  Serial.read(); //get rid of garbage trailing line feed char
  delay(100);

  return colorVal;
}

void rampToRGBW(int r, int g, int b, int w, String label, int rampDur, int temp){
    // time dilation constant
    float tau = 3;

    ramp_mode rampStyle = (ramp_mode)temp;

    R_ramp.go(r, rampDur * tau, rampStyle); 
    B_ramp.go(b, rampDur * tau, rampStyle); 
    W_ramp.go(w, rampDur * tau, rampStyle); 

    while (R_ramp.isRunning() || B_ramp.isRunning() || W_ramp.isRunning()){
      strip.setPixelColor(led, R_ramp.update(), 0, B_ramp.update(), W_ramp.update());
      strip.show();
    }

    Serial.println(label);
}