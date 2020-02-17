#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
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
    const Model* mesh;
    const Geometry& geometry;
    Transform transform;
};
//const Object object = { 0 };

class GameObject {
public:
    GameObject(Object object);
    GameObject(Model* mesh, const Geometry& geometry, Transform transform);
    GameObject(Model* mesh, const Geometry& geometry, glm::vec3 position, glm::vec3 rotation,glm::vec3 scale);

    void update() const;
    void start() const;
    void render(const Shader& shader);
    Transform getTransform() const;
    
private:
    Object _object;
};

#endif
