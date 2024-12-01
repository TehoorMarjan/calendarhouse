#include "cal_led.h"

class LedController {
public:
  LedController();

  void begin();
  void setActiveDay(uint8_t day);
  void setOff();
  void loop();

private:
  CAL_LED _calLed;
  int8_t _activeLed;
  int16_t _fadeValue;
  int8_t _fadeDirection;
  const uint8_t _ledMapping[24] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
};
