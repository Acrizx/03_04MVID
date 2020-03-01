#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__ 1

#include <glm/glm.hpp>
#include <engine\mesh.hpp>
#include <engine\shader.hpp>
#include <engine\geometry\geometry.hpp>
#include <engine\model.hpp>

struct Transform {
    glm::vec3 l_Position;
    glm::vec3 l_Rotation;
    glm::vec3 l_Scale;
};

struct Object {
    Model* mesh;
    Transform transform;
};

//const Object object = { 0 };

class GameObject {
public:
    //Constructores
    GameObject(Object object);
    GameObject(Model* mesh, Transform transform);
    GameObject(std::string tag ,Model* mesh, glm::vec3 position, glm::vec3 rotation,glm::vec3 scale);
    GameObject(std::string tag, Model* mesh, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, float distanceCollider);

    //Methods
    void render(const Shader& shader);
    void instantiate(const Shader& shader);

    //Abstract Methods
    virtual void update() = 0;
    virtual void onCollider(GameObject* collisionObject) = 0;

    //Get & Set
    void setPosition(Transform transform);
    glm::vec3 getPosition();
    void setTime(float time);
    float getTime();
    std::string getTag();
    float getDistanceCollider();
    bool Destroy();
    void setDestroy(bool destroy);

protected:
    Object _object;
    float _time; 
    std::string _tag;
    float _distanceCollider;
    bool _destroy;
};

#endif
