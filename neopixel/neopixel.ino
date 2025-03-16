#include <Adafruit_NeoPixel.h>
#include <Ramp.h>

const int ledPin = 9;
const int ledCount = 2;
const int led = 1; // strip index

int delayTime = 3000;

ramp R_ramp;
ramp B_ramp;
ramp W_ramp;

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(ledCount, ledPin, NEO_RGBW + NEO_KHZ800);

void setup() {
  strip.begin();

  //initialize daytime
  R_ramp.go(10); 
  B_ramp.go(0); 
  W_ramp.go(200); 
  strip.setPixelColor(led, R_ramp.update(), 0, B_ramp.update(), W_ramp.update());
  strip.show();

  Serial.begin(9600);

}

void loop() {
  //test pattern cycle
    // strip.setPixelColor(0, 200, 0, 0, 0);
    // strip.show();
    // delay(1000);
    // strip.setPixelColor(0, 0, 200, 0, 0);
    // strip.show();
    // delay(1000);
    // strip.setPixelColor(0, 0, 0, 200, 0);
    // strip.show();
    // delay(1000);
    // strip.setPixelColor(0, 0, 0, 0, 200);
    // strip.show();
    // delay(1000);
    // strip.clear();
    // delay(1000);

  //test daylight colors cycle
    // strip.setPixelColor(led, 10, 0, 0, 200); //day
    // strip.show();
    // delay(delayTime);
    // strip.setPixelColor(led, 100, 0, 50, 100); //sunset
    // strip.show();
    // delay(delayTime);
    // strip.setPixelColor(led, 0, 0, 50, 20); //dusk
    // strip.show();
    // delay(delayTime);
    // strip.setPixelColor(led, 0, 0, 10, 5); //night
    // strip.show();
    // delay(delayTime);
    // strip.setPixelColor(led, 20, 0, 20, 20); //dawn
    // strip.show();
    // delay(delayTime);
    // strip.setPixelColor(led, 100, 0, 50, 100); //sunrise
    // strip.show();
    // delay(delayTime);

  // Ramp testing
    // W_ramp.go(200); 
    // W_ramp.go(0,10000);
    // while (W_ramp.isRunning()){
    //   strip.setPixelColor(led, 10, 0, 0, W_ramp.update()); //day
    //   strip.show();
    // }
    // delay(3000);

  // Ramp daylight cycle

    // // go to sunset
    // R_ramp.go(55 , 5000); 
    // B_ramp.go(55  , 5000); 
    // W_ramp.go(55 , 5000); 
    // while (R_ramp.isRunning() && B_ramp.isRunning() && W_ramp.isRunning()){
    //   strip.setPixelColor(led, R_ramp.update(), 0, B_ramp.update(), W_ramp.update());
    //   strip.show();
    // }
    // Serial.println("sunset");

    // // go to dusk
    // R_ramp.go(0 , 5000); 
    // B_ramp.go(50  , 5000); 
    // W_ramp.go(20 , 5000); 
    // while (R_ramp.isRunning() && B_ramp.isRunning() && W_ramp.isRunning()){
    //   strip.setPixelColor(led, R_ramp.update(), 0, B_ramp.update(), W_ramp.update());
    //   strip.show();
    // }
    // Serial.println("dusk");

    // // go to night
    // R_ramp.go(0 , 5000); 
    // B_ramp.go(10  , 5000); 
    // W_ramp.go(5 , 5000); 
    // while (R_ramp.isRunning() && B_ramp.isRunning() && W_ramp.isRunning()){
    //   strip.setPixelColor(led, R_ramp.update(), 0, B_ramp.update(), W_ramp.update());
    //   strip.show();
    // }
    // Serial.println("night");
    // delay(5000);

    // // go to dawn
    // R_ramp.go(20 , 5000); 
    // B_ramp.go(20  , 5000); 
    // W_ramp.go(20 , 5000); 
    // while (R_ramp.isRunning() && B_ramp.isRunning() && W_ramp.isRunning()){
    //   strip.setPixelColor(led, R_ramp.update(), 0, B_ramp.update(), W_ramp.update());
    //   strip.show();
    // }
    // Serial.println("dawn");

    // // go to sunrise
    // R_ramp.go(55 , 5000); //100
    // B_ramp.go(55  , 5000); //50
    // W_ramp.go(55 , 5000); 
    // while (R_ramp.isRunning() && B_ramp.isRunning() && W_ramp.isRunning()){
    //   strip.setPixelColor(led, R_ramp.update(), 0, B_ramp.update(), W_ramp.update());
    //   strip.show();
    // }
    // Serial.println("sunrise");

    // // go to day
    // R_ramp.go(10 , 5000); 
    // B_ramp.go(0  , 5000); 
    // W_ramp.go(100 , 5000); 
    // while (R_ramp.isRunning() && B_ramp.isRunning() && W_ramp.isRunning()){
    //   strip.setPixelColor(led, R_ramp.update(), 0, B_ramp.update(), W_ramp.update());
    //   strip.show();
    // }
    // Serial.println("day");
    
  // functions
    rampToRGBW(55, 0, 55, 55, "sunset", 10000);
    rampToRGBW(0, 0, 50, 20,  "dusk",   2000);
    rampToRGBW(0, 0, 5, 2, "night",  20000);
    delay(5000);

    rampToRGBW(20, 0, 20, 20, "dawn",   20000);
    rampToRGBW(55, 0, 55, 55, "sunrise",2000);
    rampToRGBW(10, 0, 0, 100, "day",    5000);
    delay(5000);

}

void rampToRGBW(int r, int g, int b, int w, String label, int rampDur){
    // time dilation constant
    float tau = .75;
    // g LED is not used
    R_ramp.go(r, rampDur * tau); 
    B_ramp.go(b, rampDur * tau); 
    W_ramp.go(w, rampDur * tau); 

    while (R_ramp.isRunning() && B_ramp.isRunning() && W_ramp.isRunning()){
      strip.setPixelColor(led, R_ramp.update(), 0, B_ramp.update(), W_ramp.update());
      strip.show();
    }

    Serial.println(label);
}