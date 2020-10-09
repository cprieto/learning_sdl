#pragma once
#include <memory>
#include <tuple>

using color = std::tuple<unsigned char, unsigned char, unsigned char>;

class Game {
    bool running = false;

    struct WindowDeleter {
        void operator()(SDL_Window*);
    };

    struct RendererDeleter {
        void operator()(SDL_Renderer*);
    };

    std::unique_ptr<SDL_Window, WindowDeleter> window;
    std::unique_ptr<SDL_Renderer, RendererDeleter> renderer;
    int width;
    int height;
    color background;
public:
    Game(const std::string& name, int width, int height, color  background = color{255, 255, 255});
    ~Game();
    bool run();
};
