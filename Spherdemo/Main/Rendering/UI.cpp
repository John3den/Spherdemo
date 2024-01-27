#include "UI.h"
#include "Macros.h"

void engine::UI::DrawFrame(engine::Scene& scene, engine::Renderer& renderer) {

    static float f = 0.0f;
    static int counter = 0;
    static ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoMove;
    bool t = true;
    ImGui::Begin("Setup", &t, flags);

    if (ImGui::Button("Add Sphere", ImVec2(BUTTON_W, BUTTON_H))) {
        auto sphere = engine::Sphere(X_MIN, Y_MIN, Z_MAX, MAX_SPHERE_RADIUS);
        scene.AddSphere(sphere);
        renderer.UpdateScene(scene);
    }

    if (ImGui::Button("Add Box", ImVec2(BUTTON_W, BUTTON_H))) {
        auto box = engine::Box(X_MIN, Y_MIN, Z_MAX, 1, 1, 1);
        scene.AddBox(box);
        renderer.UpdateScene(scene);
    }
    // sliders for spheres
    for (int i = 0; i < scene.NumberOfSpheres(); i++) {
        std::string s = std::string("Sphere #") + std::to_string(i + 1);
        // slider labels
        std::string sx = std::string("sX #") + std::to_string(i + 1);
        std::string sy = std::string("sY #") + std::to_string(i + 1);
        std::string sz = std::string("sZ #") + std::to_string(i + 1);
        std::string sr = std::string("sR #") + std::to_string(i + 1);

        ImGui::Text(s.c_str());

        auto x = &scene.GetSpheresData()[SPHERE_X(i)];
        auto y = &scene.GetSpheresData()[SPHERE_Y(i)];
        auto z = &scene.GetSpheresData()[SPHERE_Z(i)];
        auto r = &scene.GetSpheresData()[SPHERE_R(i)];

        ImGui::SliderFloat(sx.c_str(), x, X_MIN, X_MAX);
        ImGui::SliderFloat(sy.c_str(), y, Y_MIN, Y_MAX);
        ImGui::SliderFloat(sz.c_str(), z, Z_MIN, Z_MAX);
        ImGui::SliderFloat(sr.c_str(), r, MIN_SPHERE_RADIUS, MAX_SPHERE_RADIUS);
    }
    // sliders for boxes
    for (int i = 0; i < scene.NumberOfBoxes(); i++) {

        std::string s = std::string("Box #") + std::to_string(i + 1);
        // slider labels
        std::string sx = std::string("bX #") + std::to_string(i + 1);
        std::string sy = std::string("bY #") + std::to_string(i + 1);
        std::string sz = std::string("bZ #") + std::to_string(i + 1);

        std::string srx = std::string("bRX #") + std::to_string(i + 1);
        std::string sry = std::string("bRY #") + std::to_string(i + 1);
        std::string srz = std::string("bRZ #") + std::to_string(i + 1);

        ImGui::Text(s.c_str());
        auto x = &scene.GetBoxPositions()[BOX_X(i)];
        auto y = &scene.GetBoxPositions()[BOX_Y(i)];
        auto z = &scene.GetBoxPositions()[BOX_Z(i)];

        auto rx = &scene.GetBoxRadii()[BOX_X(i)];
        auto ry = &scene.GetBoxRadii()[BOX_Y(i)];
        auto rz = &scene.GetBoxRadii()[BOX_Z(i)];

        ImGui::SliderFloat(sx.c_str(), x, X_MIN, X_MAX);
        ImGui::SliderFloat(sy.c_str(), y, Y_MIN, Y_MAX);
        ImGui::SliderFloat(sz.c_str(), z, Z_MIN, Z_MAX);

        ImGui::SliderFloat(srx.c_str(), rx, MIN_BOX_WIDTH, MAX_BOX_WIDTH);
        ImGui::SliderFloat(sry.c_str(), ry, MIN_BOX_HEIGHT, MAX_BOX_HEIGHT);
        ImGui::SliderFloat(srz.c_str(), rz, MIN_BOX_LENGTH, MAX_BOX_LENGTH);
    }

    ImGui::SetWindowPos(ImVec2(0, 0));
    ImGui::SetWindowSize(ImVec2(UI_PANEL_W, UI_PANEL_H));

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void engine::UI::SetupFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

ImGuiIO& engine::UI::InitUI(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 420");
    return io;
}
