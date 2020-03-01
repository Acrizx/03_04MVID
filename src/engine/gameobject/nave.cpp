#include "engine/gameobject/nave.hpp"
#include <engine\input.hpp>
#include "engine/gameobject/bala.hpp"

Nave::Nave(Model* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) 
    :GameObject("Player", mesh, position, rotation, scale, 0.1f) {}

float velocidad = 0.5f;
float limitex = 0.7f;

void movePlayer(float dt, Object* _object) {
    Input* input = Input::instance();

    if (input->isKeyPressed(GLFW_KEY_A) && _object->transform.l_Position.x >= -limitex) {
        _object->transform.l_Position.x -= (dt) *velocidad;
        _object->transform.l_Rotation.z = -30;
    }else
    if (input->isKeyPressed(GLFW_KEY_D) && _object->transform.l_Position.x <= limitex) {
        _object->transform.l_Position.x += (dt) *velocidad;
        _object->transform.l_Rotation.z = 30;
    }
    else {
        _object->transform.l_Rotation.z = 0;
    }
}

void Nave::update() {
    float actualTime = static_cast<float>(glfwGetTime());
    movePlayer(actualTime - getTime(),&_object);
    setTime(actualTime);
}

void Nave::onCollider(GameObject* colliderObject)
{
}



