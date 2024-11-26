#include "board.h"
#include "sd_card.h"
#include <SPI.h>

SDCardManager::SDCardManager() : _spi(HSPI), _sdfs(SD) {}

bool SDCardManager::begin() {
  _spi.begin(PIN_SD_CLK, PIN_SD_MISO, PIN_SD_MOSI, PIN_SD_CS);
  return _sdfs.begin(PIN_SD_CS, _spi);
}

bool SDCardManager::isCardPresent() const {
  return _sdfs.cardType() != CARD_NONE;
}

bool SDCardManager::createDirectory(const char *path) {
  return _sdfs.mkdir(path);
}

bool SDCardManager::removeDirectory(const char *path) {
  return _sdfs.rmdir(path);
}

bool SDCardManager::readFile(const char *path, String& content) {
  File file = _sdfs.open(path);
  if (!file) return false;
  content = file.readStringUntil('\0');
  file.close();
  return true;
}

bool SDCardManager::writeFile(const char *path, const char *message) {
  File file = _sdfs.open(path, FILE_WRITE);
  if (!file) return false;
  bool success = file.print(message);
  file.close();
  return success;
}

bool SDCardManager::appendFile(const char *path, const char *message) {
  File file = _sdfs.open(path, FILE_APPEND);
  if (!file) return false;
  bool success = file.print(message);
  file.close();
  return success;
}

bool SDCardManager::renameFile(const char *path1, const char *path2) {
  return _sdfs.rename(path1, path2);
}

bool SDCardManager::deleteFile(const char *path) {
  return _sdfs.remove(path);
}

uint64_t SDCardManager::cardSizeMB() const {
  return _sdfs.cardSize() / (1024 * 1024);
}

uint64_t SDCardManager::totalSpaceMB() const {
  return _sdfs.totalBytes() / (1024 * 1024);
}

uint64_t SDCardManager::usedSpaceMB() const
{
    return _sdfs.usedBytes() / (1024 * 1024);
}
