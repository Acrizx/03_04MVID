#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>

#include "engine/camera.hpp"
//#include "engine/geometry/cube.hpp"
#include "engine/input.hpp"
#include "engine/shader.hpp"
//#include "engine/texture.hpp"
#include "engine/window.hpp"
#include <iostream>
#include <engine\light\light.hpp>
//#include <engine\fbo.hpp>
#include <engine\scene.hpp>
#include <engine\gameobject\bala.hpp>
#include <engine\gameobject\asteroide.hpp>
#include <engine\gameobject\nave.hpp>
#include <engine\gameobject\luna.hpp>

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
glm::vec3 lightPos(0.0f, 8.0f, 4.0f);

const float k_shadow_near = 0.0f;
const float k_shadow_far = 25.5f;

float disparaTime = 0.0f;
float spawnTime = 0.0f;
//Input
#pragma region Input
void handleInput(Model* bala, std::vector<GameObject*>* gameObjects, glm::vec3 position) {
    Input* input = Input::instance();

    if (gameObjects->at(0)->getTag() == "Player" && input->isKeyPressed(GLFW_KEY_SPACE) && glfwGetTime() - disparaTime > 0.4f) {
        gameObjects->push_back(new Bala(bala, position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.001f, 0.002f, 0.001f)));
        disparaTime = glfwGetTime();
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
#pragma endregion

//Gamefunctions
#pragma region functions
void spawner(std::vector<GameObject*> *gameObjects, Model* m_asteroide) {
    if (glfwGetTime() - spawnTime > 0.5f) {
        for (size_t i = 0; i < 2; i++)
        {
            float size = 0.01f;//glm::linearRand(0.01f, 0.05f);
            //gameObjects->push_back(new Asteroide(m_asteroide, glm::vec3(glm::linearRand(-0.7f, 0.7f), 1.4f, 0.3f), glm::vec3(0.0f, 0.0f, glm::gaussRand(0.0f, 90.0f)), glm::vec3(size, size, size)));
            gameObjects->push_back(new Asteroide(m_asteroide, glm::vec3(glm::linearRand(-0.7f, 0.7f), 1.4f, 0.3f), glm::vec3(0.0f, 0.0f, glm::gaussRand(0.0f, 90.0f)), glm::vec3(size, size, size)));
        }
        spawnTime = glfwGetTime();
    }
}

void outBounds(std::vector<GameObject*>* gameObjects) {
    for (size_t i = 0; i < gameObjects->size(); i++)
    {
        if (gameObjects->at(i)->getPosition().y < -1.3f || gameObjects->at(i)->getPosition().y > 1.4f || gameObjects->at(i)->Destroy()) {
            gameObjects->erase(gameObjects->begin() + i);
        }
    }
}

void onCollision(std::vector<GameObject*>* gameObjects) {    
    for (size_t i = 0; i < gameObjects->size(); i++)
    {
        for (size_t j = 0/*i + 1*/; j < gameObjects->size(); j++)
        {
            float distance = (gameObjects->at(i)->getPosition().x - gameObjects->at(j)->getPosition().x)/ (gameObjects->at(i)->getPosition().y - gameObjects->at(j)->getPosition().y);
            float distance2 = glm::distance(gameObjects->at(i)->getPosition(), gameObjects->at(j)->getPosition());
            if (glm::distance(gameObjects->at(i)->getPosition(), gameObjects->at(j)->getPosition()) < gameObjects->at(j)->getDistanceCollider() + gameObjects->at(i)->getDistanceCollider()) {
                gameObjects->at(i)->onCollider(gameObjects->at(j));
            }
        }
    }
}
#pragma endregion


int main(int, char* []) {
    Window* window = Window::instance();

    glClearColor(0.0f, 0.3f, 0.6f, 1.0f);
    
    std::vector<Light> lights{ Light(lightPos, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.6f, 0.6f, 0.6f),
        glm::ortho(-1.0f, 1.0f, -1.5f, 1.5f, k_shadow_near, k_shadow_far),
        glm::lookAt(lightPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),true) };
    
    Model m_luna("../assets/models/FinalProject/Luna/Luna.obj");
    Model m_nave("../assets/models/FinalProject/Nave/Nave.obj");
    Model m_bala("../assets/models/FinalProject/Bullet/Bullet.obj");
    Model m_asteroide("../assets/models/FinalProject/AsteroidA/Asteroid.obj");
    //Model m_asteroide("../assets/models/FinalProject/ASTEROID_1_/Asteroid_1_/Asteroid_1_LOW_MODEL_.obj");
//D:\Proyects\MasterProyects\ProgramacionAvanzada\Motor\REngine\03_04MVID\assets\models\FinalProject\ASTEROID_1_\Asteroid_1_
    Shader s_phong("../projects/FINAL/phong.vs", "../projects/FINAL/blinn.fs");
    Shader s_depth("../projects/FINAL/depth.vs", "../projects/FINAL/depth.fs");


    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    Input::instance()->setKeyPressedCallback(onKeyPress);

    glfwSetTime(0);
    GameObject* luna = new Luna(&m_luna, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.01f, 0.01f, 0.01f));
    GameObject* nave = new Nave(&m_nave, glm::vec3(0.0f, -0.9f, 0.3f), glm::vec3(90.0f, 180.0f, 0.0f), glm::vec3(0.00035f, 0.00035f, 0.00035f));
    std::vector<GameObject*> gameObjects {nave ,luna };

    Scene scene(lights, s_phong, s_depth);
    while (window->alive()) {

        spawner(&gameObjects, &m_asteroide);
        handleInput(&m_bala,&gameObjects,gameObjects[0]->getPosition());
        scene.renderScene(camera, &gameObjects);
        onCollision(&gameObjects);
        outBounds(&gameObjects);
        window->frame(); 
    }
    scene.clearScene();
    return 0;
}