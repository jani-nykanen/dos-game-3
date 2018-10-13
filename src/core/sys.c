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

// Maximum scene count
#define MAX_SCENES 16


// Is the loop running
static bool loop_running = false;

// Scenes
static SCENE scenes[MAX_SCENES];
// Scene count
static int scene_count;
// Current scene pointer
static int scene_current;
// Global scene pointer
static int scene_global = -1;


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
    clear_screen(0);
}


// Start application
void sys_start_prog() {

    short i = 0;
    SCENE s;

    // Initialize scenes
    for(; i < scene_count; ++ i) {

        s = scenes[i];
        if(s.init != NULL) {

            s.init();
        }
    }

    // Enter the loop
    loop_running = true;
    while(loop_running) {

        // Wait for vsync
        vsync();

        // Update & draw current scene
        s = scenes[scene_current];
        if(s.update != NULL) {

            s.update();
        }
        if(s.draw != NULL) {

            s.draw();
        }

        // Update global scene
        if(scene_global != -1) {

            s = scenes[scene_global];
            if(s.update != NULL) {

                s.update();
            }
            if(s.draw != NULL) {

                s.draw();
            }
        }
    }
}


// Add a scene
void sys_add_scene(SCENE s, bool global, bool make_current) {

    // Make global
    if(global) {

        scene_global = 0;
    }

    // Make current, if no scene given, or make_current
    // flag is true
    if(scene_count == 0 || make_current) {

        scene_global = -1;
    }

    scenes[scene_count] = s;
    scene_current = scene_count ++;
}

