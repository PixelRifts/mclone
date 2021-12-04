#include "window.h"


namespace Window {
    struct WindowParams {
        GLFWwindow* Handle;
        GLFWmonitor* Monitor;
        
        i32 Width;
        i32 Height;
        bool IsFullscreen;
        std::string WindowTitle;
    };
    
    static WindowParams state;
    
    i32 cached_x, cached_y;
    i32 cached_w, cached_h;
    
    void Init(i32 width, i32 height, std::string title){
        glfwInit();
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        state.Monitor = glfwGetPrimaryMonitor();
        state.Handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        state.Width = width;
        state.Height = height;
        state.WindowTitle = title;
        state.IsFullscreen = false;
        
        Input::Init(state.Handle);
        glfwSetKeyCallback(state.Handle, Input::KeyCallback);
        glfwSetCursorPosCallback(state.Handle, Input::CursorPosCallback);
        glfwSetScrollCallback(state.Handle, Input::ScrollCallback);
    }
    
    void PollEvents() {
        Input::Reset();
        glfwPollEvents();
    }
    
    bool IsOpen() { return !glfwWindowShouldClose(state.Handle); }
    void SwapBuffers() { glfwSwapBuffers(state.Handle); }
    void Close() { glfwSetWindowShouldClose(state.Handle, true); }
    
    void FullscreenSwitch() {
        if (state.IsFullscreen) {
            glfwGetWindowPos(state.Handle, &cached_x, &cached_y);
            glfwGetWindowSize(state.Handle, &cached_w, &cached_h);
            
            // get resolution of monitor
            const GLFWvidmode * mode = glfwGetVideoMode(state.Monitor);
            
            // switch to full screen
            glfwSetWindowMonitor(state.Handle, state.Monitor, 0, 0, mode->width, mode->height, 0);
        } else {
            glfwSetWindowMonitor(state.Handle, nullptr, cached_x, cached_y, cached_w, cached_h, 0);
        }
        
        state.IsFullscreen = !state.IsFullscreen;
    }
    
    void Destroy() {
        glfwDestroyWindow(state.Handle);
        glfwTerminate();
    }
}
