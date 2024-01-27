#include "Renderer.h"

void engine::Renderer::SetUniforms(engine::Scene& scene) {
    auto location = glGetUniformLocation(m_shaderProgram.ID, "spheres");
    int speheresSize = scene.GetSpheresVector().size();
    int boxesSize = scene.GetBoxesVector().size();

    glUniform4fv(location, speheresSize, scene.GetSpheresData());
    location = glGetUniformLocation(m_shaderProgram.ID, "boxesPos");
    glUniform3fv(location, boxesSize, scene.GetBoxPositions());
    location = glGetUniformLocation(m_shaderProgram.ID, "boxesRad");
    glUniform3fv(location, boxesSize, scene.GetBoxRadii());
    location = glGetUniformLocation(m_shaderProgram.ID, "SPHERESCOUNT");
    glUniform1i(location, speheresSize);
    location = glGetUniformLocation(m_shaderProgram.ID, "BOXCOUNT");
    glUniform1i(location, boxesSize);
}

void engine::Renderer::UpdateScene(engine::Scene& scene) {
    auto sphereVector = scene.GetSpheresVector();
    auto sphereData = scene.GetSpheresData();
    engine::Sphere::VectorToArray(sphereVector, sphereData);

    auto boxVector = scene.GetBoxesVector();
    auto boxPos = scene.GetBoxPositions();
    auto boxRad = scene.GetBoxRadii();
    engine::Box::VectorToArray(boxVector, boxPos, boxRad);
}

void engine::Renderer::StartScene(engine::Scene& scene) {
    auto sphereVector = scene.GetSpheresVector();
    auto sphereData = scene.GetSpheresData();
    engine::Sphere::ArrayToVector(sphereVector, sphereData);

    auto boxVector = scene.GetBoxesVector();
    auto boxPos = scene.GetBoxPositions();
    auto boxRad = scene.GetBoxRadii();
    engine::Box::ArrayToVector(boxVector, boxPos, boxRad);
}

void engine::Renderer::GLFWInit() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* engine::Renderer::SetupWindow() {
    GLFWwindow* window =
        glfwCreateWindow(SCREEN_W, SCREEN_H, "Spheremarching demo.", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(0);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    glViewport(0, 0, SCREEN_W, SCREEN_H);
    return window;
}

VAO engine::Renderer::SetupRender() {
    VAO VAO1(0);
    VAO1.Bind();

    // Put square over screen to display spheremarching results
    GLfloat vertices[] = {
        -1, -1, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 1, 3
    };

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    m_shaderProgram.Activate();
    return VAO1;
}

void engine::Renderer::SetupFrame() {
    m_shaderProgram.Activate();
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


}

void engine::Renderer::DrawFrame() {
    m_VAO1.Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void engine::Renderer::EndFrame() {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

GLFWwindow* engine::Renderer::GetWindow()
{
    return m_window;
}

engine::Renderer::~Renderer()
{
    m_shaderProgram.Delete();
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

engine::Renderer::Renderer() {
    GLFWInit();

    m_window = SetupWindow();

    m_shaderProgram = Shader("Main\\Shaders\\default.vert",
        "Main\\Shaders\\default.frag");

    m_VAO1 = SetupRender();

}

