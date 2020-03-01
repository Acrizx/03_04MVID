#include "engine/gameobject/luna.hpp"

Luna::Luna(Model* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) :GameObject("Back", mesh, position, rotation, scale) {}

void Luna::update() {
}

void Luna::onCollider(GameObject* colliderObject)
{
}
