#include <glad/glad.h>

#include "engine/window.hpp"
#include "engine/shader.hpp"

#include "engine/texture.hpp"
#include "engine/geometry/cube.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <GLFW/glfw3.h>

void handleInput() {/*Intentionally Left BLank*/ }

void render(const Geometry& geom, const Shader& shader, Texture& tex, glm::vec3 position) {
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, static_cast<float>(glfwGetTime())* glm::radians(20.0f), glm::vec3(0.5f, 1.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, position);

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    shader.use();

    tex.use(shader, "tex", 0);

    shader.set("model", model);
    shader.set("view", view);
    shader.set("proj", proj);  //TODO const mat4

    geom.render();
}

int main(int, char* []) {
    srand(time(0));
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);

    const Shader shader("../projects/EJ05_01/vertex.vs", "../projects/EJ05_01/fragment.fs");

    //Centro del circulo
    glm::vec3 centro = glm::vec3(glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, 1.0f), glm::linearRand(-1.0f, -10.0f));
    //Radio del circulo
    float radio = glm::linearRand(0.0f,1.0f);
    float size = (radio * cosf(45))*2;
    const Cube cube(size);

    Texture tex("../assets/textures/blue_blocks.jpg", Texture::Format::RGB);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    while (window->alive()) {
        handleInput();
        render(cube, shader, tex, centro);
        window->frame();
    }

    return 0;
}