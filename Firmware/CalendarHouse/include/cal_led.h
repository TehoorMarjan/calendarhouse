/*!
 *  @file CAL_LED.h
 *
 * 	 TLC5947 24-Channel, 12-Bit PWM LED Driver
 *
 *  Written by Tehoor Marjan
 */

#ifndef _CAL_LED_H
#define _CAL_LED_H

#include <Arduino.h>
#include <SPI.h>
#include "board.h"

#define CAL_LED_BLOCK_SIZE (36) // nb of bytes: 24 channels * 12 bits / 8

/*!
 *    @brief  Class that stores state and functions for interacting with
 *            TLC5947 24-channel PWM/LED driver
 */
class CAL_LED {
public:
  CAL_LED();
  ~CAL_LED();

  void begin(void);

  void setPWM(uint16_t chan, uint16_t pwm);
  uint16_t getPWM(uint16_t chan);
  //void setLED(uint16_t lednum, uint16_t r, uint16_t g, uint16_t b);
  void write();

private:
  uint8_t _pwmbuffer[CAL_LED_BLOCK_SIZE * CAL_LED_NBCHAIN];
  uint8_t _pwmcommit[CAL_LED_BLOCK_SIZE * CAL_LED_NBCHAIN];
  SPIClass _spi;
  SPISettings _spi_settings;
};

#endif
