#pragma once

enum MediaPlayerSource {
    PLAYER_SOURCE_NONE,
    PLAYER_SOURCE_SDCARD,
    PLAYER_SOURCE_USB,
    PLAYER_SOURCE_BLUETOOTH,
    PLAYER_SOURCE_YOUTUBE,
};

enum MediaPlayerState {
    PLAYER_STATE_NOT_PLAYING,
    PLAYER_STATE_PLAYING,
    PLAYER_STATE_PAUSED,
    PLAYER_STATE_FAST_FORWARD,
    PLAYER_STATE_FAST_BACKWARD,
};

class MusicPlayerStream {
  public:
    MediaPlayerSource source = PLAYER_SOURCE_NONE;
};

class MusicPlayerClass {
  private:
    MediaPlayerState state = PLAYER_STATE_NOT_PLAYING;
    MusicPlayerStream* stream;

  public:

    MusicPlayerClass();
    MusicPlayerClass(const MusicPlayerClass&) = default;
    MusicPlayerClass(MusicPlayerClass&&) = delete;
    MusicPlayerClass& operator=(const MusicPlayerClass&) = default;
    MusicPlayerClass& operator=(MusicPlayerClass&&) = delete;
    ~MusicPlayerClass();

    MediaPlayerState getState();

    bool play();
    bool play(MusicPlayerStream* stream);

    bool pause();

    bool stop();

    bool toggle();

    bool prev();
    bool next();
};

extern MusicPlayerClass MP;
