// Game scene
// (c) 2018 Jani Nykänen

#include "game.h"

#include <stdio.h>

#include "../core/graph.h"
#include "../core/input.h"
#include "../core/bitmap.h"

// Bitmaps
static BITMAP* bmp_parrot = NULL;
static BITMAP* bmp_font = NULL;



// Initialize game
void game_init() {

    bmp_parrot = load_bitmap("ASSETS/BITMAPS/PARROT.BIN");
    bmp_font = load_bitmap("ASSETS/BITMAPS/FONT.BIN");
}


// Change to the game scene
void game_run() {

    // clear_screen(3);
    draw_bitmap_fast(bmp_parrot, 32, 32);
   
    draw_text(bmp_font, "Hello world!", 2, 2);
}
