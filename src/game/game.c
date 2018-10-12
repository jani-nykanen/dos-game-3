// Game scene
// (c) 2018 Jani Nykänen

#include "game.h"

#include <stdio.h>

#include "../core/graph.h"
#include "../core/input.h"
#include "../core/bitmap.h"

// Frame skip
static const FRAME_SKIP = 2;

// Bitmaps
static BITMAP* bmp_parrot = NULL;
static BITMAP* bmp_font = NULL;
static BITMAP* bmp_goat = NULL;

// Game canvas
static BITMAP* canvas;

// Frame skip timer
static char frame_skip_timer = 0;

// TEMP
static int pos = 0;


// Draw canvas
static void draw_canvas() {

    clear_screen(170);
    draw_bitmap_fast(bmp_parrot, -16, 48);
    draw_text(bmp_font, "Hello world!", 0, 0);
    fill_rect(144,32,64,32, 65);

    draw_bitmap_region(bmp_goat, 
        0, 0, 128, 32, 96 + pos, 32, FLIP_BOTH);
}


// Update game
static void update_game() {

    pos -= 2;
    pos %= 192;
}


// Draw
static void draw_game() {

    // Draw content to the canvas
    set_render_target(canvas);
    draw_canvas();

    // Set target to the screen
    set_render_target(NULL);

    draw_bitmap_fast(canvas, 20, 20);
}


// Initialize game
void game_init() {

    // Load bitmaps
    bmp_parrot = load_bitmap("ASSETS/BITMAPS/PARROT.BIN");
    bmp_font = load_bitmap("ASSETS/BITMAPS/FONT.BIN");
    bmp_goat = load_bitmap("ASSETS/BITMAPS/GOAT.BIN");

    // Create canvas
    canvas = create_bitmap(192, 160, NULL);

    // Clear screen to blue
    clear_screen(15);
}


// Change to the game scene
void game_run() {

    // Skip frames
    if(++ frame_skip_timer == FRAME_SKIP) {

        frame_skip_timer = 0;
        return;
    }

    // Update game
    update_game();
    // Draw game
    draw_game();
}
