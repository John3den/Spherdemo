#include "Box.h"
#include "Macros.h"

namespace engine {
    engine::Vector3 Box::GetSize() {
        return size;
    }

    void Box::SetSize(engine::Vector3 s) {
        if (s.x >= 0 && s.y >= 0 && s.z >= 0) {
            size = s;
        }
        else {
            throw(std::invalid_argument("box size"));
        }
    }

    Box::Box(float x, float y, float z, float rx, float ry, float rz) :
        Shape(engine::Vector3(x, y, z), engine::Vector3(rx, ry, rz)) {}

    void Box::VectorToArray(std::vector<engine::Box> boxesVector, float* posData, float* sizeData) {

        for (int i = 0; i < boxesVector.size(); i++) {
            posData[BOX_X(i)] = boxesVector[i].position.x;
            posData[BOX_Y(i)] = boxesVector[i].position.y;
            posData[BOX_Z(i)] = boxesVector[i].position.z;
        }

        for (int i = 0; i < boxesVector.size(); i++) {
            sizeData[BOX_X(i)] = boxesVector[i].size.x;
            sizeData[BOX_Y(i)] = boxesVector[i].size.y;
            sizeData[BOX_Z(i)] = boxesVector[i].size.z;
        }
    }

    void Box::ArrayToVector(std::vector<engine::Box>& boxesVector, float* posData, float* sizeData) {
        for (int i = 0; i < boxesVector.size(); i++) {
            boxesVector[i].setPosition(engine::Vector3(posData[BOX_X(i)], posData[BOX_Y(i)], posData[BOX_Z(i)]));
            boxesVector[i].SetSize(engine::Vector3(sizeData[BOX_X(i)], sizeData[BOX_Y(i)], sizeData[BOX_Z(i)]));
        }
    }
};
