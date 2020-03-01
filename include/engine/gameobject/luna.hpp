#ifndef __LUNA_H__
#define __LUNA_H__ 1

#include "gameobject.hpp"
#include <iostream>
#include <GLFW\glfw3.h>

class Luna final : public GameObject {
public:
    //    Bala() = delete;
    Luna(Model* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    void update() override;
    void onCollider(GameObject* colliderObject) override;


};
#endif