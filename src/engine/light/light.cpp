#include "engine/light/light.hpp"


Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::mat4 projection, glm::mat4 view, bool shadows)
:_position(position), _ambient(ambient),_diffuse(diffuse), _specular(specular),_projection(projection),_view(view),_shadows(shadows){
	calculatematrix();
}


glm::vec3 Light::getPosition() const {
	return _position;
}
glm::vec3 Light::getAmbient() const {
	return _ambient;
}
glm::vec3 Light::getDiffuse() const {
	return _diffuse;
}
glm::vec3 Light::getSpecular() const {
	return _specular;
}
glm::mat4 Light::getSpaceMatrix() const {
	return _spacematrix;
}
bool Light::getShadows() const {
	return _shadows;
}

void Light::calculatematrix() {
	_spacematrix = _projection * _view;
}

void Light::render(const Shader& shader, int shinness) const {
	shader.set("light.position", _position);
	shader.set("light.ambient", _ambient);
	shader.set("light.diffuse", _diffuse);
	shader.set("light.specular", _specular);
	shader.set("material.shininess", shinness);
	shader.set("lightSpaceMatrix", _spacematrix);
}