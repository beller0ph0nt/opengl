#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glx.h>

void
w_glGetError()
{
    GLenum err = glGetError();
    switch (err)
    {
    case GL_NO_ERROR:
        printf("GL_NO_ERROR\n");
        break;
    case GL_INVALID_ENUM:
        printf("GL_INVALID_ENUM\n");
        break;
    case GL_INVALID_VALUE:
        printf("GL_INVALID_VALUE\n");
        break;
    case GL_INVALID_OPERATION:
        printf("GL_INVALID_OPERATION\n");
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        printf("GL_INVALID_FRAMEBUFFER_OPERATION\n");
        break;
    case GL_OUT_OF_MEMORY:
        printf("GL_OUT_OF_MEMORY\n");
        break;
    case GL_STACK_UNDERFLOW:
        printf("GL_STACK_UNDERFLOW\n");
        break;
    case GL_STACK_OVERFLOW:
        printf("GL_STACK_OVERFLOW\n");
        break;
    default:
        printf("UNKNOWN ERROR\n");
    }
}


const GLubyte*
w_glGetString(GLenum name)
{
    const GLubyte* str = glGetString(name);
    if (str == NULL)
        w_glGetError();

    return str;
}

int
main(int argc, char** argv)
{
#define TCP_DISPLAY_NAME        "localhost:0.0"
#define DECNET_DISPLAY_NAME     "localhost::0.0"
#define DISPLAY_NAME            ":0"

    char* display_name = DISPLAY_NAME;
	Display* dpy = XOpenDisplay(display_name);
	if (dpy == NULL)
	{
        printf("XOpenDisplay failure!\n");
        exit(EXIT_FAILURE);
	}

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

    int attribute_list[] =
    {
        GLX_RGBA,
        GLX_DOUBLEBUFFER,
        GLX_RED_SIZE,     1,
        GLX_GREEN_SIZE,   1,
        GLX_BLUE_SIZE,    1,
        None
    };

	XVisualInfo* vi = glXChooseVisual(dpy, DefaultScreen(dpy), attribute_list);
	if (vi == NULL)
	{
        printf("glXChooseVisual failure!\n");
        exit(EXIT_FAILURE);
	}

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
    GLXContext ctx = glXCreateContext(dpy, vi, 0, GL_TRUE);
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




//#define GLX_CONTEXT_MAJOR_VERSION_ARB		0x2091
//#define GLX_CONTEXT_MINOR_VERSION_ARB		0x2092
//typedef GLXContext (*GLXCREATECONTEXTATTRIBSARBPROC)(Display*, GLXFBConfig, GLXContext, Bool, const int*);
//
//
//int main (int argc, char ** argv){
//
//	//oldstyle context:
//	//	GLXContext ctx = glXCreateContext(dpy, vi, 0, GL_TRUE);
//
//	std::cout << "glXCreateContextAttribsARB " << (void*) glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB") << std::endl;
//	GLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB =
//        (GLXCREATECONTEXTATTRIBSARBPROC) glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");
//
//	int attribs[] = {
//		GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
//		GLX_CONTEXT_MINOR_VERSION_ARB, 0,
//		0};
//
//	GLXContext ctx = glXCreateContextAttribsARB(dpy, *fbc, 0, true, attribs);
//
//	glXMakeCurrent (dpy, win, ctx);
//
//		glClearColor (0, 0.5, 1, 1);
//		glClear (GL_COLOR_BUFFER_BIT);
//		glXSwapBuffers (dpy, win);
//
//		sleep(1);
//
//		glClearColor (1, 0.5, 0, 1);
//		glClear (GL_COLOR_BUFFER_BIT);
//		glXSwapBuffers (dpy, win);
//
//		sleep(1);
//
//	ctx = glXGetCurrentContext();
//	glXDestroyContext(dpy, ctx);
//	}
