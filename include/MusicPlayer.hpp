#pragma once

enum MusicPlayerSource {
    PLAYER_SOURCE_NONE,
    PLAYER_SOURCE_SDCARD,
    PLAYER_SOURCE_USB,
    PLAYER_SOURCE_BLUETOOTH,
    PLAYER_SOURCE_YOUTUBE,
};

enum MusicPlayerState {
    PLAYER_STATE_NOT_PLAYING,
    PLAYER_STATE_PLAYING,
    PLAYER_STATE_PAUSED,
    PLAYER_STATE_FAST_FORWARD,
    PLAYER_STATE_FAST_BACKWARD,
};

class MusicPlayerStream {
  public:
    MusicPlayerSource source = PLAYER_SOURCE_NONE;
};

class MusicPlayerClass {
  private:
    MusicPlayerStream* stream;
    MusicPlayerState state = PLAYER_STATE_NOT_PLAYING;

  public:

    MusicPlayerClass();
    MusicPlayerClass(const MusicPlayerClass&) = default;
    MusicPlayerClass(MusicPlayerClass&&) = delete;
    MusicPlayerClass& operator=(const MusicPlayerClass&) = default;
    MusicPlayerClass& operator=(MusicPlayerClass&&) = delete;
    ~MusicPlayerClass();

    MusicPlayerState getState();

    bool play();
    bool play(MusicPlayerStream* stream);

    bool pause();

    bool stop();

    bool toggle();
};

extern MusicPlayerClass MP;
