#include <iostream>
using namespace std;

#include "vgl.h"
#include "LoadShader.h"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };
GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];
const GLuint  NumVertices = 6;

void init(void) {
    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);

    GLfloat  vertices[NumVertices][2] = {
        { -0.90, -0.90 },  // Triangle 1
        {  0.85, -0.90 },
        { -0.90,  0.85 },
        {  0.90, -0.85 },  // Triangle 2
        {  0.90,  0.90 },
        { -0.85,  0.90 }
    };

    glGenBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    ShaderInfo  shaders[] = {
        { GL_VERTEX_SHADER, "triangles.vert" },
        { GL_FRAGMENT_SHADER, "triangles.frag" },
        { GL_NONE, NULL }
    };

    GLuint program = LoadShaders(*shaders);
    glUseProgram(program);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    glFlush();
}

int
main(int argc, char** argv) {
     glutInit(&argc, argv);
     cout << "glutInit...[ OK ]" << endl;
     glutInitDisplayMode(GLUT_RGBA);
     cout << "glutInitDisplayMode...[ OK ]" << endl;
     glutInitWindowSize(512, 512);
     cout << "glutInitWindowSize...[ OK ]" << endl;
     glutInitContextVersion(4, 3);
     cout << "glutInitContextVersion...[ OK ]" << endl;
     glutInitContextProfile(GLUT_CORE_PROFILE);
     cout << "glutInitContextProfile...[ OK ]" << endl;
     glutCreateWindow(argv[0]);
     cout << "glutCreateWindow...[ OK ]" << endl;
     glewExperimental = GL_TRUE;
     if (glewInit()) {
         cerr << "Unable to initialize GLEW ... exiting" << endl;
         exit(EXIT_FAILURE);
     }
     init();
     cout << "init...[ OK ]" << endl;
     glutDisplayFunc(display);
     cout << "glutDisplayFunc...[ OK ]" << endl;
     glutMainLoop();
     cout << "glutMainLoop...[ OK ]" << endl;
}
