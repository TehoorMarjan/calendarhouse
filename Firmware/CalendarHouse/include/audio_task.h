#ifndef _AUDIO_TASK_H_
#define _AUDIO_TASK_H_

#include <Arduino.h>
#include "board.h"

#include "AudioFileSourceSD.h"
#include "AudioFileSourceBuffer.h"    //input buffer
#include "AudioGeneratorMP3.h"        //decoder
#include "AudioOutputI2S.h"           //output stream

class AudioTask {
public:
    AudioTask();
    ~AudioTask();
    void setup();
    void playDaily(uint8_t day);
    void playAlert(const char * name);
    void stop();
    bool isRunning();
    void loop();

private:
    AudioFileSourceSD _source;
    AudioGeneratorMP3 _decoder;
    //AudioFileSourceBuffer _bufferstream;
    AudioOutputI2S _out;
    //uint8_t _buffer[AUD_BUF_SIZE];
    char _filename[32];
    uint8_t _codecbuffer[AUD_CODEC_BUF_SIZE];
};

#endif
