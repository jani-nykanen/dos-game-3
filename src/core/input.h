// Input
// (c) 2018 Jani Nykänen

#ifndef __INPUT__
#define __INPUT__

// Buttons
enum {

    ARROW_RIGHT = 0,
    ARROW_UP = 1,
    ARROW_LEFT = 2,
    ARROW_DOWN = 3,
    BUTTON_FIRE1 = 4,
    BUTTON_FIRE2 = 5,
    BUTTON_CONFIRM = 6,
    BUTTON_CANCEL = 7,
};

// Button states
enum {
    UP = 0,
    DOWN = 1,
    PRESSED = 2,
    RELEASED = 3,
};

// Initialize
void init_input();

// Update
void input_update();

// Get button
char input_get_button(short id);

// Destroy
void input_destroy();

#endif // __INPUT__
