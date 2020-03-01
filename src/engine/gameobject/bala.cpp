#include "engine/gameobject/bala.hpp"

Bala::Bala(Model* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) 
	:GameObject("Bullet",mesh, position, rotation, scale,0.05f) {}

void Bala::update() {
	float actualTime = static_cast<float>(glfwGetTime());
	_object.transform.l_Position.y += (actualTime - getTime())*1.5f;
	setTime(actualTime);
}

void Bala::onCollider(GameObject* colliderObject)
{
	if (colliderObject->getTag() == "Enemy") {
		colliderObject->setDestroy(true);
		_destroy = true;
	}
}
