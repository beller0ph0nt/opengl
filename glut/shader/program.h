#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
using namespace std;

#include <GL/glew.h>
#include <GL/freeglut.h>

struct ShaderInfo {
    GLuint type;
    string fileName;
};

class Program {
    struct ProgramPrivat {
        map<GLuint, GLuint> shaderId;
        GLuint programId;

        ProgramPrivat():programId(0) {}
    } *_priv;
public:
    Program(vector<ShaderInfo> shaders);
    ~Program();
private:
    GLuint CreateProgram(vector<ShaderInfo> shaders);
    GLuint CreateShader(GLuint type, const char *fileName);
    const char* ReadShader(const char *fileName);
};

#endif // PROGRAM_H
