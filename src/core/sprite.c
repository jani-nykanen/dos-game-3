// Sprite
// (c) 2018 Jani Nykänen

#include "sprite.h"

#include "graph.h"
#include "bitmap.h"


// Create a new sprite
SPRITE create_sprite(int w, int h) {

    SPRITE s;
    s.w = w;
    s.h = h;

    s.frame = 0;
    s.row = 0;
    s.count = 0;

    return s;
}


// Animate a sprite
void spr_animate(SPRITE*s, int row, int start, int end, int speed) {

    // If nothing to animate
    if(start == end) {
    
		s->count = 0;
		s->frame = start;
		s->row = row;
		return;
	}

    // If row changed
	if(s->row != row) {
	
		s->count = 0;
		s->frame = end > start ? start : end;
		s->row = row;
	}

	if(start < end && s->frame < start) {
	
		s->frame = start;
    }
    else if(end < start && s->frame < end) {
    
        s->frame = end;
    }

    // Animate
	++ s->count;
	if(s->count > speed) {
	
        if(start < end) {
        
            if(++ s->frame > end) {
                s->frame = start;
            }
        }
        else {
        
            if(-- s->frame < end) {
            
                s->frame = start;
            }
        }

		s->count -= speed;
	}
}


// Draw a sprite frame
void spr_draw_frame(SPRITE*s, BITMAP* bmp, int frame, int row, int x, 
    int y, int flip) {

    draw_bitmap_region(bmp,s->w*frame,s->h*row,s->w,s->h,x,y,flip);
}


// Draw a sprite
void spr_draw(SPRITE* s, BITMAP* bmp, int x, int y, int flip) {

    spr_draw_frame(s,bmp,s->frame,s->row,x,y,flip);
}
