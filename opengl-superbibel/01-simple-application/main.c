#include <stdio.h>

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>

void
display()
{
    const GLfloat color[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glClearBufferfv(GL_COLOR, 0, color);
}

int
main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowPosition(300, 400);
    glutInitWindowSize(400, 400);
    glutCreateWindow("min");
    glutDisplayFunc(display);
    init();
    glutMainLoop();

    return EXIT_SUCCESS;
}
