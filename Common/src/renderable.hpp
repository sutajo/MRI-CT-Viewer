#pragma once

#include <glm/glm.hpp>

#include "shader.hpp"

class Renderable
{
    virtual void prepareShader(Shader&) = 0;
    virtual void render(Shader&, glm::mat4) = 0; 
};