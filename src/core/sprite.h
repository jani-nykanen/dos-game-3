// Sprite
// (c) 2018 Jani Nykänen

#ifndef __SPRITE__
#define __SPRITE__

#include "bitmap.h"

// Sprite object
typedef struct {

    int w;
    int h; 
    int frame;
    int row;
    int count;

} 
SPRITE;

// Create a new sprite
SPRITE create_sprite(int w, int h);

// Animate a sprite
void spr_animate(SPRITE* s, int row, int start, int end, int speed);

// Draw a sprite frame
void spr_draw_frame(SPRITE* s, BITMAP* bmp, int frame, int row, int x, 
    int y, int flip);

// Draw a sprite
void spr_draw(SPRITE* s, BITMAP* bmp, int x, int y, int flip);

#endif // __SPRITE__
