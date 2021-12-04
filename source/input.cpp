#include "input.h"
#include <cstring>

namespace Input {
    GLFWwindow* cached_window;
    
    // Stored as bitfields
    // first  bit is "pressed"
    // second bit is "released"
    // third  bit is "held"
    // rest unused. maybe use for modifiers
    u8 key_states[350];
    
    float mouse_x;
    float mouse_y;
    
    inline static void SetPressedBit(u32 index)    { key_states[index] |= 0b00000001; }
    inline static void SetReleasedBit(u32 index)   { key_states[index] |= 0b00000010; }
    inline static void SetHeldBit(u32 index)       { key_states[index] |= 0b00000100; }
    
    inline static void ResetPressedBit(u32 index)  { key_states[index] &= 0b11111110; }
    inline static void ResetReleasedBit(u32 index) { key_states[index] &= 0b11111101; }
    inline static void ResetHeldBit(u32 index)     { key_states[index] &= 0b11111011; }
    
    void Init(GLFWwindow* window) { cached_window = window; }
    
    void Reset() {
        // Sizeof u8 just to be explicit
        std::memset(key_states, 0, 350 * sizeof(u8));
    }
    
    void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        switch (action) {
            case GLFW_PRESS: {
                SetPressedBit(key);
                ResetReleasedBit(key);
                ResetHeldBit(key);
            } break;
            
            case GLFW_RELEASE: {
                ResetPressedBit(key);
                SetReleasedBit(key);
                ResetHeldBit(key);
            } break;
            
            case GLFW_REPEAT: {
                ResetPressedBit(key);
                ResetReleasedBit(key);
                SetHeldBit(key);
            } break;
        }
    }
    
    void CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
        mouse_x = (float)xpos;
        mouse_y = (float)ypos;
    }
    
    bool Key(i32 key) {
        return glfwGetKey(cached_window, key) != GLFW_RELEASE;
    }
    
    bool KeyPressed(i32 key) {
        return ((key_states[key] & 0b00000001) >> 0) != 0;
    }
    
    bool KeyReleased(i32 key) {
        return ((key_states[key] & 0b00000010) >> 1) != 0;
    }
    
    bool KeyHeld(i32 key) {
        return ((key_states[key] & 0b00000100) >> 2) != 0;
    }
}
