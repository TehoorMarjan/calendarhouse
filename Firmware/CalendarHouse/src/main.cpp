
#include "board.h"
#include "sd_card.h"
#include "cal_led.h"
#include "audio_task.h"
#include <WiFiManager.h>

SDCardManager sdCardManager;
CAL_LED cal_led;
AudioTask audioTask(sdCardManager);
WiFiManager wifiManager;

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

  wifiManager.setHostname("calendarhouse");
  wifiManager.setWiFiAutoReconnect(true);
  wifiManager.autoConnect("CalendarHouse");

  Serial.println("Connected to WiFi");
}

void loop() {
  audioTask.loop();
}
