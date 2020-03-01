#ifndef __NAVE_H__
#define __NAVE_H__ 1

#include "gameobject.hpp"
#include <iostream>
#include <GLFW\glfw3.h>

class Nave final : public GameObject {
public:
    //    Bala() = delete;
    Nave(Model* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    void update() override;
    void onCollider(GameObject* colliderObject) override;


};
#endif