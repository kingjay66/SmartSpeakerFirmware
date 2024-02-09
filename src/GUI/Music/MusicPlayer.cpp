#include <GUI/Music/MusicPlayer.hpp>

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

MediaPlayerState MusicPlayerClass::getState() {
    return state;
}

bool MusicPlayerClass::play() {
#ifdef PRODUCTION
    if (stream == nullptr) {
        return false;
    }
#endif  // PRODUCTION
    if (this->state == PLAYER_STATE_PAUSED) {
        this->state = PLAYER_STATE_PLAYING;
    }
    return true;
}

bool MusicPlayerClass::play(MusicPlayerStream* stream) {
#ifdef PRODUCTION
    if (stream == nullptr) {
        return false;
    }
#endif  // PRODUCTION
    this->stream = stream;
    this->state = PLAYER_STATE_PLAYING;
    return true;
}

bool MusicPlayerClass::pause() {
#ifdef PRODUCTION
    if (stream == nullptr) {
        return false;
    }
#endif  // PRODUCTION
    if (state == PLAYER_STATE_PLAYING) {
        state = PLAYER_STATE_PAUSED;
        return true;
    }
    return false;
}

bool MusicPlayerClass::stop() {
#ifdef PRODUCTION
    if (stream == nullptr) {
        return false;
    }
#endif  // PRODUCTION
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

bool MusicPlayerClass::prev() {
    return false;
}

bool MusicPlayerClass::next() {
    return false;
}
