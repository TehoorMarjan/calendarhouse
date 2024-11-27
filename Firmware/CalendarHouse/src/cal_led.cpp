/*
 *  @file CAL_LED.cpp
 *
 * 	 TLC5947 24-Channel, 12-Bit PWM LED Driver
 *
 *  Written by Tehoor Marjan
 */

#include <SPI.h>
#include "CAL_LED.h"
#include "board.h"

CAL_LED::CAL_LED():
        _spi(CAL_LED_SPI),
        _spi_settings(CAL_LED_FREQ, MSBFIRST, SPI_MODE0) { }

/*!
 *    @brief  Setups the HW
 *    @return True if initialization was successful, otherwise false.
 */
void CAL_LED::begin() {
  _spi.begin(CAL_LED_PIN_CLK, -1, CAL_LED_PIN_MOSI, CAL_LED_PIN_CS);
  pinMode(_spi.pinSS(), OUTPUT);
}

/*!
 *    @brief  Releases allocated resources
 */

CAL_LED::~CAL_LED() { }

/*!
 *    @brief  Writes PWM data to the all connected TLC5947 boards
 */
void CAL_LED::write() {
  _spi.beginTransaction(_spi_settings);
  digitalWrite(_spi.pinSS(), LOW);
  // 24 channels per TLC5974
  // Call is blocking, buffer is replaced with "received" date (=0)
  (void) memcpy(&_pwmcommit[0], &_pwmbuffer[0], CAL_LED_BLOCK_SIZE * CAL_LED_NBCHAIN);
  _spi.transfer(_pwmcommit, CAL_LED_BLOCK_SIZE * CAL_LED_NBCHAIN);

  digitalWrite(_spi.pinSS(), HIGH);
  digitalWrite(_spi.pinSS(), LOW);
  _spi.endTransaction();
}

/*!
 *    @brief  Set the PWM channel / value
 *    @param  chan
 *            channel number ([0 - 23] on each board, so channel 2 for second
 * board will be 25)
 *    @param  pwm
 *            pwm value [0-4095]
 */
void CAL_LED::setPWM(uint16_t chan, uint16_t pwm) {
    if (chan >= 24 * CAL_LED_NBCHAIN) return;
    if (pwm > 0xFFF) pwm = 0xFFF;

    chan = (24 * CAL_LED_NBCHAIN - 1) - chan; // Reverse storing order

    size_t bit_pos = chan * 12;           // Position du premier bit dans le buffer
    size_t byte_index = bit_pos / 8;      // Index de l'octet dans le buffer
    size_t bit_offset = bit_pos % 8;      // Décalage en bits dans cet octet (0 ou 4)

    // Insérer les 12 bits dans le buffer
    // Insert high nibble or byte into lower part of first byte
    _pwmbuffer[byte_index] &= ~(0xFF >> bit_offset); // Clear
    _pwmbuffer[byte_index] |= (pwm >> (4 + bit_offset)) & 0xFF; // Write

    // Insert lower byte or nibble into higher part of second byte
    _pwmbuffer[byte_index + 1] &= ~(0xFF << (4 - bit_offset)); // Clear
    _pwmbuffer[byte_index + 1] |= (pwm << (4 - bit_offset)) & 0xFF; // Write
}

/*!
 *    @brief  Get the PWM value for channel.
 *    @param  chan
 *            channel number ([0 - 23] on each board, so channel 2 for second
 * board will be 25)
 *    @return PWM value ([0 - 4095]) for valid channels, 0xFFFF for non-existing
 * channels.
 */
uint16_t CAL_LED::getPWM(uint16_t chan) {
  if (chan >= 24 * CAL_LED_NBCHAIN) return 0xFFFF;

  chan = (24 * CAL_LED_NBCHAIN - 1) - chan; // Reverse storing order

  size_t index = (chan * 12) / 8; // Byte index in the array
  size_t offset = (chan % 2) * 4; // offset of 4 or 0, depending on odd/even

  // Temporary cast of 2 bytes to acces the two bytes together
  uint16_t *ptr = (uint16_t *)(&_pwmbuffer[index]);

  // Extract masked value
  return (*ptr >> offset) & 0xFFF;
}

/*!
 *    @brief  Set LED
 *    @param  lednum
 *            led number
 *    @param  r
 *            red value [0-255]
 *    @param  g
 *            green value [0-255]
 *    @param  b
 *            blue value [0-255]
 *//*
void CAL_LED::setLED(uint16_t lednum, uint16_t r, uint16_t g, uint16_t b) {
  setPWM(lednum * 3, r);
  setPWM(lednum * 3 + 1, g);
  setPWM(lednum * 3 + 2, b);
}
*/
