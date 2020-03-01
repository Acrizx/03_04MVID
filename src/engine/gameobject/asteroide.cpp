#include "engine/gameobject/asteroide.hpp"
#include <iostream>
#include <GLFW\glfw3.h>
#include <engine\gameobject\nave.hpp>

Asteroide::Asteroide(Model* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) 
	:GameObject("Enemy", mesh, position, rotation, scale,0.1f) {}




void Asteroide::update() {
	float actualTime = static_cast<float>(glfwGetTime());
	_object.transform.l_Position.y -= (actualTime - getTime()) * 0.4f;
	_object.transform.l_Rotation.x += (actualTime - getTime()) * l_ratationx;
	_object.transform.l_Rotation.y += (actualTime - getTime()) * l_ratationy;
	_object.transform.l_Rotation.z += (actualTime - getTime()) * l_ratationz;
	setTime(actualTime);
}

void Asteroide::onCollider(GameObject* colliderObject)
{
	if (colliderObject->getTag() == "Player") {
		colliderObject->setDestroy(true);
		_destroy = true;
	}
}
