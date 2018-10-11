// System
// (c) 2018 Jani Nykänen

#include "sys.h"

#include <dos.h>
#include <conio.h>
#include <bios.h>

#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"
#include "input.h"


// Callback function for loop
static void (*loop_cb) (void);
// Is the loop running
static bool loop_running =false;



// VSync
static void vsync() {

    while(inp(0x3DA) & 8);
    while(!(inp(0x3DA) & 8));
}


// Initialize system
void sys_init() {

    // Initialize components
    init_graphics();
    init_input();

    // Clear screen
    clear_screen(170);
}


// Start application
void sys_start_prog(void (*cb) (void)) {

    loop_cb = cb;

    // Enter the loop
    loop_running = true;
    while(loop_running) {

        // Wait for vsync
        vsync();

        // Update
        if(loop_cb != NULL)
            loop_cb();
    }
}
