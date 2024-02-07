#pragma once

#include <GUI/GUI.hpp>
#include <SDL2/SDL.h>

class MusicPlayerGUIClass : GUIClass {
  private:
    void eventHandling();
    void renderPlayerGUI();

  public:
    void mainThread(SDL_Renderer* renderer);
};

extern MusicPlayerGUIClass MusicPlayerGUI;
