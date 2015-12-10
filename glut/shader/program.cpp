#include "program.h"

Program::Program() {
    _priv = new ProgramPrivat();
}

Program::~Program() {
    delete _priv;
}

GLuint CreateProgram(vector<ShaderInfo> shaders) {
    for (vector<ShaderInfo>::iterator i = shaders.begin(); i == shaders.end(); i++) {
    }
}

GLuint Program::CreateVertShader(const char *fileName) {
    _priv->vertShaderId = CreateShader(GL_VERTEX_SHADER, fileName);
    return _priv->vertShaderId;
}

GLuint Program::CreateFragShader(const char *fileName) {
    _priv->fragShaderId = CreateShader(GL_FRAGMENT_SHADER, fileName);
    return _priv->fragShaderId;
}

GLuint Program::CreateShader(GLuint type, const char *fileName) {
    GLuint shaderId = glCreateShader(type);
    const char *src = ReadShader(fileName);
    glShaderSource(shaderId, 1, &src, NULL);
    glCompileShader(shaderId);
    GLint status;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        cerr << endl << "shader compilation [ ERROR ]" << endl;
    }
    GLsizei bufSize = 100;
    char *infoLog = new char[bufSize + 1];
    infoLog[bufSize] = '\0';
    glGetShaderInfoLog(shaderId, bufSize, NULL, infoLog);
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
