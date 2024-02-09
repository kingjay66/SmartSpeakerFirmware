#include <GUI/Music/MusicPlayer.hpp>
#include <GUI/Music/MusicPlayerGUI.hpp>
#include <iostream>

#define PLAY_BTN_WIDTH 40
#define PLAY_BTN_HEIGHT 40

MusicPlayerGUIClass MusicPlayerGUI = MusicPlayerGUIClass();

void MusicPlayerGUIClass::eventHandling() {
    if (animationProgress > 0) {
        return;
    }
    SDL_Event e;
    if (SDL_WaitEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_p:
                    MP.toggle();
                    needRedraw = true;
                    animationProgress = 1;
                    break;
            }
        }
    }
}

void MusicPlayerGUIClass::renderPlayerGUI() {
    double playButtonPosX = static_cast<double>(WINDOW_WIDTH) / 2;
    double playButtonPosY = static_cast<double>(WINDOW_HEIGHT) / 2;
    setColor(color_black);
    if (MP.getState() == PLAYER_STATE_PLAYING) {
        // PAUSE BUTTON
        double x1 = playButtonPosX - PLAY_BTN_WIDTH / 2.0;
        SDL_Rect rect = {
            .x = static_cast<int>(x1),
            .y = static_cast<int>(playButtonPosY),
            .w = PLAY_BTN_WIDTH / 2,
            .h = PLAY_BTN_HEIGHT};
        SDL_RenderDrawRect(renderer, &rect);
        x1 = playButtonPosX + PLAY_BTN_WIDTH / 2.0;
        rect.x = static_cast<int>(x1);
        SDL_RenderDrawRect(renderer, &rect);
    } else {
        // PLAY BUTTON
        double x1 = playButtonPosX - PLAY_BTN_WIDTH / 2.0;
        double y1 = playButtonPosY - PLAY_BTN_HEIGHT / 2.0;
        double x2 = playButtonPosX + PLAY_BTN_WIDTH / 2.0;
        double y2 = playButtonPosY;
        double x3 = x1;
        double y3 = playButtonPosY + PLAY_BTN_HEIGHT / 2.0;
        SDL_RenderDrawLine(renderer, static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));
        SDL_RenderDrawLine(renderer, static_cast<int>(x2), static_cast<int>(y2), static_cast<int>(x3), static_cast<int>(y3));
        SDL_RenderDrawLine(renderer, static_cast<int>(x3), static_cast<int>(y3), static_cast<int>(x1), static_cast<int>(y1));
    }
}

void MusicPlayerGUIClass::mainThread(SDL_Renderer* renderer) {
    if (this->renderer == nullptr) {
        this->renderer = renderer;
    }
    needRedraw = true;
    animationProgress = 1;
    quit = false;
    while (!quit) {
        frameStart = SDL_GetTicks();

#ifdef TESTING
        eventHandling();
        std::cout << "PLAYER GUI SCREEN UPDATE" << '\n';
#endif  // TESTING

        double t = static_cast<double>(animationProgress) / static_cast<double>(ANIMATION_FRAMES);

        clearScreen();

        renderPlayerGUI();
        
        animations();
        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_RenderPresent(renderer);
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
}
