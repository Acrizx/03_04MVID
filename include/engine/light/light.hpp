#ifndef __LIGHT_H__
#define __LIGHT_H__
#include <glm/glm.hpp>
#include <engine\shader.hpp>

const glm::vec3 l_Ambient;
const glm::vec3 l_Diffuse;
const glm::vec3 l_Specular;
const bool l_Shadows = false;
const glm::mat4 l_Projection;
const glm::mat4 l_View;

class Light {
public:
    Light(glm::vec3 position, glm::vec3 ambient = l_Ambient, glm::vec3 diffuse = l_Diffuse, glm::vec3 specular = l_Specular
        , glm::mat4 projection = l_Projection, glm::mat4 view = l_View, bool shadows = l_Shadows);

    glm::vec3 getPosition() const;
    glm::vec3 getAmbient() const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;
    glm::mat4 getSpaceMatrix() const;
    bool getShadows() const;
    void render(const Shader& shader, int shinness) const;

private:
    void calculatematrix();

private:
    glm::vec3 _position, _ambient, _diffuse, _specular;
    glm::mat4 _projection, _view, _spacematrix;
    bool _shadows;
};

#endif
