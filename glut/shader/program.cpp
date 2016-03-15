#include "program.h"

Program::~Program()
{
    glDeleteProgram(_priv->programId);
    delete _priv;
}

void Program::CreateProgram(vector<Shader> shaders)
{
    _priv->programId = glCreateProgram();
    cerr << "program create [ " << ((_priv->programId == 0) ? "ERROR" : "OK") << " ]" << endl;
    for (int i = 0; i < shaders.size(); i++)
    {
        CreateShader(shaders[i].type, shaders[i].fileName);
        glAttachShader(_priv->programId, _priv->shaderId[shaders[i].type]);
    }
    glLinkProgram(_priv->programId);

    GLint status;
    glGetProgramiv(_priv->programId, GL_LINK_STATUS, &status);
    cerr << "program link [ " << ((status != GL_TRUE) ? "ERROR" : "OK") << " ]" << endl;
    glUseProgram(_priv->programId);
}

void Program::CreateShader(GLuint type, const string fileName)
{
    _priv->shaderId[type] = glCreateShader(type);

    string src;
    ReadShader(fileName, src);
    const char *c_src = src.c_str();

    glShaderSource(_priv->shaderId[type], 1, &c_src, NULL);
    glCompileShader(_priv->shaderId[type]);

    GLint status;
    glGetShaderiv(_priv->shaderId[type], GL_COMPILE_STATUS, &status);
    cerr << fileName << " compile [ " << ((status != GL_TRUE) ? "ERROR" : "OK") << " ]" << endl;

    GLsizei bufSize = 100;
    char *infoLog = new char[bufSize];
    glGetShaderInfoLog(_priv->shaderId[type], bufSize, NULL, infoLog);
    cerr << infoLog;
    delete[] infoLog;
}

void Program::ReadShader(const string fileName, string &src) const {
    fstream file(fileName, ios::in);
    if (file.is_open())
    {
        stringstream buffer;
        buffer << file.rdbuf();
        src = buffer.str();
        buffer.clear();
    }
    file.close();
}
