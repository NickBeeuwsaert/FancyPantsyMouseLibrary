#ifndef __MAIN_H__
#define __MAIN_H__
//#undef __APPLE__
#ifdef _WIN32
#define __WIN32__
#endif

#ifdef __APPLE__
    #include <ApplicationServices/ApplicationServices.h>
#elif __WIN32__
    #include <windows.h>
#else
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/X.h>
#endif

#define MT_BUTTON(x) (1 << x)
#define MT_RBUTTON MT_BUTTON(0)
#define MT_MBUTTON MT_BUTTON(1)
#define MT_LBUTTON MT_BUTTON(2)

class MouseTool {
    #ifdef __APPLE__
    #elif __WIN32__
    #else
        Display *dpy;
        Window root_window;
    #endif
    public:
        MouseTool();
        void WarpPointer(float, float);
        int GetMouseState(int *,int *);
};

#endif //__MAIN_H__