
#include "board.h"
#include "sd_card.h"
#include "leds.h"
#include "audio_task.h"
#include <WiFiManager.h>
#include "time.h"

SDCardManager sdCardManager;
LedController ledController;
AudioTask audioTask(sdCardManager);
WiFiManager wifiManager;

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

void timeCheckTask( void * pvParameters );
void ledTask( void * pvParameters );

void setup() {
  
  Serial.begin(115200);
  sdCardManager.begin();
  ledController.begin();

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

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  xTaskCreatePinnedToCore(
    ledTask,                /* Task function. */
    "ledTask",              /* String with name of task. */
    10000,                  /* Stack size in words. */
    NULL,                   /* Parameter to pass to the task. */
    1,                      /* Task priority. */
    NULL,                   /* Task handle. */
    1);                     /* Core where the task should run. */

  xTaskCreatePinnedToCore(
    timeCheckTask,          /* Task function. */
    "timeCheckTask",        /* String with name of task. */
    10000,                  /* Stack size in words. */
    NULL,                   /* Parameter to pass to the task. */
    1,                      /* Task priority. */
    NULL,                   /* Task handle. */
    1);                     /* Core where the task should run. */
}

void timeCheckTask( void * pvParameters ){
  struct tm timeinfo;
  for(;;){
    if(!getLocalTime(&timeinfo)){
      Serial.println("Failed to obtain time");
    }
    else {
      ledController.setActiveDay(timeinfo.tm_wday);
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void ledTask( void * pvParameters ){
  for(;;){
    ledController.loop();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void loop() {
  audioTask.loop();
}
