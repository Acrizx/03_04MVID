#include "engine/gameobject.hpp"
#include <glm/glm.hpp>
#include <engine\mesh.hpp>
#include <glm\ext\matrix_transform.hpp>

GameObject::GameObject(Object object) :_object(object) {
}
GameObject::GameObject(Model* mesh, const Geometry& geometry, Transform transform)
    : _object({ mesh,geometry, transform }) {
    }

GameObject::GameObject(Model* mesh, const Geometry& geometry, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
    : _object({ mesh, geometry,{ position,rotation,scale } }){}

void GameObject::update() const {
}

void GameObject::start() const {
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
    if (_object.mesh->meshes_.size() > 0) {
        _object.mesh->render(shader);
    }
    else {
        _object.geometry.render();
    }
}

Transform GameObject::getTransform() const {
    return _object.transform;
}


