#pragma once

#include <GUI.hpp>
#include <SDL2/SDL.h>

class PlayerGUIClass : GUIClass {
  private:
    bool play = false;

    void eventHandling();
    void renderPlayerGUI();
  public:
    PlayerGUIClass(SDL_Renderer* renderer);

    void mainThread();
};

extern PlayerGUIClass PlayerGUI;
