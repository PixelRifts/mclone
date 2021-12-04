/* date = December 4th 2021 3:22 pm */

#ifndef WINDOW_H
#define WINDOW_H

#include "input.h"
#include <string>

namespace Window {
    void Init(i32 width, i32 height, std::string title);
    
    void PollEvents();
    bool IsOpen();
    void SwapBuffers();
    void FullscreenSwitch();
    void Close();
    
    void Destroy();
}

#endif //WINDOW_H
