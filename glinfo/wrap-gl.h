#ifndef __WRAP_GL_H
#define __WRAP_GL_H

#include <GL/gl.h>

void
w_glGetError();

const GLubyte*
w_glGetString(GLenum name);

#endif // __WRAP_GL_H
