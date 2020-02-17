#include "engine/scene.hpp"
#include <glad\glad.h>
#include <glm\ext\matrix_clip_space.hpp>
#include <engine\window.hpp>



Scene::Scene(std::vector<Light> lights,std::vector<GameObject> gameObjects,const Shader& shader):
_lights(lights),_gameObjects(gameObjects),_shader(shader){}

void Scene::renderScene(Camera camera) const{
    //Shadows
    _Fbo.renderShadows();

    _shader.use();
    for each (Light light in _lights)
    {
        _shader.set("lightSpaceMatrix", light.getSpaceMatrix());
    }
    for each (GameObject object in _gameObjects)
    {
        object.render(_shader);
    }

    
    //Scene
    _Fbo.renderScene();

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), static_cast<float>(Window::instance()->getWidth()) / Window::instance()->getHeight(), 0.1f, 100.0f);
    
    _shader.use();

    _shader.set("view", view);
    _shader.set("proj", proj);
    _shader.set("viewPos", camera.getPosition());
    _shader.set("depthMap", 2);

    for each (Light light in _lights)
    {
        light.render(_shader, 32);
    }

    for each (GameObject object in _gameObjects)
    {
        object.render(_shader);
    }
}


void Scene::clearScene() const {
    _Fbo.deleteFBO();
}