#include "engine/gameobject/gameobject.hpp"
#include <glm/glm.hpp>
#include <engine\mesh.hpp>
#include <glm\ext\matrix_transform.hpp>
#include <GLFW\glfw3.h>


GameObject::GameObject(Object object) :_object(object) {
    _time = glfwGetTime();
    _destroy = false;
}
GameObject::GameObject(Model* mesh, Transform transform)
    : _object({ mesh, transform }) {
    _time = glfwGetTime();
    _destroy = false;
    }

GameObject::GameObject(std::string tag, Model* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : _object({ mesh, { position,rotation,scale } }){
    _time = glfwGetTime();
    _tag = tag;
    _destroy = false;
}

GameObject::GameObject(std::string tag, Model* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float distanceCollider)
    : _object({ mesh, { position,rotation,scale } }),_distanceCollider(distanceCollider) {
    _time = glfwGetTime();
    _tag = tag;
    _destroy = false;
}



void GameObject::render(const Shader& shader) {
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, _object.transform.l_Position);
    model = glm::rotate(model, glm::radians(_object.transform.l_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(_object.transform.l_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(_object.transform.l_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, _object.transform.l_Scale);
    shader.set("model", model);
    glm::mat3 normalMat = glm::inverse(glm::transpose(glm::mat3(model)));
    shader.set("normalMat", normalMat);
    _object.mesh->render(shader);
}

//void GameObject::setmesh(const Model* mesh) {
//    _meshGO = mesh;
//}
//
//void GameObject::setTransform(Transform transform) {
//    _transformGO = transform;
//}

void GameObject::instantiate(const Shader& shader)
{
    update();
    render(shader);
}

void GameObject::update()
{
}

void GameObject::setPosition(Transform transform)
{
    _object.transform = transform;
}

glm::vec3 GameObject::getPosition()
{
    return _object.transform.l_Position;
}

void GameObject::setTime(float time)
{
    _time = time;
}

float GameObject::getTime()
{
    return _time;
}

std::string GameObject::getTag()
{
    return _tag;
}

float GameObject::getDistanceCollider()
{
    return _distanceCollider;
}

bool GameObject::Destroy()
{
    return _destroy;
}

void GameObject::setDestroy(bool destroy)
{
    _destroy = destroy;
}

