#include "Sphere.h"
#include "Macros.h"

namespace engine {

    float Sphere::GetSize() {
        return size.x;
    }

    void Sphere::SetSize(float r) {
        size = engine::Vector3(r, 0, 0);
    }

    Sphere::Sphere(engine::Vector3 pos, float r) :
        Shape(pos, engine::Vector3(r, 0, 0)) {}

    Sphere::Sphere(float x, float y, float z, float r) :
        Shape(engine::Vector3(x, y, z), engine::Vector3(r, 0, 0)) {}

    void Sphere::VectorToArray(std::vector<engine::Sphere> v, GLfloat* spheresData) {
        for (int i = 0; i < v.size(); i++) {
            spheresData[SPHERE_X(i)] = v[i].getPosition().x;
            spheresData[SPHERE_Y(i)] = v[i].getPosition().y;
            spheresData[SPHERE_Z(i)] = v[i].getPosition().z;
            spheresData[SPHERE_R(i)] = v[i].GetSize();
        }
    }

    void Sphere::ArrayToVector(std::vector<engine::Sphere>& spheresVector, GLfloat* spheresData) {
        for (int i = 0; i < spheresVector.size(); i++) {
            spheresVector[i].setPosition(engine::Vector3(
                spheresData[SPHERE_X(i)],
                spheresData[SPHERE_Y(i)],
                spheresData[SPHERE_Z(i)]));
            spheresVector[i].SetSize(spheresData[SPHERE_R(i)]);
        }
    }
};