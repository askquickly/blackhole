// read data from the android serial connection and address data to ring light
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// make the pin output:
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);

#define hi_red strip.Color(80, 0, 0) // mute
#define hi_blue strip.Color(0, 0, 255) // listen
#define hi_white strip.Color(127, 127, 127) //vol adjt
#define hi_or strip.Color(255, 140, 0) //err set
#define off strip.Color(0, 0, 0) //vol adjt
#define hi_g strip.Color(10, 0, 0) //vol adjt
#define topaz strip.Color(0, 0, 255) // listen

// hold bytes
int incomingByte = 0;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  strip.begin();
  strip.show();
}


void loop()
{
  if (Serial.available()) {
   // while(Serial.read() != -1) {
    readsa();
    // byte 49 = 1
    Serial.print(incomingByte);
  }
}

void readsa() {
  // read the incoming byte:
  incomingByte = Serial.read();
  if (incomingByte == '1')
  {
    // listening
    colourWipe(hi_blue, 30);
  }
  else if (incomingByte == '2')
  {
    // stopped
    colourWipe(hi_blue, 10);
    colourWipe(off, 10);
  }
  else if (incomingByte == '3')
  {
    // mute function
    colourWipe(hi_red, 10);
    colourWipe(off, 90);
    colourWipe(hi_red, 10);
  }
  else if (incomingByte == '4')
  {
    // error or setup function
    colourWipe(hi_or, 90);
    colourWipe(off, 90);
    colourWipe(hi_or, 90);
    colourWipe(off, 90);
  }
  else if (incomingByte == '5')
  {
    // error or setup function
    colourWipe(hi_g, 50);
  }
  else if (incomingByte == '6')
  {
    // volume
    colourWipe(hi_white, 10);
    colourWipe(off, 30);
  }
  else if (incomingByte == '7')
  {
    // volume wipe
    colourWipe(topaz, 10);
    colourWipe(off, 30);
  }
  else
  {
    // nothing
  }
}

// Fill the dots one after the other with a colour
void colourWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

