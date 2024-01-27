// This class defines a shader program
#pragma once
#include "glad/glad.h"
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include <memory>

std::string get_file_contents(const char* filename);

class Shader {
    public:
    
    GLuint ID;
    Shader();
    Shader(const char* vertexFile, const char* fragmentFile);
    void compileErrors(unsigned int shader, const char* type);
    
    void Activate();
    
    void Delete();
};
