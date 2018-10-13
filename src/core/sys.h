// System
// (c) 2018 Jani Nykänen

#ifndef __SYS__
#define __SYS__

#include <stdbool.h>

#include "scene.h"

// Initialize system
void sys_init();

// Start application
void sys_start_prog();

// Add a scene
void sys_add_scene(SCENE s, bool global, bool make_current);

#endif // __SYS__
