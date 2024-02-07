#pragma once

#include <GUI/Music/MusicPlayerGUI.hpp>

class VideoPlayerGUIClass : MusicPlayerGUIClass {
  private:
    void eventHandling();
    void renderPlayerGUI();
};

extern VideoPlayerGUIClass VideoPlayerGUI;
