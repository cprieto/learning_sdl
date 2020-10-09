#include <stdexcept>
#include <SDL2/SDL.h>
#include <memory>
#include <utility>
#include "Game.h"

Game::Game(const std::string& name, int width, int height, color background): width{width}, height{height}, background{std::move(background)} {
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error("Error when intializing SDL graphics: " + std::string{SDL_GetError()});

    window = std::unique_ptr<SDL_Window, WindowDeleter>(SDL_CreateWindow(
            name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height, SDL_WINDOW_SHOWN));

    if (window == nullptr)
        throw std::runtime_error("Problems when creating the window");

    renderer = std::unique_ptr<SDL_Renderer, RendererDeleter>(SDL_CreateRenderer(
            window.get(), -1, 0));

    if (renderer == nullptr)
        throw std::runtime_error("Problems when creating the renderer");
}

bool Game::run() {
    auto [r, g, b] = background;
    SDL_SetRenderDrawColor(renderer.get(),r, g, b, 255);
    SDL_RenderClear(renderer.get());
    SDL_RenderPresent(renderer.get());

    running = true;
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            default:
                break;
        }
    }

    return running;
}

Game::~Game() {
    SDL_Quit();
}

void Game::WindowDeleter::operator()(SDL_Window *win) {
    SDL_DestroyWindow(win);
}

void Game::RendererDeleter::operator()(SDL_Renderer *rdr) {
    SDL_DestroyRenderer(rdr);
}
