#ifndef __SCENE_H__
#define __SCENE_H__

#include <cstdint>
#include <vector>
#include <engine\light\light.hpp>
#include <engine\gameobject\gameobject.hpp>
#include <engine\fbo.hpp>
#include <engine\camera.hpp>
#include <engine\geometry\geometry.hpp>

class Scene {
public:
    Scene(std::vector<Light> lights,const Shader& shader, const Shader& depth);

    void renderScene(Camera camera, std::vector<GameObject*>* gameObjects);
    void clearScene() const;
    //void update

private: 
    std::vector<Light> _lights;
    //std::vector<GameObject*> *_gameObjects;
    const Shader& _shader;
    const Shader& _depth;
    Fbo _Fbo;
};

#endif