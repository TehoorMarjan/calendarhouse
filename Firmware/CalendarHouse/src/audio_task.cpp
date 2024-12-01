
#include "audio_task.h"

AudioTask::AudioTask(SDCardManager &sdCardManager):
        _audio(), _sdCardManager(sdCardManager) {
    _audio.setPinout(I2S_PIN_BCLK, I2S_PIN_LRC, I2S_PIN_DOUT);
    _audio.setVolume(17); // default 0...21
}

AudioTask::~AudioTask() {
    stop();
}

void AudioTask::playDaily(uint8_t day) {
    stop();
    (void) sprintf(&_filename[0], "/daily/%d.mp3", day);
    
    if (_audio.connecttoFS(_sdCardManager.getSDFS(), _filename)) {
        Serial.printf("Playing %s\n", _filename);
    }
    else {
        Serial.printf("Failed to open %s\n", _filename);
    }
}

void AudioTask::stop() {
    _audio.stopSong();
    Serial.println("Stopped ;)");
}

void AudioTask::playAlert(const char * name) {
    stop();
    (void) sprintf(&_filename[0], "/alert/%s.mp3", name);
    if (_audio.connecttoFS(_sdCardManager.getSDFS(), _filename)) {
        Serial.printf("Playing %s\n", _filename);
    }
    else {
        Serial.printf("Failed to open %s\n", _filename);
    }
}

bool AudioTask::isRunning() {
    return _audio.isRunning();
}

void AudioTask::loop() {
    _audio.loop();
}
