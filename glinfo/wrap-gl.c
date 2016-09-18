#include <stdio.h>
#include <wrap-gl.h>

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
