#include <NetworkService.hpp>
#include <SDL2/SDL.h>
#include <User.hpp>
#include <cstdlib>
#include <iostream>
#include <thread>

#ifdef FB_EN
    #define SDL_WINDOW_TYPE SDL_WINDOW_FULLSCREEN
#else
    #define SDL_WINDOW_TYPE SDL_WINDOW_OPENGL
#endif  // FB_EN

#define SCREEN_RADIUS 240

#define SCREEN_WIDTH SCREEN_RADIUS * 2
#define SCREEN_HEIGHT SCREEN_RADIUS * 2

void drawCircle(SDL_Renderer* renderer, int32_t centerX, int32_t centerY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        // Draw horizontal lines from the left to the right of the circle
        for (int i = centerX - x; i <= centerX + x; i++)
        {
            SDL_RenderDrawPoint(renderer, i, centerY + y);
            SDL_RenderDrawPoint(renderer, i, centerY - y);
        }
        for (int i = centerX - y; i <= centerX + y; i++)
        {
            SDL_RenderDrawPoint(renderer, i, centerY + x);
            SDL_RenderDrawPoint(renderer, i, centerY - x);
        }

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

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

    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                quit = true;  // Exit on any key press
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // Draw and fill circle with blue color
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);  // Blue color
        drawCircle(renderer, 240, 240, 240);                       // Circle with radius 240

        // Update screen
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

int rest_api_test()
{
    AuthRequest req = {
        .username = "tim",
        .email = "email",
        .password = "password",
    };
    NetworkService.authRegister(req, [=](RequestError err, AuthResponse& response) {
        if (err != REQUEST_ERR_OK)
        {
            std::cerr << err << '\n';
            return;
        }
        std::cout << response.token << '\n';
    });
    std::this_thread::sleep_for(std::chrono::seconds(3));
    NetworkService.authLogin(req, [=](RequestError err, AuthResponse& response) {
        if (err != REQUEST_ERR_OK)
        {
            std::cerr << err << '\n';
            return;
        }
        std::cout << response.token << '\n';
    });
    std::this_thread::sleep_for(std::chrono::seconds(3));
    User user;
    NetworkService.userGetCurrentUserInfo(user, [=](RequestError err, User& user) {
        if (err != REQUEST_ERR_OK)
        {
            std::cerr << err << '\n';
            return;
        }
        std::cout << user.id << '\n';
    });
    while (true)
    {};
    return EXIT_SUCCESS;
}

int main()
{
    //rest_api_test();
    return sdl_test();
}
