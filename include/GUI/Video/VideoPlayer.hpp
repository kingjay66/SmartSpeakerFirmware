#pragma once

#include <GUI/Music/MusicPlayer.hpp>

class VideoPlayerStream {
    // TODO(jayadamsmorgan): Video stream impl
  public:
    MediaPlayerSource source = PLAYER_SOURCE_NONE;
};

class VideoPlayerClass : MusicPlayerClass {
  private:
    MediaPlayerState state = PLAYER_STATE_NOT_PLAYING;
    VideoPlayerStream* stream;
};
