/**
 * @file sd_card.h
 * @brief This file encapsulates generic access to the SD Card connected to the ESP32.
 */

#ifndef SD_CARD_MANAGER_H
#define SD_CARD_MANAGER_H

#include "FS.h"
#include "SD.h"
#include "SPI.h"

class SDCardManager {
public:
    SDCardManager();

    bool begin();

    bool isCardPresent() const;

    bool createDirectory(const char *path);

    bool removeDirectory(const char *path);

    bool readFile(const char *path, String& content); // Return content via String& for efficiency

    bool writeFile(const char *path, const char *message);

    bool appendFile(const char *path, const char *message);

    bool renameFile(const char *path1, const char *path2);

    bool deleteFile(const char *path);

    uint64_t cardSizeMB() const;

    uint64_t totalSpaceMB() const;

    uint64_t usedSpaceMB() const;

private:
    SPIClass _spi;
    SDFS &_sdfs;
};

#endif
