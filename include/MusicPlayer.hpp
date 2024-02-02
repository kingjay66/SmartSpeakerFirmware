#pragma once

enum PlayerSource {
    PLAYER_SOURCE_NONE,
    PLAYER_SOURCE_SDCARD,
    PLAYER_SOURCE_USB,
    PLAYER_SOURCE_BLUETOOTH,
    PLAYER_SOURCE_YOUTUBE,
};

enum PlayerState {
    PLAYER_STATE_NOT_PLAYING,
    PLAYER_STATE_PLAYING,
    PLAYER_STATE_PAUSED,
    PLAYER_STATE_FAST_FORWARD,
    PLAYER_STATE_FAST_BACKWARD,
};

class PlayerStream {
public:
    PlayerSource source = PLAYER_SOURCE_NONE;
    
};

class PlayerClass {
  private:
    PlayerStream* stream;

  public:
    PlayerState state = PLAYER_STATE_NOT_PLAYING;

    PlayerClass();

    bool play();
    bool play(PlayerStream* stream);

    bool pause();

    bool stop();

    bool toggle();

};

extern PlayerClass Player;
