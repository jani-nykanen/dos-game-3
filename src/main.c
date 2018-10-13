// Main file
// (c) 2018 Jani Nykänen

#include "core/sys.h"

#include "game/game.h"


// Main
void main() {

    // Initialize system
    sys_init();

    // Add scenes
    sys_add_scene(get_game_scene(), false, true);

    // Start application
    sys_start_prog();
}
