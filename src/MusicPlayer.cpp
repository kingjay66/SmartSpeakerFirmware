#include <MusicPlayer.hpp>

PlayerClass::PlayerClass()
  : stream(nullptr) {
}

bool PlayerClass::play() {
    if (stream == nullptr) {
        return false;
    }
    if (this->state == PLAYER_STATE_PAUSED) {
        this->state = PLAYER_STATE_PLAYING;
    }
    return true;
}

bool PlayerClass::play(PlayerStream* stream) {
    if (stream == nullptr) {
        return false;
    }
    this->stream = stream;
    this->state = PLAYER_STATE_PLAYING;
    return true;
}

bool PlayerClass::pause() {
    if (stream == nullptr) {
        return false;
    }
    if (state == PLAYER_STATE_PLAYING) {
        state = PLAYER_STATE_PAUSED;
        return true;
    }
    return false;
}

bool PlayerClass::stop() {
    if (stream == nullptr) {
        return false;
    }
    if (state == PLAYER_STATE_PLAYING || state == PLAYER_STATE_PAUSED) {
        state = PLAYER_STATE_NOT_PLAYING;
        return true;
    }
    return false;
}

bool PlayerClass::toggle() {
    if (stream == nullptr) {
        return false;
    }
    if (state == PLAYER_STATE_PLAYING) {
        return stop();
    }
    if (state == PLAYER_STATE_NOT_PLAYING || state == PLAYER_STATE_PAUSED) {
        return play();
    }
    return false;
}
