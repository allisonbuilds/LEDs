/*
Allison Berman 2014

This is modified from the Adafruit_Neopixel strandtest for (http://www.adafruit.com/products/1138)
Code for "flux capacitor" effect on LED strand broken into 3 strips of 6 each for a total of 18 pixels.
Each RGB draws 5V/60mA and has an integrated controller which means it uses a single input/output for data. 
All the LEDs are controlled via shift registers chained along the strip
Buffer needs 3 bytes RAM per pixel (1500 bytes/500 pixels - use a Mega or Beaglebone for big room lighting projects)

Notes from Adafruit:
Not great for POV - use an SPI caapble strip instead 
LEDs will not work with the Raspberry Pi, Basic Stamp, NETduino, any other interpreted/virtual machine microprocessor or __any processor slower than 8 MHz__
ATTiny85: 20MHz processor, 512 bytes RAM = good 
Atmega32u4: 16MHz, 2.5kb x 8 RAM = good (Flora, Arduino Micro) See special Flora codes below
ATmega328: 20MHz, 2Kb RAM = good (Lilypad ProtoSnap/Simple) (LilyPads can only output 40mA per pin)


*/

#include <Adafruit_NeoPixel.h>
// fixed #include from #include_

#define PIN 6
int r = 0;
int g = 0;
int b = 0;
//PIN 6 is a convenient default but it could be any PWM out pin

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(18, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

#define ORANGE 250,187, 85
#define LBLUE 94,104,127
#define WHITE 127,127,127

void loop() {
  
//  fade(90,55,0,10);
//  theaterChase(strip.Color(ORANGE),50);
  fluxChase(strip.Color(ORANGE), 10);
  fadeslope(ORANGE,10);
//  fadeslope(LBLUE,10);
  delay(100);
  
  // Some example procedures showing how to display to the pixels:
//  colorWipe(strip.Color(255, 0, 0), 50); // Red
//  colorWipe(strip.Color(0, 255, 0), 50); // Green
//  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
//  theaterChase(strip.Color(127, 127, 127), 50); // White 
//  theaterChase(strip.Color(127,   0,   0), 50); // Red
//light yellow-orange original color flux capacitor - (252,252, 212) or (127,127,87) or (127,127,106)?
//more orange - (250,187, 85) or (125, 94, 43)?
//light blue (182, 208, 250) or (94, 104, 127)?
//  theaterChase(strip.Color(  0,   0, 127), 50); // Blue
//  theaterChase(strip.Color(100,  100, 127), 150); // light blue, slow - it is slow in the movie until time loop is activated
//changing the crawl speed: make a var speed
//make a function that iterates during main loop and increases speed. call theaterchase in that function - or set a new theaterchase function
//    fluxChase(strip.Color(80,  80, 127), 150); //light blue
    
//    r=90;
//    g = 55;
//    b = 0;
//    fluxChase(strip.Color(r, g, b), 150); //dim gold
//    fluxChase(strip.Color(90, 55, 0), 150); //dim gold
/*
  if(buttonpress){
    fluxChase(strip.Color(100,  100, 127), 150);
  }
  else {  theaterChase(strip.Color(100,  100, 127), 150); }

*/

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}


//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do j cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

void fluxChase(uint32_t c, uint8_t wait) {
    for (int j=0; j<30; j++) {  //do 30 cycles of chasing
      wait -=5; //decrease wait by 5 ms each round do not go above 50 ms to avoid latching issues
        for (int q=0; q < 6; q++) {
            for (int i=0; i < strip.numPixels(); i=i+6) {
            strip.setPixelColor(i+q, c);    //turn every 6th pixel on
             }
            strip.show();
     
            delay(wait);
     
            for (int i=0; i < strip.numPixels(); i=i+6) {
            strip.setPixelColor(i+q, 0);        //turn every 6th pixel off
            }
        }
       
   }

//   for (int j=0; j<10; j++) {  //slow fade to 0
//     
//      for (int i=0; i < strip.numPixels(); i=i+1) {
//        if(c > 0){
//          c -= 10;
//          strip.setPixelColor(i, c);    
//         }
//        strip.show();
//     
//        delay(50);
//    
//    }
//  
//  }
}

// Color Wheel
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void fade(int R, int G, int B, uint8_t wait){
  //strip.Color(R,G,B);
 
    //strip.numPixels - how many leds need fading
    //let's fade all of them
    for(int j= 0; j < 256; j++){
       for (int i=0; i < strip.numPixels(); i=i+1) {

          strip.setPixelColor(i, strip.Color(R,G,B));    
       }
   strip.show();
   //after showing all the leds, then decrement each color by 1
   //make sure we don't accidentally go below 0 and loop back around
   if(R > 0){ R--; }
   if(G > 0){ G--; }
   if(B > 0){ B--; }
   
   delay(wait);
   //look at using a sine wave her
//    
   }
}

char calcslope(int S, int R, int j){
  int r;
  r = S - R*j; 
  r /= 256;
  return r;
}

void fadeslope(int R, int G, int B, uint8_t wait){
    int S = 256*R; //multiply by step number (j) so we don't need fractions until the end
    int H = 256*G;
    int C = 256*B;
    int r; //initial val R needs to remain constant but the fading val is a moving target
    int g;
    int b;
    
    for(int j= 0; j < 256; j++){
      r = calcslope(S,R,j);
      g = calcslope(H,G,j);
      b = calcslope(C,B,j);
      
       for (int i=0; i < strip.numPixels(); i=i+1) {

          strip.setPixelColor(i, strip.Color(r,g,b));    
       }
       strip.show();
   
       delay(wait);
    }
}
