// Graphics
// (c) 2018 Jani Nykänen

#include "graph.h"

#include <dos.h>
#include <conio.h>
#include <graph.h>

#include "stdbool.h"
#include "string.h"
#include "stdio.h"

#include "palette.h"


// VGA position
static const long VGA_POS = 0xA0000000;

// Palette constants
static const long PALETTE_INDEX = 0x03c8;
static const long PALETTE_DATA = 0x03c9;


// Set palette
static void set_palette() {

    short i = 0;

    // Set palette
    outp(PALETTE_INDEX,0);

    for(i = 0; i < 255*3 ; ++ i) {

        outp(PALETTE_DATA, palette[i]);
    }
}


// Initialize
void init_graphics() {

    // Set video mode to 320x200 256 colors
    _setvideomode(_MRES256COLOR);

    // Set palette
    set_palette();
}



// Clear screen
void clear_screen(char col) {

    char* VGA = (char*)VGA_POS;   

    memset(VGA, col, 320*200);
}
