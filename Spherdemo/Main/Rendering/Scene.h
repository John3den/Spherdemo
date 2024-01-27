#pragma once
#include "Vector3.h"
#include "Box.h"
#include "Sphere.h"
#include "Params.h"

namespace engine {
    class Scene {
        public:
        Scene();
        GLfloat* GetSpheresData();
        GLfloat* GetBoxPositions();
        GLfloat* GetBoxRadii();
        std::vector<engine::Sphere>& GetSpheresVector();
        std::vector<engine::Box>& GetBoxesVector();
        void AddBox(engine::Box);
        void AddSphere(engine::Sphere);
        int NumberOfBoxes();
        int NumberOfSpheres();
        ~Scene();

        private:
        GLfloat* m_spheresData;
        GLfloat* m_boxPositions;
        GLfloat* m_boxRadii;
        
        std::vector<engine::Sphere> m_spheres;
        std::vector<engine::Box> m_boxes;
    };
} // namespace engine
