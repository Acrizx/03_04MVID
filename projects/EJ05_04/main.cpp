#include <glad/glad.h>

#include "engine/window.hpp"
#include "engine/shader.hpp"

#include "engine/texture.hpp"
#include "engine/geometry/cube.hpp"
#include "engine/geometry/quad.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <GLFW/glfw3.h>

void handleInput() {/*Intentionally Left BLank*/ }

void render(const Geometry& geom, const Shader& shader, Texture& tex, float radians, const glm::vec3 position) {

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, radians, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::translate(model, position);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 proj = glm::perspective(glm::radians(80.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shader.use();

    tex.use(shader, "tex", 0);

    shader.set("model", model);
    shader.set("view", view);
    shader.set("proj", proj);  //TODO const mat4
    geom.render();
}

int main(int, char* []) {
    Window* window = Window::instance();
    srand(time(0));

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader shader("../projects/EJ05_04/vertex.vs", "../projects/EJ05_04/fragment.fs");
    const Cube cube(1.0f); const Cube cube2(0.5f);
    const Quad quad(10.0f);
    Geometry geometries[] = {cube, cube2, cube, cube2, cube };
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

    while (window->alive()) {

        handleInput();
        render(quad, shader, tex, glm::radians(-90.0f), glm::vec3(0.0f, -1.0f, -5.0f));
        for (int i = 0; i < sizeof(geometries)/ sizeof(geometries[0]); i++)
        {
            render(geometries[i], shader, tex, 0.0f, positions[i]);
        }
        window->frame();
        glClear(GL_COLOR_BUFFER_BIT);
    }

    return 0;
}