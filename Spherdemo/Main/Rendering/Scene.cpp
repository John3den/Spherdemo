#include "Vector3.h"
#include "Box.h"
#include "Sphere.h"
#include "Scene.h"

namespace engine {
    Scene::Scene() {
        m_spheresData = new GLfloat[SPHERES_SIZE];
        m_boxPositions = new GLfloat[BOXES_SIZE];
        m_boxRadii = new GLfloat[BOXES_SIZE];
        m_spheres = std::vector<engine::Sphere>();
        m_boxes = std::vector<engine::Box>();
    }
    GLfloat* Scene::GetSpheresData() {
        return m_spheresData;
    }
    GLfloat* Scene::GetBoxPositions() {
        return m_boxPositions;
    }
    GLfloat* Scene::GetBoxRadii() {
        return m_boxRadii;
    }
    std::vector<engine::Sphere>& Scene::GetSpheresVector() {
        return m_spheres;
    }
    std::vector<engine::Box>& Scene::GetBoxesVector() {
        return m_boxes;
    }
    void Scene::AddBox(engine::Box b) {
        m_boxes.push_back(b);
    }    
    void Scene::AddSphere(engine::Sphere s) {
        m_spheres.push_back(s);
    }
    int Scene::NumberOfBoxes()
    {
        return m_boxes.size();
    }
    int Scene::NumberOfSpheres()
    {
        return m_spheres.size();
    }
    Scene::~Scene()
    {
        delete m_spheresData;
        delete m_boxPositions;
        delete m_boxRadii;
    }
};
