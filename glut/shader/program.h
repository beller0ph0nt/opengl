#ifndef PROGRAM_H
#define PROGRAM_H

#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include <GL/glew.h>
#include <GL/freeglut.h>

typedef GLuint ShdrId;
typedef GLuint ShdrType;

struct Shader
{
    GLuint type;
    string fileName;
};

class Program
{
    struct ProgramPrivat
    {
        map<ShdrType, ShdrId> shaderId;
        GLuint programId;
    } *_priv;

public:
    Program() { _priv = new ProgramPrivat(); }
    Program(vector<Shader> shaders):Program() { CreateProgram(shaders); }
    ~Program();
    void CreateProgram(vector<Shader> shaders);
    GLuint getProgramId() const { return _priv->programId; }

private:
    void CreateShader(GLuint type, const string fileName);
    void ReadShader(const string fileName, string &src) const;
};

#endif // PROGRAM_H
