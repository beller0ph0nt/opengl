#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GL/freeglut.h>

const char *vsSrc =
        "#version 120\n"
        "attribute vec2 coord2d;"
        "void main(void) {"
        "   gl_Position = vec4(coord2d, 0.0, 1.0);"
        "}";

const char *fsSrc =
        "#version 120\n"
        "void main(void) {"
        "   gl_FragColor = vec4(gl_FragCoord.x / 640.0, gl_FragCoord.y / 480.0, 0.5, 1.0);"
        "}";

GLuint program;
GLint attribute_coord2d;

GLuint CreateShader(const GLenum type, const char *src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    GLint compileOk = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileOk);
    if (compileOk == GL_FALSE) {
        return 0;
    }
    return shader;
}

GLuint CreateProgram() {
    GLuint prog = glCreateProgram();
    glAttachShader(prog, CreateShader(GL_VERTEX_SHADER, vsSrc));
    glAttachShader(prog, CreateShader(GL_FRAGMENT_SHADER, fsSrc));
    glLinkProgram(prog);
    GLint linkOk;
    glGetProgramiv(prog, GL_LINK_STATUS, &linkOk);
    if (!linkOk) {
        return 0;
    }
    return prog;
}

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
    program = CreateProgram();
    glUseProgram(program);
    attribute_coord2d = glGetAttribLocation(program, "coord2d");
}

void free() {
    cout << "free res" << endl;
    glDeleteProgram(program);
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
    free();
    return EXIT_SUCCESS;
}
