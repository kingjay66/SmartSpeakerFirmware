#pragma once

#include <SDL2/SDL_ttf.h>
#include <array>
#include <string_view>

#ifndef PRODUCTION
    #define TESTING
#endif  // PRODUCTION

#define SCREEN_RADIUS 240

#define WINDOW_WIDTH SCREEN_RADIUS * 2
#define WINDOW_HEIGHT SCREEN_RADIUS * 2

#ifdef FB_EN
    #define SDL_WINDOW_TYPE SDL_WINDOW_FULLSCREEN
#else
    #define SDL_WINDOW_TYPE SDL_WINDOW_OPENGL
#endif  // FB_EN

#ifndef MAX_FONT_SIZE
    #define MAX_FONT_SIZE 32
#endif  // MAX_FONT_SIZE

#ifndef MIN_FONT_SIZE
    #define MIN_FONT_SIZE 12
#endif  // MIN_FONT_SIZE

#if MAX_FONT_SIZE < MIN_FONT_SIZE
    #error MAX_FONT_SIZE has to be greater than MIN_FONT_SIZE
#endif  // MAX_FONT_SIZE < MIN_FONT_SIZE

#ifndef FONT_PATH
    #define FONT_PATH "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf"
#endif  // FONT_PATH

#ifndef FPS
    #define FPS 60.0
#endif  // FPS

#define FRAME_DELAY 1000.0 / FPS

#define ANIMATION_FRAMES FPS / 6.0

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
  protected:
    SDL_Renderer* renderer = nullptr;

    bool quit = false;

    Uint32 frameStart = 0;
    uint32_t frameTime = 0;

    bool needRedraw = true;

    int animationProgress = 0;

    void setColor(SDLColor color);

    void drawCircle(int32_t centerX, int32_t centerY, int32_t radius);

    void animations();

  private:
    SDL_Window* window = nullptr;
    TTF_Font* font = nullptr;

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

#ifdef TESTING
    void eventHandling();
#endif  // TESTING

    template<unsigned int i>
    void renderSubMenu(std::array<std::string_view, i> array, double t);

    void renderMainMenu(double t);

  public:
    void init();
    void mainThread();
    void close();
};

extern GUIClass GUI;
