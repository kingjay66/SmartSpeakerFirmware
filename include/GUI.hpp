#pragma once

#include <SDL2/SDL_ttf.h>
#include <array>
#include <string_view>

#ifndef PRODUCTION
    #define TESTING
#endif  // PRODUCTION

struct SDLColor {
    Uint8 red = 0;
    Uint8 green = 0;
    Uint8 blue = 0;
    Uint8 alpha = 255;
};

constexpr SDLColor color_red = {.red = 255};
constexpr SDLColor color_green = {.green = 255};
constexpr SDLColor color_blue = {.blue = 255};

constexpr SDLColor color_white = {.red = 255, .green = 255, .blue = 255};
constexpr SDLColor color_black = {};

constexpr SDLColor color_purple = {.red = 155, .blue = 255};

class GUIClass {
  private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;

    bool quit = false;

    Uint32 frameStart = 0;
    uint32_t frameTime = 0;

    bool needRedraw = true;

    int animationProgress = 0;
    int selectedWord = 0;
    int lastSelectedWord = 0;

    int musicMenuSelectedWord = 0;
    int lastMusicMenuSelectedWord = 0;

    int videoMenuSelectedWord = 0;
    int lastVideoMenuSelectedWord = 0;

    int eqMenuSelectedWord = 0;
    int lastEqMenuSelectedWord = 0;

    int otherMenuSelectedWord = 0;
    int lastOtherMenuSelectedWord = 0;

    int settingsMenuSelectedWord = 0;
    int lastSettingsMenuSelectedWord = 0;

    int lastMenuState = -1;
    int currentMenuState = -1;

    void setColor(SDLColor color);

    void drawCircle(int32_t centerX, int32_t centerY, int32_t radius);

#ifdef TESTING
    void eventHandling();
#endif  // TESTING

    template<unsigned int i>
    void renderSubMenu(std::array<std::string_view, i> array, double t);

    void renderMainMenu(double t);

    void animations();

  public:
    void init();
    void mainThread();
    void close();
};

extern GUIClass GUI;
