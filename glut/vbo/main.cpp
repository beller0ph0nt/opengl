#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "program.h"

Program prog;
GLint attributeCoord2d;
GLuint vboTriangle;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(attributeCoord2d);
    glVertexAttribPointer(attributeCoord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, vboTriangle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(attributeCoord2d);
    glutSwapBuffers();
}

void init() {
    prog.CreateProgram({ { GL_VERTEX_SHADER, "shaders/vert" }, { GL_FRAGMENT_SHADER, "shaders/frag" } });
    attributeCoord2d = glGetAttribLocation(prog.getProgramId(), "coord2d");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    GLfloat triangleVertices[] = {
         0.0,  0.8,
        -0.8, -0.8,
         0.8, -0.8,
    };
    glGenBuffers(1, &vboTriangle);
    glBindBuffer(GL_ARRAY_BUFFER, vboTriangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 200);
    glutInitWindowSize(640, 480);
    glutCreateWindow("vbo");
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
