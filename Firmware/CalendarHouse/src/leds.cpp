#include "leds.h"

LedController::LedController() :
    _activeLed(-1),
    _fadeDirection(1),
    _fadeValue(0)
    {}

void LedController::begin() {
    _calLed.begin();
}

void LedController::setActiveDay(uint8_t day) {
    if (day < 1 || day > 24) return;
    int8_t oldActiveLed = _activeLed;
    _activeLed = _ledMapping[day - 1];
    if (oldActiveLed != _activeLed) {
        _calLed.setPWM(oldActiveLed, 0);
        _calLed.write();
        _fadeValue = 0;
    }
}

void LedController::setOff() {
    if (_activeLed == -1) return;
    _calLed.setPWM(_activeLed, 0);
    _calLed.write();
    _activeLed = -1;
}

void LedController::loop() {
    if (_activeLed != -1) {
        _fadeValue += _fadeDirection * 33; 
        if (_fadeValue > 4095) {
            _fadeValue = 4095;
            _fadeDirection = -1;
        } else if (_fadeValue < 0) {
            _fadeValue = 0;
            _fadeDirection = 1;
        }
        _calLed.setPWM(_activeLed, _fadeValue);
        _calLed.write();
    }
}
