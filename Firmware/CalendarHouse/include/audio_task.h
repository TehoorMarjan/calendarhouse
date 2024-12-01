#ifndef _AUDIO_TASK_H_
#define _AUDIO_TASK_H_

#include <Arduino.h>
#include "board.h"
#include "sd_card.h"

#include "Audio.h"
#include "SD.h"
#include "FS.h"

class AudioTask {
public:
    AudioTask(SDCardManager &sdCardManager);
    ~AudioTask();
    void playDaily(uint8_t day);
    void playAlert(const char * name);
    void stop();
    bool isRunning();
    void loop();

private:
    Audio _audio;
    SDCardManager& _sdCardManager;
    char _filename[32];
};

#endif
