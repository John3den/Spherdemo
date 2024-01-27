#pragma once
#include "Renderer.h"
namespace engine {
    class UI {

    public:
        void DrawFrame(engine::Scene& scene, engine::Renderer& renderer);
        void SetupFrame();
        ImGuiIO& InitUI(GLFWwindow* window);
        UI() = default;
    };
} // namespace engine