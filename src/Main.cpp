#include <NetworkService.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <User.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#ifdef FB_EN
    #define SDL_WINDOW_TYPE SDL_WINDOW_FULLSCREEN
#else
    #define SDL_WINDOW_TYPE SDL_WINDOW_OPENGL
#endif  // FB_EN

#define SCREEN_RADIUS 240

#define SCREEN_WIDTH SCREEN_RADIUS * 2
#define SCREEN_HEIGHT SCREEN_RADIUS * 2

const int WINDOW_WIDTH = 480;
const int WINDOW_HEIGHT = 480;
const int MAX_FONT_SIZE = 32;
const int MIN_FONT_SIZE = 12;
const int NUM_WORDS = 5;
const std::vector<std::string> words = {"Music", "Videos", "Equalizer", "Other", "Settings"};

int selectedWord = 0;  // Index of the currently selected word

// Function to initialize SDL and SDL_ttf
bool init(SDL_Window** window, SDL_Renderer** renderer, TTF_Font** font)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    *window = SDL_CreateWindow("Text Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if ((*window) == nullptr)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if ((*renderer) == nullptr)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(*window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    *font = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", MAX_FONT_SIZE);  // Replace with the path to your font file
    if ((*font) == nullptr)
    {
        std::cerr << "Failed to load font! TTF_Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(*renderer);
        SDL_DestroyWindow(*window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}

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

// Function to close SDL and SDL_ttf
void close(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font)
{
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

// Main function
int main()
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;

    if (!init(&window, &renderer, &font))
    {
        std::cerr << "Failed to initialize!" << std::endl;
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        // Event handling
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_UP:
                        if (selectedWord > 0) {
                            selectedWord--;
                        }
                        break;
                    case SDLK_DOWN:
                        if (selectedWord < NUM_WORDS - 1) {
                            selectedWord++;
                        }
                        break;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 155, 0, 255, 0xFF);
        drawCircle(renderer, 240, 240, 240);

        // Render text
        for (int i = 0; i < NUM_WORDS; ++i)
        {
            int distance = std::abs(i - selectedWord);
            double fontSize = MAX_FONT_SIZE - distance * (MAX_FONT_SIZE - MIN_FONT_SIZE) / (NUM_WORDS / 1.5);
            TTF_Font* tempFont = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/Ubuntu-B.ttf", static_cast<int>(fontSize));  // You should optimize this by caching font sizes
            SDL_Color textColor = {0, 0, 0, 0xFF};

            SDL_Surface* textSurface = TTF_RenderText_Solid(tempFont, words[i].c_str(), textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

            int textWidth = textSurface->w;
            int textHeight = textSurface->h;
            SDL_Rect renderQuad = {
                static_cast<int>((WINDOW_WIDTH - textWidth) / 2 - std::cos(i - selectedWord) * 60),
                (WINDOW_HEIGHT - textHeight) / 2 + (i - selectedWord) * 80,
                textWidth,
                textHeight};

            SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);

            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
            TTF_CloseFont(tempFont);
        }

        // Update screen
        SDL_RenderPresent(renderer);
    }

    close(window, renderer, font);
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
