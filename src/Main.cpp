#include <NetworkService.hpp>
#include <SDL2/SDL.h>
#include <User.hpp>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#ifdef FB_EN
    #define SDL_WINDOW_TYPE SDL_WINDOW_FULLSCREEN
#else
    #define SDL_WINDOW_TYPE SDL_WINDOW_OPENGL
#endif  // FB_EN

#define SCREEN_RADIUS 240

#define SCREEN_WIDTH SCREEN_RADIUS * 2
#define SCREEN_HEIGHT SCREEN_RADIUS * 2

int sdl_test()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        //SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return EXIT_FAILURE;
    }

#ifdef FB_EN
    SDL_setenv("SDL_VIDEDRIVER", "directfb", 1);
#endif  // FB_EN

    SDL_Window* window =
        SDL_CreateWindow("SDL_FB_EXAMPLE", 0, 0, 480, 480, SDL_WINDOW_TYPE);
    if (window == nullptr)
    {
        //SDL_Log("Unable to create window: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr)
    {
        //SDL_Log("Unable to create renderer: %s", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}

void rest_api_test()
{
    AuthRequest req = {.username = "tim", .password = "password"};
    NetworkService.authLogin(req, [](RequestError* err, AuthResponse& response) {
        if (err != nullptr)
        {
            std::cerr << err->error << std::endl;
            return;
        }
        std::cout << response.token << std::endl;
    });
}

int main()
{
    rest_api_test();
    //return sdl_test();
}
