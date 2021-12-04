#include <iostream>

#include <glad/glad.h>
#include "window.h"

int main(int argc, char** argv) {
    Window::Init(1080, 720, "MClone");
    
    while (Window::IsOpen()) {
        Window::PollEvents();
        
        if (Input::KeyPressed(GLFW_KEY_F11))
            Window::FullscreenSwitch();
        if (Input::mouse_x > 1000)
            std::cout << "To the Left!" << std::endl;
        if (Input::KeyPressed(GLFW_KEY_ESCAPE))
            Window::Close();
        
        Window::SwapBuffers();
    }
    
    Window::Destroy();
}
