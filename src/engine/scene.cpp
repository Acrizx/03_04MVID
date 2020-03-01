#include "engine/scene.hpp"
#include <glad\glad.h>
#include <glm\ext\matrix_clip_space.hpp>
#include <engine\window.hpp>
#include <glm\ext\matrix_transform.hpp>

#include <GLFW/glfw3.h>




Scene::Scene(std::vector<Light> lights,const Shader& shader, const Shader& depth):
_lights(lights),_shader(shader),_depth(depth){
    //_Fbo.createFBO();
}

void Scene::renderScene(Camera camera, std::vector<GameObject*>* gameObjects){
    ////Shadows
    _Fbo.renderShadows();

    _depth.use();
    for each (Light light in _lights)
    {
        _depth.set("lightSpaceMatrix", light.getSpaceMatrix());
    }
    for (size_t i = 0; i < gameObjects->size() ; i++)
    {
        gameObjects->at(i)->render(_depth);
    }

    
    //Scene
    _Fbo.renderScene();

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(camera.getFOV()), static_cast<float>(Window::instance()->getWidth()) / Window::instance()->getHeight(), 0.1f, 100.0f);
    //glm::mat4 proj = glm::ortho(-1.0f, 1.0f, -1.5f, 1.5f, 0.0f, 25.5f);
    //glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 8.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//(glm:vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //glm::mat4 view = glm::lookAt(glm:vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    _shader.use();

    _shader.set("view", view);
    _shader.set("proj", proj);
    _shader.set("viewPos", camera.getPosition());
    _shader.set("depthMap", 2);

    for each (Light light in _lights)
    {
        light.render(_shader, 16);
    }

    for (size_t i = 0; i < gameObjects->size(); i++)
    {
        gameObjects->at(i)->instantiate(_shader);
    }
    /*for each (GameObject* object in _gameObjects)
    {
        object->instantiate(_shader);
    }*/
}


void Scene::clearScene() const {
    _Fbo.deleteFBO();
}