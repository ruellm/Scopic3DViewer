#pragma once

#include "common.h"

namespace intersect
{
    bool MousePick(const glm::vec3& position,
                   const glm::vec3& mn,
                   const glm::vec3& mx,
                   const glm::vec3& rayPos,
        const glm::vec3& rayDir, glm::vec3* hitPos);

    bool RaySlabIntersect(float slabmin, float slabmax, float raystart,
                          float rayend, float& tbenter, float& tbexit);
}
