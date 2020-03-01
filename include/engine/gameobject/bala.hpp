#ifndef __BALA_H__
#define __BALA_H__ 1

#include "gameobject.hpp"
#include <iostream>
#include <GLFW\glfw3.h>

class Bala final : public GameObject {
public:
//    Bala() = delete;
    Bala(Model* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    void update() override;
    void onCollider(GameObject* colliderObject) override;
//
//    void update();
//    void start();
//
//    void instantiate(const Shader& shader);
//
//private:
//    const Model* _bala;
//    Transform _transform;
};
#endif