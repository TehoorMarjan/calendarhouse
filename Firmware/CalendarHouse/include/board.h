/**
 * @file board.h
 * @brief This file lists all defines related to port assignment of functions specific to this board
 */

#ifndef BOARD_H
#define BOARD_H

#include <SPI.h>

// SD Card
#define SD_SPI              (HSPI)

#define PIN_SD_CS           (15)
#define PIN_SD_MISO         (12)
#define PIN_SD_MOSI         (13)
#define PIN_SD_CLK          (14)

// PWM LED Controller
#define CAL_LED_SPI         (VSPI)

#define PIN_CAL_LED_CS      (19)
#define PIN_CAL_LED_MOSI    (23)
#define PIN_CAL_LED_CLK     (18)
#define PIN_CAL_LED_EN      (35)

#endif
