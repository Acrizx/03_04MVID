#ifndef __ASTEROIDE_H__
#define __ASTEROIDE_H__ 1

#include "gameobject.hpp"
#include <glm\gtc\random.hpp>

const float l_ratationx = glm::gaussRand(4.0f, 6.f);
const float l_ratationy = glm::gaussRand(2.0f, 4.f);
const float l_ratationz = glm::gaussRand(6.0f, 8.f);

class Asteroide final : public GameObject {


public:
    //    Bala() = delete;
    Asteroide(Model* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
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