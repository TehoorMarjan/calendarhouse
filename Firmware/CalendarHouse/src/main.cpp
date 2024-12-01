
#include "board.h"
#include "sd_card.h"
#include "cal_led.h"
#include "audio_task.h"

SDCardManager sdCardManager;
CAL_LED cal_led;
AudioTask audioTask(sdCardManager);

uint8_t day = 5;

void setup() {
  
  Serial.begin(115200);
  sdCardManager.begin();
  cal_led.begin();

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
}

void loop() {

  if (!audioTask.isRunning()) {
    day+=1;
    if (day > 8) {
      Serial.println("Finished");
      while(1) {sleep(2000);}
    }
    audioTask.playDaily(day);

  }
  audioTask.loop();
}
