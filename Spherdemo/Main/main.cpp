#include "UI.h"

int main() {
    engine::UI ui;
    engine::Renderer renderer;
    engine::Scene scene;

    ui.InitUI(renderer.GetWindow());
    
    while (!glfwWindowShouldClose(renderer.GetWindow())) {
        renderer.SetupFrame();
        
        ui.SetupFrame();

        renderer.StartScene(scene);
        
        renderer.SetUniforms(scene);
        
        renderer.DrawFrame();
        
        ui.DrawFrame(scene, renderer);
        
        renderer.EndFrame();
    }

    return 0;
}
