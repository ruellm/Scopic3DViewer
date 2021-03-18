#pragma once

#include "common.h"

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
};

struct Light {
    glm::vec3 position;
    float ambientStrength;
    Material material;
};
