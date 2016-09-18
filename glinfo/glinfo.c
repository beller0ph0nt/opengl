#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <wrap-gl.h>
#include <wrap-glx.h>

#define TCP_DISPLAY_NAME        "notebook/unix:0"
#define DECNET_DISPLAY_NAME     "notebook/unix::0"
#define DISPLAY_NAME            ":0"

int
main(int argc, char** argv)
{
    char* display_name = DISPLAY_NAME;
	Display* dpy = w_XOpenDisplay(display_name);

    int attribute_list[] =
    {
        GLX_RGBA,
        GLX_DOUBLEBUFFER,
        GLX_RED_SIZE,     1,
        GLX_GREEN_SIZE,   1,
        GLX_BLUE_SIZE,    1,
        None
    };

	XVisualInfo* vi = w_glXChooseVisual(dpy, DefaultScreen(dpy), attribute_list);

	XSetWindowAttributes swa;
	swa.colormap = XCreateColormap(dpy,
	                               RootWindow(dpy, vi->screen),
	                               vi->visual,
	                               AllocNone);
	swa.border_pixel = 0;
	swa.event_mask = StructureNotifyMask;

	Window win = XCreateWindow(dpy,
	                           RootWindow(dpy, vi->screen),
	                           0,
	                           0,
	                           100,
	                           100,
	                           0,
	                           vi->depth,
	                           InputOutput,
	                           vi->visual,
	                           CWBorderPixel | CWColormap | CWEventMask,
	                           &swa);
//    XMapWindow(dpy, win);

#ifdef GLX_ARB_create_context
    #define GLX_CONTEXT_MAJOR_VERSION_ARB		0x2091
    #define GLX_CONTEXT_MINOR_VERSION_ARB		0x2092

    typedef GLXContext (*GLXCREATECONTEXTATTRIBSARBPROC)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

    const GLubyte* func_name = (const GLubyte*) "glXCreateContextAttribsARB";
    GLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB = \
        (GLXCREATECONTEXTATTRIBSARBPROC) glXGetProcAddress(func_name);

    int fbc_list_size;
	GLXFBConfig* fbc_list = glXChooseFBConfig(dpy,
	                                          DefaultScreen(dpy),
	                                          0,
	                                          &fbc_list_size);
	if (fbc_list == NULL)
	{
        printf("glXChooseFBConfig failure!\n");
        exit(EXIT_FAILURE);
	}

    const int attribs[] =
    {
		GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
		GLX_CONTEXT_MINOR_VERSION_ARB, 0,
		0
    };

    GLXContext ctx = glXCreateContextAttribsARB(dpy, *fbc_list, 0, True, attribs);
#else
    GLXContext ctx = glXCreateContext(dpy, vi, 0, GL_TRUE);
#endif // GLX_ARB_create_context

    glXMakeCurrent(dpy, win, ctx);

    printf("VENDOR:\n"
           "    %s\n"
           "RENDERER:\n"
           "    %s\n"
           "VERSION:\n"
           "    %s\n"
           "SHADING LANGUAGE VERSION:\n"
           "    %s\n",
           w_glGetString(GL_VENDOR),
           w_glGetString(GL_RENDERER),
           w_glGetString(GL_VERSION),
           w_glGetString(GL_SHADING_LANGUAGE_VERSION));


    const GLubyte* extensions = w_glGetString(GL_EXTENSIONS);

    printf("EXTENSIONS:\n"
           "    ");

    int i;
    for (i = 0; extensions[i] != '\0'; i++)
    {
        if (extensions[i] == ' ')
            printf("\n    ");
        else
            printf("%c", extensions[i]);
    }
    printf("\n");


    ctx = glXGetCurrentContext();
//    XUnmapWindow(dpy, win);
	glXDestroyContext(dpy, ctx);
	XCloseDisplay(dpy);

    return EXIT_SUCCESS;
}
