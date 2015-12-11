#include "program.h"

Program::Program(vector<ShaderInfo> shaders) {
    _priv = new ProgramPrivat();
    _priv->programId = CreateProgram(shaders);
}

Program::~Program() {
    glDeleteProgram(_priv->programId);
    delete _priv;
}

GLuint Program::CreateProgram(vector<ShaderInfo> shaders) {
    GLuint programId = glCreateProgram();
    cerr << "program create [ " << (programId == 0) ? "ERROR" : "OK" << " ]" << endl;
    for (int i = 0; i < shaders.size(); i++) {
        _priv->shaderId[shaders[i].type] = CreateShader(shaders[i].type, shaders[i].fileName.c_str());
        if (_priv->shaderId[shaders[i].type] == 0) {
            return 0;
        }
        glAttachShader(programId, _priv->shaderId[shaders[i].type]);
    }
    glLinkProgram(programId);
    GLint status;
    glGetProgramiv(programId, GL_LINK_STATUS, &status);
    cerr << "program link [ " << (status != GL_TRUE) ? "ERROR" : "OK" << " ]" << endl;
    return programId;
}

GLuint Program::CreateShader(GLuint type, const char *fileName) {
    GLuint shaderId = glCreateShader(type);
    const char *src = ReadShader(fileName);
    glShaderSource(shaderId, 1, &src, NULL);
    glCompileShader(shaderId);
    GLint status;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
    cerr << "shader compile [ " << (status != GL_TRUE) ? "ERROR" : "OK" << " ]" << endl;
    GLsizei bufSize = 100;
    char *infoLog = new char[bufSize + 1];
    glGetShaderInfoLog(shaderId, bufSize, NULL, infoLog);
    infoLog[bufSize] = '\0';
    cout << infoLog;
    delete[] infoLog;
    return shaderId;
}

const char* Program::ReadShader(const char *fileName) {
    fstream file(fileName, ios::in);
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str().c_str();
}
