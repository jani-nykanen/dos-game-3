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

// Game canvas
static BITMAP* canvas;



// Initialize game
void game_init() {

    // Load bitmaps
    bmp_parrot = load_bitmap("ASSETS/BITMAPS/PARROT.BIN");
    bmp_font = load_bitmap("ASSETS/BITMAPS/FONT.BIN");

    // Create canvas
    canvas = create_bitmap(192, 160, NULL);

    // Clear screen to blue
    clear_screen(15);
}


// Change to the game scene
void game_run() {

    // draw_bitmap_fast(bmp_parrot, -32, 32);
    // draw_text(bmp_font, "Hello world!", -2, -2);

    // Set target to canvas
    set_render_target(canvas);

    clear_screen(170);
    draw_bitmap_fast(bmp_parrot, -16, 48);
    draw_text(bmp_font, "Hello world!", 0, 0);

    set_render_target(NULL);

    draw_bitmap_fast(canvas, 20, 20);
}
