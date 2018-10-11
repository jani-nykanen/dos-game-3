// Bitmap
// (c) 2018 Jani Nykänen

#ifndef __BITMAP__
#define __BITMAP__

// Bitmap type
typedef struct {

    short w,h;
    unsigned char* data;
}
BITMAP;

// Create an empty bitmap
BITMAP* create_bitmap(short w, short h, char* data);

// Load a bitmap
BITMAP* load_bitmap(const char* path);

// Destroy a bitmap
void destroy_bitmap(BITMAP* bmp);

#endif // __BITMAP__
