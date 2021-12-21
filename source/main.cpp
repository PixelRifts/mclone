#include <iostream>

#include <glad/glad.h>
#include "window.h"
#include "challenges.h"

#include <glm/glm.hpp>

// Uncomment line when I don't want to compile challenges
//#define MCLONE_NO_CHALLENGES

int main(int argc, char** argv) {
    Window::Init(1080, 720, "MClone");
    Challenges::Ep2_5_Init();
    
    while (Window::IsOpen()) {
        Window::PollEvents();
        
        if (Input::KeyPressed(GLFW_KEY_F11))
            Window::FullscreenSwitch();
        if (Input::KeyPressed(GLFW_KEY_ESCAPE))
            Window::Close();
        
        Challenges::Ep2_5_Draw();
        
        Window::SwapBuffers();
    }
    
    Challenges::Ep2_5_Free();
    Window::Destroy();
}
