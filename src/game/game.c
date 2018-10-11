// Game scene
// (c) 2018 Jani Nykänen

#include "game.h"

#include "../core/graph.h"
#include "../core/input.h"


// Change to the game scene
void game_run() {

    short t1 = input_get_button(BUTTON_FIRE1);
    short t2 = input_get_button(ARROW_LEFT);

    // Change color when certain buttons are pressed/released

    if(t1 == PRESSED) {

        clear_screen(128);
    }
    else if(t1 == RELEASED) {

        clear_screen(170);
    }
    
    if(t2 == RELEASED) {

        clear_screen(165);
    }
    else if(t2 == PRESSED) {

        clear_screen(170);
    }
}
