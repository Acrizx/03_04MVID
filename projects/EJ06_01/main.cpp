#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "engine/camera.hpp"
#include "engine/geometry/cube.hpp"
#include "engine/geometry/quad.hpp"
#include "engine/input.hpp"
#include "engine/shader.hpp"
#include "engine/texture.hpp"
#include "engine/window.hpp"
#include "engine/geometry/sphere.hpp"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastFrame = 0.0f;
float lastX, lastY;
bool firstMouse = true;

void handleInput(float dt) {
    Input* input = Input::instance();
    if (input->isKeyPressed(GLFW_KEY_W)) {
        camera.handleKeyboard(Camera::Movement::Forward, dt);
    }
    if (input->isKeyPressed(GLFW_KEY_S)) {
        camera.handleKeyboard(Camera::Movement::Backward, dt);
    }
    if (input->isKeyPressed(GLFW_KEY_A)) {
        camera.handleKeyboard(Camera::Movement::Left, dt);
    }
    if (input->isKeyPressed(GLFW_KEY_D)) {
        camera.handleKeyboard(Camera::Movement::Right, dt);
    }
}

void onKeyPress(int key, int action) {
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        Window::instance()->setCaptureMode(true);
    }

    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        Window::instance()->setCaptureMode(false);
    }
}

void onMouseMoved(float x, float y) {
    if (firstMouse) {
        firstMouse = false;
        lastX = x;
        lastY = 0.0f;
    }

    const float xoffset = x - lastX;
    const float yoffset = lastY - y;
    lastX = x;
    //lastY = y;

    camera.handleMouseMovement(xoffset, lastY);
}

void onScrollMoved(float x, float y) {
    camera.handleMouseScroll(y);
}

void render(const Geometry& geom, const Shader& shader, Texture& tex, float radians, const glm::vec3 position) {

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model,position);
    model = glm::rotate(model, radians, glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

   
    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);

    shader.use();

    tex.use(shader, "tex", 0);

    shader.set("model", model);
    shader.set("view", camera.getViewMatrix());
    shader.set("proj", proj);  //TODO const mat4

    geom.render();
}

int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader shader("../projects/AG06/vertex.vs", "../projects/AG06/fragment.fs");
    //const Cube cube(1.0f);
    const Sphere sphere(1.0f, 50, 50);
    const Cube cube(1.0f); const Cube cube2(0.5f);
    const Quad quad(10.0f);
    Geometry geometries[] = { cube, cube2, cube, cube2, cube };
    const glm::vec3 positions[] = {
        glm::vec3(2.0f, -0.5, -5.0f),
        glm::vec3(1.0f, -0.75, -3.0f),
        glm::vec3(2.5f, -0.5, -2.0f),
        glm::vec3(0.0f, -0.75, -5.0f),
        glm::vec3(-2.5f, -0.5, -10.0f)
    };

    Texture tex("../assets/textures/blue_blocks.jpg", Texture::Format::RGB);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    Input::instance()->setKeyPressedCallback(onKeyPress);
    Input::instance()->setMouseMoveCallback(onMouseMoved);
    Input::instance()->setScrollMoveCallback(onScrollMoved);

    while (window->alive()) {
        const float currentFrame = glfwGetTime();
        const float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        handleInput(deltaTime);
        render(quad, shader, tex, glm::radians(-90.0f), glm::vec3(0.0f, -1.0f, -5.0f));
        for (int i = 0; i < sizeof(geometries) / sizeof(geometries[0]); i++)
        {
            render(geometries[i], shader, tex, 0.0f, positions[i]);
        }
        window->frame();
        glClear(GL_COLOR_BUFFER_BIT);
    }

    return 0;
}