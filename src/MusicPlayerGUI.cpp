#include <MusicPlayerGUI.hpp>
#include <iostream>

PlayerGUIClass::PlayerGUIClass(SDL_Renderer* renderer) {
    this->renderer = renderer;
}

void PlayerGUIClass::eventHandling() {
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
                    break;
            }
        }
    }
}

void PlayerGUIClass::renderPlayerGUI() {

}

void PlayerGUIClass::mainThread() {
    while (!quit) {
        frameStart = SDL_GetTicks();

#ifdef TESTING
        eventHandling();
        std::cout << "PLAYER GUI SCREEN UPDATE" << '\n';
#endif  // TESTING

        double t = static_cast<double>(animationProgress) / static_cast<double>(ANIMATION_FRAMES);

// Clear screen
#ifdef TESTING
        setColor(color_black);
        SDL_RenderClear(renderer);

        setColor(color_purple);
        drawCircle(SCREEN_RADIUS, SCREEN_RADIUS, SCREEN_RADIUS);
#else   // PRODUCTION
        setColor(color_purple);
        SDL_RenderClear(renderer);
#endif  // TESTING
        

        animations();
        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_RenderPresent(renderer);
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
}
