#pragma once

#include <SDL2/SDL_ttf.h>

struct SDLColor
{
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

class GUIClass
{
  private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;

    void setColor(SDLColor color);

    void drawCircle(int32_t centerX, int32_t centerY, int32_t radius);

  public:
    void init();
    void mainThread();
    void close();
};

extern GUIClass GUI;
