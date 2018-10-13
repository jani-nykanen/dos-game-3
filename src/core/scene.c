// Scene
// (c) 2018 Jani Nykänen

#include "scene.h"

#include "stdio.h"
#include "stdlib.h"


// Create a new scene
SCENE scene_create(FUNCTION init, FUNCTION update,
                   FUNCTION draw, FUNCTION destroy, 
                   FUNCTION change, 
                   const char* name) {
                       
    SCENE s;
    // Copy functions
    s.init = init;
    s.update = update;
    s.draw = draw;
    s.destroy = destroy;
    s.change = change;
    // Copy name
    snprintf(s.name,SCENE_NAME_LENGTH,"%s",name);

    return s;
}
