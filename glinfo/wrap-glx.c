#include <stdio.h>
#include <stdlib.h>

#include <wrap-glx.h>

Display*
w_XOpenDisplay(_Xconst char* display_name)
{
    Display* dpy = XOpenDisplay(display_name);
	if (dpy == NULL)
	{
        printf("XOpenDisplay failure!\n");
        exit(EXIT_FAILURE);
	}

	return dpy;
}

XVisualInfo*
w_glXChooseVisual(Display* dpy, int screen, int* attribList)
{
    XVisualInfo* vi = glXChooseVisual(dpy, screen, attribList);
	if (vi == NULL)
	{
        printf("glXChooseVisual failure!\n");
        exit(EXIT_FAILURE);
	}

	return vi;
}
