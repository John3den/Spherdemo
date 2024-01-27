#pragma once
#include "Vector3.h"
#include "Shape.h"
#include <stdexcept>

namespace engine {
    class Box : Shape {
        public:
        
        engine::Vector3 GetSize();
        
        void SetSize(engine::Vector3 s);
        
        Box(float x, float y, float z, float rx, float ry, float rz);
        
        static void VectorToArray(std::vector<engine::Box> v, float* posData, float* sizeData);
        
        static void ArrayToVector(std::vector<engine::Box>& v, float* posData, float* sizeData);
    };
} // namespace engine
