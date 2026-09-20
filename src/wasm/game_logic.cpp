#ifdef EMSCRIPTEN
#include <emscripten/emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <array>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>

#include "box.hpp"

static constexpr int boardSize = 4;
static std::array<std::array<Box, boardSize>, boardSize> board;
static int boxesIteratedCount = 0;
static bool canCreateNewBox = false;
static int keyXMove = 0;
static int keyYMove = 0;

static unsigned int frameDuration = 16;
static unsigned int startTime = 0;
static unsigned int delta = 0;

static constexpr int boxSize = 100;
static constexpr int boardScale = 100;

extern "C" {

EMSCRIPTEN_KEEPALIVE
int getRandomCoordinate()
{
    #ifdef EMSCRIPTEN
    return emscripten_random() * 4;
    #else
    return rand() % 4;
    #endif
}

EMSCRIPTEN_KEEPALIVE
bool isOutbounds(int x, int y)
{
    return x >= boardSize || x < 0 || y >= boardSize || y < 0;
}

EMSCRIPTEN_KEEPALIVE
bool isBoxEmpty(int x, int y)
{
    return board[y][x].isValid == false;
}

EMSCRIPTEN_KEEPALIVE
bool isBoxMergable(int x, int y, int number)
{
    if (isOutbounds(x, y) || isBoxEmpty(x, y))
    {
        return false;
    }

    return board[y][x].number == number && board[y][x].deleteAfterMerge == false;
}

EMSCRIPTEN_KEEPALIVE
bool isAnyBoxMoving()
{
    // double any_of
    for (const auto& row : board)
    {
        for (const auto& box : row)
        {
            if (box.isValid && box.isMoving)
            {
                return true;
            }
        }
    }

    return false;
}

EMSCRIPTEN_KEEPALIVE
void setKeyMove(int x, int y)
{
    keyXMove = x;
    keyYMove = y;
}

EMSCRIPTEN_KEEPALIVE
int iterateBox(int x, int xNext, int y, int yNext)
{
    if (isOutbounds(x, y) || isBoxEmpty(x, y))
    {
        return 0;
    }

    if (board[y][x].deleteAfterMerge)
    {
        board[y][x].isValid = false;
        return 1;
    }

    if (isBoxEmpty(xNext, yNext))
    {
        board[yNext][xNext] = board[y][x];
        board[yNext][xNext].setLocation(xNext, yNext);
        board[y][x].isValid = false;

        return 1;
    }
    else if (isBoxMergable(xNext, yNext, board[y][x].number))
    {
        board[y][x].setLocation(xNext, yNext);
        board[y][x].deleteAfterMerge = true;
        board[yNext][xNext].merge();

        return 1;
    }

    return 0;
}

EMSCRIPTEN_KEEPALIVE
int iterateRow(int y, int direction)
{
    int moveCount = 0;

    if (direction > 0)
    {
        for (int x = board.size() - 2; x >= 0; x--)
        {
            moveCount += iterateBox(x, x + 1, y, y);
        }
    }
    else if (direction < 0)
    {
        for (int x = 1; x < board.size(); x++)
        {
            moveCount += iterateBox(x, x - 1, y, y);
        }   
    }

    return moveCount;
}

EMSCRIPTEN_KEEPALIVE
int iterateColumn(int x, int direction)
{
    int moveCount = 0;

    if (direction > 0)
    {
        for (int y = board.size() - 2; y >= 0; y--)
        {
            moveCount += iterateBox(x, x, y, y + 1);
        }
    }
    else if (direction < 0)
    {
        for (int y = 1; y < board.size(); y++)
        {
            moveCount += iterateBox(x, x, y, y - 1);
        }   
    }

    return moveCount;
}

EMSCRIPTEN_KEEPALIVE
int iterateBoxes(int xMove, int yMove)
{
    int moveCount = 0;

    if (xMove != 0)
    {
        for (int y = 0; y < board.size(); y++)
        {
            moveCount += iterateRow(y, xMove);
        }
    }
    if (yMove != 0)
    {
        for (int x = 0; x < board.size(); x++)
        {
            moveCount += iterateColumn(x, yMove);
        }
    }

    return moveCount;
}

EMSCRIPTEN_KEEPALIVE
void createBox(int x, int y, int number)
{
    board[y][x] = Box(x, y, boardScale, boxSize, number);
}

EMSCRIPTEN_KEEPALIVE
void update()
{
    for (auto& row : board)
    {
        for (auto& box : row)
        {
            if (box.isValid)
            {
                box.update();
            }
        }
    }

    int previousBoxesIteratedCount = boxesIteratedCount;
    boxesIteratedCount = iterateBoxes(keyXMove, keyYMove);

    if (previousBoxesIteratedCount > 0 && boxesIteratedCount == 0)
    {
        canCreateNewBox = true;
    }

    if (canCreateNewBox && !isAnyBoxMoving())
    {
        canCreateNewBox = false;
        int newX = 0;
        int newY = 0;
        do
        {
            newX = getRandomCoordinate();
            newY = getRandomCoordinate();
        }
        while(!isBoxEmpty(newX, newY));

        createBox(newX, newY, 2);

        keyXMove = 0;
        keyYMove = 0;

        return;
    }
}

EMSCRIPTEN_KEEPALIVE
int getBoardSize()
{
    return boardSize;
}

EMSCRIPTEN_KEEPALIVE
int getXCoordinate(int x, int y)
{
    return board[y][x].x;
}

EMSCRIPTEN_KEEPALIVE
int getYCoordinate(int x, int y)
{
    return board[y][x].y;
}

EMSCRIPTEN_KEEPALIVE
int getHeight(int x, int y)
{
    return board[y][x].height;
}

EMSCRIPTEN_KEEPALIVE
int getWidth(int x, int y)
{
    return board[y][x].width;
}

EMSCRIPTEN_KEEPALIVE
int getNumber(int x, int y)
{
    return board[y][x].number;
}

}

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;
std::array<SDL_Texture*, 10> textCache;

void generateCache()
{
    for (int i = 0; i < textCache.size(); ++i)
    {
        const std::string number = std::to_string(static_cast<int>(std::pow(2, i + 1)));

        SDL_Color textColor = {0, 0, 0};
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, number.c_str(), textColor); 
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        textCache[i] = textTexture;

        SDL_FreeSurface(textSurface);
    }
}

void draw(const Box& box)
{
    if (!box.isValid)
    {
        return;
    }

    // Draw background
    SDL_Rect r;
    r.x = box.x;
    r.y = box.y;
    r.w = boxSize;
    r.h = boxSize;

    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 0);
    SDL_RenderFillRect(renderer, &r);

    // Draw text
    const std::string number = std::to_string(box.number);

    SDL_Rect textRect;
    TTF_SizeText(font, number.c_str(), &(textRect.w), &(textRect.h));
    textRect.x = box.x + ((boxSize / 2) - (textRect.w / 2));
    textRect.y = box.y + ((boxSize / 2) - (textRect.h / 2));

    int textIndex = (std::log(box.number) / std::log(2)) - 1;
    SDL_Texture* textTexture = textCache[textIndex];
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}

void draw()
{
    SDL_Texture* screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 400, 400);
    SDL_SetRenderTarget(renderer, screenTexture);

    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
    SDL_RenderClear(renderer);

    for (const auto& row : board)
    {
        for (const auto& box : row)
        {
            draw(box);
        }
    }

    SDL_SetRenderTarget(renderer, NULL);

    SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(screenTexture);
}

void game_loop()
{
    auto currentTime = SDL_GetTicks();
    auto elapsedTime = currentTime - startTime;
    startTime = currentTime;

    delta += elapsedTime;

    while(delta >= frameDuration)
    {
        update();
        delta -= frameDuration;
    }
    draw();
}

int main()
{
    createBox(0, 0, 2);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(400, 400, 0, &window, &renderer);

    TTF_Init();
    font = TTF_OpenFont("assets/LiberationSans-Bold.ttf", 30);

    generateCache();

    startTime = SDL_GetTicks();
    delta = 0;
    
    #ifdef EMSCRIPTEN
    emscripten_set_main_loop(game_loop, 0, 1);
    #else
    int close = 0;
    // animation loop
    while (!close) {
        SDL_Event event;

        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;

            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_ESCAPE:
                    close = 1;
                    break;
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    setKeyMove(0, -1);
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    setKeyMove(-1, 0);
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    setKeyMove(0, 1);
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    setKeyMove(1, 0);
                    break;
                default:
                    break;
                }
            }
        }

        game_loop();

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
    #endif
}