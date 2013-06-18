
#include "MouseTool.h"
#include <stdio.h>
MouseTool::MouseTool(){
    #ifdef __APPLE__
    #elif __WIN32__
    #else
        dpy = XOpenDisplay(0); // Open the default display (the DISPLAY environment variable)
        root_window = XDefaultRootWindow(dpy); // Get the default root window
    #endif
}
void MouseTool::WarpPointer(float x, float y){

    #ifdef __APPLE__
        CGEventRef event = CGEventCreateMouseEvent(NULL, kCGEventMouseMoved, CGPointMake(x,y), 0);
        CGEventPost(kCGHIDEventTap, event);
        CFRelease(event);
    #elif __WIN32__
        SetCursorPos(x, y);
    #else
        XWarpPointer(dpy, None, root_window, 0,0,0,0, x, y);
        XFlush(dpy);
    #endif
}
int MouseTool::GetMouseState(int *x, int *y){
    int _x, _y;
    int state=0;
    #ifdef __APPLE__
        CGEventRef event = CGEventCreate(NULL);
        CGPoint cursor = CGEventGetLocation(event);
        CFRelease(event);
        if(CGEventSourceButtonState(0, kCGMouseButtonLeft)) state |= MT_LBUTTON;
        if(CGEventSourceButtonState(0, kCGMouseButtonRight)) state |= MT_RBUTTON;
        if(CGEventSourceButtonState(0, kCGMouseButtonCenter)) state |= MT_MBUTTON;
        _x = cursor.x;
        _y = cursor.y;
    #elif __WIN32__
        POINT point;
        GetCursorPos(&point);
        _x = point.x;
        _y = point.y;
        //printf("%d %d %d\n",!(GetAsyncKeyState(VK_RBUTTON) & 1<<16),GetAsyncKeyState(VK_MBUTTON),GetKeyState(VK_LBUTTON));
        if(GetAsyncKeyState(VK_RBUTTON) & 1 << 16) state |= MT_RBUTTON;
        if(GetAsyncKeyState(VK_MBUTTON) & 1 << 16) state |= MT_MBUTTON;
        if(GetAsyncKeyState(VK_LBUTTON) & 1 << 16) state |= MT_LBUTTON;
    #else
        XEvent evt;
        XQueryPointer(dpy, root_window, &evt.xbutton.root, &evt.xbutton.root, &_x, &_y, &evt.xbutton.x, &evt.xbutton.y, &evt.xbutton.state);
        if(evt.xbutton.state & Button1Mask) state |= MT_RBUTTON;
        if(evt.xbutton.state & Button2Mask) state |= MT_MBUTTON;
        if(evt.xbutton.state & Button3Mask) state |= MT_LBUTTON;
    #endif
    if(x != NULL) *x = _x;
    if(y != NULL) *y = _y;
    return state;
}
