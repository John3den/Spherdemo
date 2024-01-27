#pragma once
#include "Vector3.h"
#include <vector>
#include "glad\glad.h"

namespace engine {
    class Shape {  
        protected:
        
        engine::Vector3 position;
        
        engine::Vector3 size;
        
        public:
        
        engine::Vector3 getPosition() { return position; }
        
        void setPosition(engine::Vector3 pos) { position = pos; }
        
        Shape(engine::Vector3 pos, engine::Vector3 size) : position(pos), size(size) {}
        
    };
} // namespace engine
