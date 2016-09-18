#ifndef __WRAP_GLX_H
#define __WRAP_GLX_H

#include <GL/glx.h>

Display*
w_XOpenDisplay(_Xconst char* display_name);

XVisualInfo*
w_glXChooseVisual(Display* dpy, int screen, int* attribList);

#endif // __WRAP_GLX_H
