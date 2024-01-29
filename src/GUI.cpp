#include <GUI.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <array>
#include <iostream>

#define SCREEN_RADIUS 240

#define WINDOW_WIDTH SCREEN_RADIUS * 2
#define WINDOW_HEIGHT SCREEN_RADIUS * 2

#ifdef FB_EN
    #define SDL_WINDOW_TYPE SDL_WINDOW_FULLSCREEN
#else
    #define SDL_WINDOW_TYPE SDL_WINDOW_OPENGL
#endif  // FB_EN

#define MAX_FONT_SIZE 32
#define MIN_FONT_SIZE 12

#ifndef FONT_PATH
    #define FONT_PATH "/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf"
#endif  // FONT_PATH

#ifndef FPS
    #define FPS 60
#endif  // FPS

#define FRAME_DELAY 1000 / FPS

#define ANIMATION_FRAMES FPS / 6.0

constexpr std::array<std::string_view, 5> menuItems = {"Music", "Videos", "Equalizer", "Other", "Settings"};

GUIClass GUI = GUIClass();

double lerp(double start, double end, double t) {
    return start + t * (end - start);
}

void GUIClass::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << '\n';
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow("Text Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    font = TTF_OpenFont(FONT_PATH, MAX_FONT_SIZE);
    if (font == nullptr) {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << '\n';
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

#ifdef PRODUCTION
    setColor(color_purple);
    SDL_RenderClear(renderer);
#else   // TESTING
    setColor(color_black);
    SDL_RenderClear(renderer);
    setColor(color_purple);
    drawCircle(SCREEN_RADIUS, SCREEN_RADIUS, SCREEN_RADIUS);
#endif  // PRODUCTION
}

void GUIClass::mainThread() {
    bool quit = false;
    SDL_Event e;

    Uint32 frameStart = 0;
    uint32_t frameTime = 0;

    bool needRedraw = true;

    int animationProgress = 0;
    int selectedWord = 0;
    int lastSelectedWord = 0;

    while (!quit) {
        frameStart = SDL_GetTicks();
        // Event handling
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        needRedraw = true;
                        lastSelectedWord = selectedWord;
                        if (selectedWord > 0) {
                            selectedWord--;
                        }
                        animationProgress = 1;
                        break;
                    case SDLK_DOWN:
                        needRedraw = true;
                        lastSelectedWord = selectedWord;
                        if (selectedWord < menuItems.size() - 1) {
                            selectedWord++;
                        }
                        animationProgress = 1;
                        break;
                }
            }
        }
        double t = static_cast<double>(animationProgress) / static_cast<double>(ANIMATION_FRAMES);

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 155, 0, 255, 0xFF);
        drawCircle(240, 240, 240);

        for (int i = 0; i < menuItems.size(); ++i) {
            int lastDistance = std::abs(i - lastSelectedWord);
            int currentDistance = std::abs(i - selectedWord);

            double lastFontSize = MAX_FONT_SIZE - lastDistance * (MAX_FONT_SIZE - MIN_FONT_SIZE) / (menuItems.size() / 1.5);
            double currentFontSize = MAX_FONT_SIZE - currentDistance * (MAX_FONT_SIZE - MIN_FONT_SIZE) / (menuItems.size() / 1.5);

            double fontSize = lerp(lastFontSize, currentFontSize, t);
            TTF_Font* tempFont = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", static_cast<int>(fontSize));

            SDL_Color textColor = {0, 0, 0, 0xFF};
            SDL_Surface* textSurface = TTF_RenderText_Solid(tempFont, menuItems[i].data(), textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            int textWidth = textSurface->w;
            int textHeight = textSurface->h;

            double lastX = static_cast<double>(WINDOW_WIDTH - textWidth) / 2 - std::cos(lastDistance) * 60 + 50;
            double currentX = static_cast<double>(WINDOW_WIDTH - textWidth) / 2 - std::cos(currentDistance) * 60 + 50;
            double xPosition = lerp(lastX, currentX, t);

            double lastY = static_cast<double>(WINDOW_HEIGHT - textHeight) / 2 + (i - lastSelectedWord) * 80;
            double currentY = static_cast<double>(WINDOW_HEIGHT - textHeight) / 2 + (i - selectedWord) * 80;
            double yPosition = lerp(lastY, currentY, t);

            SDL_Rect renderQuad = {
                static_cast<int>(xPosition),
                static_cast<int>(yPosition),
                textWidth,
                textHeight};

            SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);

            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
            TTF_CloseFont(tempFont);
        }

        if (animationProgress > 0 && animationProgress <= ANIMATION_FRAMES) {
            animationProgress++;
        } else if (animationProgress > ANIMATION_FRAMES) {
            lastSelectedWord = selectedWord;
            animationProgress = 0;
            needRedraw = false;
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            if (needRedraw) {
                SDL_RenderPresent(renderer);
            }
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
}

void GUIClass::close() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void GUIClass::setColor(SDLColor color) {
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
}

void GUIClass::drawCircle(int32_t centerX, int32_t centerY, int32_t radius) {
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y) {
        for (int i = centerX - x; i <= centerX + x; i++) {
            SDL_RenderDrawPoint(renderer, i, centerY + y);
            SDL_RenderDrawPoint(renderer, i, centerY - y);
        }
        for (int i = centerX - y; i <= centerX + y; i++) {
            SDL_RenderDrawPoint(renderer, i, centerY + x);
            SDL_RenderDrawPoint(renderer, i, centerY - x);
        }

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}
