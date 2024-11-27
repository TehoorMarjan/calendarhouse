
#include "board.h"
#include "sd_card.h"
#include "cal_led.h"
#include "audio_task.h"

SDCardManager sdCardManager;
CAL_LED cal_led;
AudioTask audioTask;

int16_t l0 = 0;
int16_t l2 = 1365;
int16_t l1 = 2730;
int16_t inc0 = 123;
int16_t inc2 = 51;
int16_t inc1 = 237;

void setup() {
  
  Serial.begin(115200);
  sdCardManager.begin();
  cal_led.begin();

  audioLogger = &Serial;

  while (!Serial) {
    delay(10);
  }

  if (!sdCardManager.isCardPresent()) {
    Serial.println("No SD card attached");
  }
  else {
    Serial.printf("SD Card Size: %lluMB\n", sdCardManager.cardSizeMB());
    Serial.printf("Total space: %lluMB\n", sdCardManager.totalSpaceMB());
    Serial.printf("Used space: %lluMB\n", sdCardManager.usedSpaceMB());
  }

  audioTask.playDaily(8);
  
  Serial.println("TLC5947 test");
}

void loop() {
  //l0 += inc0;
  //l1 += inc1;
  //l2 += inc2;
//
  //if (l0 > 0xFFF) { l0 = 0xFFF; inc0 = -inc0; } else if (l0 < 0) { l0 = 0; inc0 = -inc0; }
  //if (l1 > 0xFFF) { l1 = 0xFFF; inc1 = -inc1; } else if (l1 < 0) { l1 = 0; inc1 = -inc1; }
  //if (l2 > 0xFFF) { l2 = 0xFFF; inc2 = -inc2; } else if (l2 < 0) { l2 = 0; inc2 = -inc2; }
//
  //cal_led.setPWM(0, l0);
  //cal_led.setPWM(1, l1);
  //cal_led.setPWM(2, l2);
  //cal_led.write();
  audioTask.loop();
  //delay(5);
}
