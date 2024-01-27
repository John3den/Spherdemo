#pragma once
#include "Scene.h"
#include "imgui_impl_glfw.h"
#include "VAO.h"
#include "EBO.h"
#include "Shader.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

namespace engine {
    class Renderer {
        public:
        void SetUniforms(engine::Scene& scene);
        void StartScene(engine::Scene& scene);
        void SetupFrame();
        void DrawFrame();
        void EndFrame();
        void UpdateScene(engine::Scene& scene);
        GLFWwindow* GetWindow();
        ~Renderer();
        Renderer();

        private:
        GLFWwindow* m_window;
        Shader m_shaderProgram;
        VAO m_VAO1;
        void GLFWInit();
        GLFWwindow* SetupWindow();
        VAO SetupRender();
    };
} // namespace engine