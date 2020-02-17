#ifndef __FBO_H__
#define __FBO_H__

#include <cstdint>
#include <iostream>
#include <glm\fwd.hpp>

const uint32_t l_width = 1024;
const uint32_t l_height = 1024;
const float l_borderColor[]{ 1.0f, 1.0f, 1.0f, 1.0f };

class Fbo {
public:
    Fbo();

    std::pair<uint32_t, uint32_t> getFbo() const;
    uint32_t getWidth() const;
    uint32_t getHeight() const;

    void createFBO();
    void deleteFBO() const;
    void renderShadows() const;
    void renderScene() const;

private:
    std::pair<uint32_t, uint32_t> _fboPair;
    uint32_t _fbo;
    uint32_t _depthMap;
};
#endif