#include "window.h"

namespace Window {
    i32 Width;
    i32 Height;
    bool IsFullscreen;
    std::string Title;
    
    GLFWwindow* WindowHandle;
    GLFWmonitor* Monitor;
    
    i32 cached_x, cached_y;
    i32 cached_w, cached_h;
    
    void Init(i32 width, i32 height, std::string title){
        glfwInit();
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        
        Monitor = glfwGetPrimaryMonitor();
        WindowHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        Width = width;
        Height = height;
        Title = title;
        IsFullscreen = false;
        
        Input::Init(WindowHandle);
        glfwSetKeyCallback(WindowHandle, Input::KeyCallback);
        glfwSetCursorPosCallback(WindowHandle, Input::CursorPosCallback);
    }
    
    void PollEvents() {
        Input::Reset();
        glfwPollEvents();
    }
    
    bool IsOpen() { return !glfwWindowShouldClose(WindowHandle); }
    void SwapBuffers() { glfwSwapBuffers(WindowHandle); }
    void Close() { glfwSetWindowShouldClose(WindowHandle, true); }
    
    void FullscreenSwitch() {
        if (IsFullscreen) {
            glfwGetWindowPos(WindowHandle, &cached_x, &cached_y);
            glfwGetWindowSize(WindowHandle, &cached_w, &cached_h);
            
            // get resolution of monitor
            const GLFWvidmode * mode = glfwGetVideoMode(Monitor);
            
            // switch to full screen
            glfwSetWindowMonitor(WindowHandle, Monitor, 0, 0, mode->width, mode->height, 0);
        } else {
            glfwSetWindowMonitor(WindowHandle, nullptr, cached_x, cached_y, cached_w, cached_h, 0);
        }
        
        IsFullscreen = !IsFullscreen;
    }
    
    void Destroy() {
        glfwDestroyWindow(WindowHandle);
        glfwTerminate();
    }
}
