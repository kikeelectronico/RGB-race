#include <Adafruit_NeoPixel.h>

#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(148, PIN, NEO_GRB + NEO_KHZ800);

const int players = 3;
const int playerPin[players] = {0,1,2};
int playerControl[players] = {0,0,0};
long int playerSpeed[players] = {0,0,0};
unsigned int playerPosition[players] = {0,0,0};
unsigned int last[players] = {0,0,0};
uint32_t playerColor[players];

void setup() {

  playerColor[0] = strip.Color(127, 0, 0);
  playerColor[1] = strip.Color(0, 127, 0);
  playerColor[2] = strip.Color(0, 0, 127);
  
  strip.begin();
  strip.setBrightness(50);
  strip.show();
}

void loop() {
  
  for ( int i = 0; i < players; i++){
    playerControl[i] = analogRead(playerPin[i]);
    playerSpeed[i] = map(playerControl[i], 0, 1023, 500, 1);
    if (millis() - last[i] > playerSpeed[i]){
      if (playerControl[i] > 100){
        playerPosition[i]++;
        last[i] = millis();
      }

     if (playerPosition[i] >= strip.numPixels())
     {
      colorWipe(playerColor[i], 10);
      colorWipe(strip.Color(0, 0, 0), 10);
      for ( int j = 0; j < players; j++)
        playerPosition[j] = 0;
      break;
     }
    }

    
  }

  for ( int i = 0; i < players; i++){
    strip.setPixelColor(playerPosition[i], playerColor[i]);
    strip.setPixelColor(playerPosition[i]-1, strip.Color(0, 0, 0));
  }
  strip.show();
  
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i< strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

