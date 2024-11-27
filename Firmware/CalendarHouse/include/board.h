/**
 * @file board.h
 * @brief This file lists all defines related to port assignment of functions specific to this board
 */

#ifndef BOARD_H
#define BOARD_H

#include <SPI.h>

// SD Card
#define SD_SPI              (HSPI)

#define SD_PIN_CS           (15)
#define SD_PIN_MISO         (12)
#define SD_PIN_MOSI         (13)
#define SD_PIN_CLK          (14)

// PWM LED Controller
#define CAL_LED_SPI         (VSPI)
#define CAL_LED_FREQ        (30000000) // Use 15000000 if chaining modules
#define CAL_LED_NBCHAIN     (1)

#define CAL_LED_PIN_CS      (19)
#define CAL_LED_PIN_MOSI    (23)
#define CAL_LED_PIN_CLK     (18)
#define CAL_LED_PIN_EN      (-1)

// Audio
#define AUD_FS_BUF_SIZE     (20*1024)
#define AUD_CODEC_BUF_SIZE  (20*0x600)

#endif
