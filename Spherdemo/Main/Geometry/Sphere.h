#pragma once
#include "Vector3.h"
#include <memory>
#include <vector>
#include "Shape.h"

namespace engine {

    class Sphere : Shape {
        public:
        float GetSize();
        
        void SetSize(float r);
        
        Sphere(engine::Vector3 pos, float r);
        
        Sphere(float x, float y, float z, float r);
        
        static void VectorToArray(std::vector<engine::Sphere> v, GLfloat* spheresData);
        
        static void ArrayToVector(std::vector<engine::Sphere>& v, GLfloat* spheresData);
    };
} // namespace engine
