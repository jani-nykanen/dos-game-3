// Input
// (c) 2018 Jani Nykänen

#include "input.h"

#include <dos.h>
#include <conio.h>
#include <bios.h>

#include "stdio.h"
#include "stdbool.h"

// Normal keys
static unsigned char normal_keys[0x60];
// Extended keys
static unsigned char ext_keys[0x60];

// Old key states (normal)
static unsigned char old_normals[0x60];
// Old key states (extended)
static unsigned char old_ext[0x60];
// Read states (normal)
static bool normal_read[0x60];
// Read states (extended)
static bool ext_read[0x60];

// Handlers
static void far interrupt (*old_handler)(void);

// Button key codes
static const short BUTTONS[] = {

    77, 72, 75, 80,
    44, 45, 28, 1,
};


// Keyboard interruption
// (Happily copied from one very helpful Stack Overflow answer!)
static void far interrupt handler() {

    static unsigned char buffer;
    unsigned char rawcode;
    unsigned char make_break;
    int scancode;

    rawcode = inp(0x60); 
    make_break = !(rawcode & 0x80); 
    scancode = rawcode & 0x7F;

    if (buffer == 0xE0) { 

        if (scancode < 0x60) {

            old_ext[scancode] = ext_keys[scancode];
            ext_keys[scancode] = make_break;
            
            if(ext_keys[scancode] != old_ext[scancode])
                ext_read[scancode] = false;
        }
        buffer = 0;

    } 
    else if (buffer >= 0xE1 && buffer <= 0xE2) {

        buffer = 0;

    } 
    else if (rawcode >= 0xE0 && rawcode <= 0xE2) {

        buffer = rawcode; 

    } 
    else if (scancode < 0x60) {

        old_normals[scancode] = normal_keys[scancode];
        normal_keys[scancode] = make_break;

        if(normal_keys[scancode] != old_normals[scancode])
            normal_read[scancode] = false;
    }

    outp(0x20, 0x20);
}


// Hook interruption
static void hook_keyb_int() {

    old_handler = _dos_getvect(0x09);
    _dos_setvect(0x09, handler);
}


// Get button value from an array
static char get_value_from_arr(char* arr, bool* read_arr, short id) {

    short s = BUTTONS[id];
    char state = arr[ s ];
    bool read = read_arr[ s ];
    char ret = 0;

    if(!read) {

        if(state == DOWN) {

            ret = PRESSED;
        }
        else if(state == UP) {

            ret = RELEASED;
        }
    }
    read_arr[s] = true;

    return ret;
}


// Unhook
static void unhook_keyb_int() {

    if (old_handler != NULL) {

        _dos_setvect(0x09, old_handler);
        old_handler = NULL;
    }
}


// Initialize
void init_input() {

    short i = 0;
    for(; i < 0x60; ++ i) {

        old_normals[i] = 255;
        old_ext[i] = 255;
        normal_read[i] = false;
        ext_read[i] = false;
    }

    // Init handlers
    hook_keyb_int();
}


// Update
void input_update() {

}


// Get button
char input_get_button(short id) {

    // If arrow key
    if(id < 4) {

        // Get extended
        return get_value_from_arr(
            ext_keys, ext_read, id);
    }
    else {

        // Get normal
        return get_value_from_arr(
            normal_keys, normal_read, id);
    }
}


// Destroy
void input_destroy() {

    unhook_keyb_int();
}
