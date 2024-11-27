
#include "audio_task.h"

AudioTask::AudioTask():
        _source(),
        _decoder(&_codecbuffer, AUD_CODEC_BUF_SIZE),
        _pfsbuff(NULL),
        _out(0, AudioOutputI2S::INTERNAL_DAC) { }

AudioTask::~AudioTask() {
    stop();
}

void AudioTask::setup() { }

void AudioTask::playDaily(uint8_t day) {
    stop();
    (void) sprintf(&_filename[0], "/daily/%d.mp3", day);
    if (_source.open(_filename)) {
        _pfsbuff = new AudioFileSourceBuffer(&_source, &_buffer, AUD_FS_BUF_SIZE),
        _decoder.begin(_pfsbuff, &_out);
        Serial.printf("Playing %s\n", _filename);
    }
    else {
        Serial.printf("Failed to open %s\n", _filename);
    }
}

void AudioTask::stop() {
    if (_decoder.isRunning()) {
        _decoder.stop();
    }
    if (_source.isOpen()) {
        _source.close();
    }
    if (_pfsbuff != NULL) {
        delete _pfsbuff;
        _pfsbuff = NULL;
    }
    Serial.println("Stopped");
}

void AudioTask::playAlert(const char * name) {
    stop();
    (void) sprintf(&_filename[0], "/alert/%s.mp3", name);
    if (_source.open(_filename)) {
        _decoder.begin(&_source, &_out);
    }
}

bool AudioTask::isRunning() {
    return _decoder.isRunning();
}

void AudioTask::loop() {
    if (_decoder.isRunning()) {
        bool dataLeft = _decoder.loop();
        if (!dataLeft) {
            stop();
        }
    }
}

