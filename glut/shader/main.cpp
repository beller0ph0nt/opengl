#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "program.h"

GLint attribute_coord2d;
Program prog;

void display() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(attribute_coord2d);
    GLfloat triangle_vertices[] = {
         0.0,  0.8,
        -0.8, -0.8,
         0.8, -0.8,
    };
    glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, triangle_vertices);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(attribute_coord2d);
    glutSwapBuffers();
}

void init() {
    prog.CreateProgram({ { GL_VERTEX_SHADER, "shaders/vert" }, { GL_FRAGMENT_SHADER, "shaders/frag" } });
    attribute_coord2d = glGetAttribLocation(prog.getProgramId(), "coord2d");
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 200);
    glutInitWindowSize(640, 480);
    glutCreateWindow("shaders");
    glutInitContextVersion(2, 1);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    GLenum glewStat = glewInit();
    if (glewStat != GLEW_OK) {
        cerr << glewGetErrorString(glewStat) << endl;
        return EXIT_FAILURE;
    }
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return EXIT_SUCCESS;
}
