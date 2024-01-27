// This class defines Vertex Array Object
#pragma once

#include "glad/glad.h"
#include"VBO.h"

class VAO {
    public:
    
    GLuint ID;
    
    VAO();

    VAO(int i);
    
    void LinkVBO(VBO& VBO, GLuint layout);
    
    void Bind();
    
    void Unbind();
    
    void Delete();
};
