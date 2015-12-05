#include <GL/gl.h>
#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
        glVertex2f(0.0, 0.0);
    glEnd();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-200.0, 200.0, -200.0, 200.0, -200.0, 200.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowPosition(100, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Lesson 1");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
