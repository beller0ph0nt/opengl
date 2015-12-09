#ifndef PROGRAM_H
#define PROGRAM_H

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <GL/glew.h>
#include <GL/freeglut.h>

struct ProgramPrivat {
    GLuint vertShaderId;
    //char *vertShaderSrc;
    GLuint fragShaderId;
    //char *fragShaderSrc;
    GLuint programId;

    ProgramPrivat():vertShaderId(0),
        //vertShaderSrc(NULL),
        fragShaderId(0),
        //fragShaderSrc(NULL),
        programId(0)
    {}
};

class Program {
    ProgramPrivat *_priv;
public:
    Program();
    ~Program();
    void loadVertShaderSrc(const char *fileName);
    void loadFragShaderSrc(const char *fileName);
private:
    const char* loadShader(const char *fileName);
};

#endif // PROGRAM_H
