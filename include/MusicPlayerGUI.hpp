#pragma once

#include <GUI.hpp>
#include <SDL2/SDL.h>

class PlayerGUIClass : GUIClass {
  private:
    bool play = false;

    void eventHandling();
    void renderPlayerGUI();
  public:

    void mainThread(SDL_Renderer* renderer);
};

extern PlayerGUIClass PlayerGUI;
