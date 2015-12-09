#include "program.h"

Program::Program() {
    _priv = new ProgramPrivat();
}

Program::~Program() {
}

void Program::loadVertShaderSrc(const char *fileName) {
    //_priv->vertShaderSrc = loadShader(fileName);
}

void Program::loadFragShaderSrc(const char *fileName) {
    //_priv->fragShaderSrc = loadShader(fileName);
}

const char* Program::loadShader(const char *fileName) {
    fstream file(fileName, ios::in);
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str().c_str();
}
