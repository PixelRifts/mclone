/* date = December 2nd 2021 9:05 pm */

#ifndef INPUT_H
#define INPUT_H

#include "defines.h"
#include <GLFW/glfw3.h>

namespace Input {
    extern GLFWwindow* cached_window;
    
    // Stored as bitfields
    // first  bit is "pressed"
    // second bit is "released"
    // third  bit is "held"
    // rest unused. maybe use for modifiers
    extern u8 key_states[350];
    
    extern float mouse_x;
    extern float mouse_y;
    
    
    void Init(GLFWwindow* window);
    void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    
    void Reset();
    
    bool Key(i32 key); // Is Key Pressed/Held Currently
    bool KeyPressed(i32 key); // Was Key Pressed this Frame
    bool KeyReleased(i32 key); // Was Key Released this Frame
    bool KeyHeld(i32 key); // Is Key Held
    
    float MouseX();
    float MouseY();
}

#endif //INPUT_H
