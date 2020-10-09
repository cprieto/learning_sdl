#include <iostream>
#include <SDL2/SDL.h>
#include "Game.h"

int main(int argc, char *args[]) {
    auto game = Game{"hola", 600, 600};
    while(game.run()) {}
    return 0;
}