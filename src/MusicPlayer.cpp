#include <MusicPlayer.hpp>

#ifndef PRODUCTION
    #define TESTING
#endif  // PRODUCTION

MusicPlayerClass MP = MusicPlayerClass();

MusicPlayerClass::MusicPlayerClass()
  : stream(nullptr) {
}

MusicPlayerClass::~MusicPlayerClass() {
    delete stream;
}

MusicPlayerState MusicPlayerClass::getState() {
    return state;
}

bool MusicPlayerClass::play() {
    if (stream == nullptr) {
        return false;
    }
    if (this->state == PLAYER_STATE_PAUSED) {
        this->state = PLAYER_STATE_PLAYING;
    }
    return true;
}

bool MusicPlayerClass::play(MusicPlayerStream* stream) {
    if (stream == nullptr) {
        return false;
    }
    this->stream = stream;
    this->state = PLAYER_STATE_PLAYING;
    return true;
}

bool MusicPlayerClass::pause() {
    if (stream == nullptr) {
        return false;
    }
    if (state == PLAYER_STATE_PLAYING) {
        state = PLAYER_STATE_PAUSED;
        return true;
    }
    return false;
}

bool MusicPlayerClass::stop() {
    if (stream == nullptr) {
        return false;
    }
    if (state == PLAYER_STATE_PLAYING || state == PLAYER_STATE_PAUSED) {
        state = PLAYER_STATE_NOT_PLAYING;
        return true;
    }
    return false;
}

bool MusicPlayerClass::toggle() {
#ifdef PRODUCTION
    if (state == PLAYER_STATE_NOT_PLAYING) {
        return play();
    }
#endif  // PRODUCTION
    if (state == PLAYER_STATE_PLAYING) {
        state = PLAYER_STATE_PAUSED;
        return true;
    }
    state = PLAYER_STATE_PLAYING;
    return true;
}
