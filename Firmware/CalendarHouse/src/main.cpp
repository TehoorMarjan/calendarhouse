
#include "board.h"
#include "sd_card.h"

#include "Adafruit_TLC5947.h"

SDCardManager sdCardManager;

// How many boards do you have chained?
#define NUM_TLC5947 1

#define data   PIN_CAL_LED_MOSI
#define clock   PIN_CAL_LED_CLK
#define latch   PIN_CAL_LED_CS
#define oe  PIN_CAL_LED_EN  // set to -1 to not use the enable pin (its optional)

Adafruit_TLC5947 tlc = Adafruit_TLC5947(NUM_TLC5947, clock, data, latch);

void setup() {
  
  Serial.begin(115200);
  sdCardManager.begin();

  while (!Serial) {
    delay(10);
  }

  uint8_t cardType = SD.cardType();

  if (sdCardManager.isCardPresent()) {
    Serial.println("No SD card attached");
  }

  uint64_t cardSize = sdCardManager.cardSizeMB();
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  sdCardManager.writeFile("/hello.txt", "Hello World!\n");
  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
  
  Serial.println("TLC5947 test");
  tlc.begin();
  if (oe >= 0) {
    pinMode(oe, OUTPUT);
    digitalWrite(oe, LOW);
  }
}


// Fill the dots one after the other with a color
void colorWipe(uint16_t r, uint16_t g, uint16_t b, uint8_t wait) {
  for(uint16_t i=0; i<8*NUM_TLC5947; i++) {
      tlc.setLED(i, r, g, b);
      tlc.write();
      delay(wait);
  }
}

void loop() {
  colorWipe(4095, 0, 0, 100); // "Red" (depending on your LED wiring)
  delay(200);
  colorWipe(0, 4095, 0, 100); // "Green" (depending on your LED wiring)
  delay(200);
  colorWipe(0, 0, 4095, 100); // "Blue" (depending on your LED wiring)
  delay(200);
}