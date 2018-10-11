// Main file
// (c) 2018 Jani Nykänen

#include "core/sys.h"

#include "game/game.h"


// Main
void main() {

    // Initialize system
    sys_init();

    // Initialize scenes
    game_init();

    // Start application
    sys_start_prog(game_run);
}
