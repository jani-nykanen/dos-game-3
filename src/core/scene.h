// Scene
// (c) 2018 Jani Nykänen

#ifndef __SCENE__
#define __SCENE__

// Scene name length
#define SCENE_NAME_LENGTH 32

typedef void (*FUNCTION) (void);

// Scene type
typedef struct {

    FUNCTION init;
    FUNCTION update;
    FUNCTION draw;
    FUNCTION destroy;
    FUNCTION change;

    char name[SCENE_NAME_LENGTH];
}
SCENE;

// Create a new scene
SCENE scene_create(FUNCTION init, FUNCTION update,
                   FUNCTION draw, FUNCTION destroy, 
                   FUNCTION change, 
                   const char* name);

#endif // __SCENE__
