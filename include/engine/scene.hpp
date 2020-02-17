#ifndef __SCENE_H__
#define __SCENE_H__

#include <cstdint>
#include <vector>
#include <engine\light\light.hpp>
#include <engine\gameobject.hpp>
#include <engine\fbo.hpp>
#include <engine\camera.hpp>
#include <engine\geometry\geometry.hpp>

class Scene {
public:
    Scene(std::vector<Light> lights, std::vector<GameObject> gameObjects, const Shader& shader);

    void renderScene(Camera camera) const;
    void clearScene() const;

private:
    std::vector<Light> _lights;
    std::vector<GameObject> _gameObjects;
    Shader& _shader;
    Fbo _Fbo;
};

#endif