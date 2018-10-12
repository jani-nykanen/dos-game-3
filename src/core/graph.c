// Graphics
// (c) 2018 Jani Nykänen

#include "graph.h"

#include <dos.h>
#include <conio.h>
#include <graph.h>

#include "stdbool.h"
#include "string.h"
#include "stdio.h"

#include "palette.c"

// Alpha color (temporarily a constant!)
static const char ALPHA = 170;

// VGA position
static const long VGA_POS = 0xA0000000;

// Palette constants
static const long PALETTE_INDEX = 0x03c8;
static const long PALETTE_DATA = 0x03c9;

// Target frame
static BITMAP* target_frame;
// Default frame
static BITMAP default_frame;


// Set palette
static void set_palette() {

    short i = 0;

    // Set palette
    outp(PALETTE_INDEX,0);

    for(i = 0; i < 256*3 ;  ++ i) {

        outp(PALETTE_DATA, palette[i]/4);
    }
}


// Clip
static bool clip(BITMAP* bmp, 
    short* dx, short* dy, 
    short* sx, short *sy,
    short* sw, short* sh, char flip) {

	short w = target_frame->w;
	short h = target_frame->h;

	short ow, oh;
	
	if(*dx+*sw >= w) {

		ow = *sw;
		*sw = (w - *dx);

		if((flip & FLIP_H) != 0) {

			*sx += ow - *sw;
		}

	} else if(*dx < 0) {

		ow = *sw;
		*sx += -*dx;
		*sw += *dx;
		*dx = 0;

		if((flip & FLIP_H) != 0) {

			*sx += *sw - ow;
		}
	}
	if(*dy+*sh >= h) {

		oh = *sh;
		*sh = h - *dy;

		if((flip & FLIP_V) != 0) {

			*sy += oh - *sh;
		}

	} else if(*dy < 0) {

		oh = *sh;
		*sy += -*dy;
		*sh += *dy;
		*dy = 0;

		if((flip & FLIP_V) != 0) {

			*sy += *sh - oh;
		}
	}

	// Check if(we have anything to be drawn
	if(*sw <= 0 || *sh <= 0 || *sx >= bmp->w || *sy >= bmp->h) {
	
		return false;
	}

	return true;
}


// Initialize
void init_graphics() {

    // Set video mode to 320x200 256 colors
    _setvideomode(_MRES256COLOR);

    // Set palette
    set_palette();

    // "Create" default frame
    default_frame.w = 320;
    default_frame.h = 200;
    default_frame.data = (char*)VGA_POS;

    target_frame = &default_frame;
}


// Clear screen
void clear_screen(char col) {

    memset(target_frame->data, col, 
        target_frame->w*target_frame->h);
}


// Draw a bitmap fast
void draw_bitmap_fast(BITMAP* bmp, short dx, short dy) {

    draw_bitmap_region_fast(bmp, 0, 0, bmp->w, bmp->h, dx, dy);
}


// Draw a bitmap region fast
void draw_bitmap_region_fast(BITMAP* bmp, short sx, short sy, short sw, short sh,
     short dx, short dy) {

    char* VGA = target_frame->data; 
    char* data = (char*)bmp->data;
    short y = 0;
    short offset, bmp_off;

    // Clip
    if(!clip(bmp, &dx, &dy, &sx, &sy, &sw, &sh, 0)) return;
    offset = target_frame->w*dy + dx;
    bmp_off = bmp->w*sy + sx;

    for(; y < sh; ++ y) {

        memcpy(VGA + offset, data + bmp_off, sw);
        offset += target_frame->w;
        bmp_off += bmp->w;
    }
}


// Draw bitmap
void draw_bitmap(BITMAP* bmp, short dx, short dy, char flip) {

    draw_bitmap_region(bmp, 0, 0, bmp->w, bmp->h, dx, dy, flip);
}


// Draw a bitmap region
void draw_bitmap_region(BITMAP* bmp, short sx, short sy, short sw, short sh,
     short dx, short dy, char flip) {

    char* VGA = target_frame->data; 
    char* data = (char*)bmp->data;
    short x, y;
    short offset, bmp_off;
    char col;

    bool hflip = (flip & FLIP_H) != 0;
    bool vflip = (flip & FLIP_V) != 0;

    // Clip
    if(!clip(bmp, &dx, &dy, &sx, &sy, &sw, &sh, flip)) return;
    offset = target_frame->w*dy + dx;
    bmp_off = bmp->w*sy + sx;

    // Flip
    if(vflip) {

        offset += (sh-1) * target_frame->w;
    }

    if(hflip) {

        offset += sw -1;
    }

    // Draw pixels
    for(y = 0; y < sh; ++ y) {

        for(x = 0; x <  sw; ++ x) {

            col = data[bmp_off ++];

            if(col != ALPHA)
                VGA[offset] = col;

            if(hflip)
                -- offset;
            else
                ++ offset;

        }

        bmp_off += bmp->w - sw;

        if(hflip) {

            offset += sw * 2;
        }

        offset -= sw;

        if(vflip) {

            offset -= target_frame->w; 
        }
        else {

            offset += target_frame->w; 
        }
    }
}


// Draw text 
void draw_text(BITMAP* bmp, const char* text, 
    short dx, short dy) {
    
    char len = strlen((const char*)text);

    short x = dx;
    short y = dy;
    short cw = bmp->w / 16;
    short ch = cw;
    short i=0;
    char c;
    short sx;
    short sy;

    for(; i < len; ++ i) {

        c = text[i];
        if(c > 0) -- c;
        sx = c % 16;
        sy = c / 16;

        draw_bitmap_region_fast(bmp,sx*cw,sy*ch,cw,ch,x,y);

        x += cw;
    }
}


// Draw a filled rectangle
void fill_rect(short dx, short dy, short dw, short dh, char col) {

    short endx, endy, y;
    char* VGA = target_frame->data; 
    short offset;

    // Restrict to the target frame area
    if(dx < 0) dx = 0;
    if(dy < 0) dy = 0;

    endx = dx + dw;
    if(endx > target_frame->w) 
        endx = target_frame->w;
    if(endy > target_frame->h) 
        endy = target_frame->h;

    // If nothing to draw (horizontally), skip
    if(endx <= dx) return;

    // Draw
    offset = target_frame->w*dy + dx;
    for(y = dy; y < endy; ++ y) {

        memset(VGA + offset, col, endx-dx);
        offset += target_frame->w;
    }
}


// Set render target
void set_render_target(BITMAP* bmp) {

    target_frame = bmp != NULL ? bmp : &default_frame;
}
