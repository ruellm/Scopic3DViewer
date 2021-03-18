#include "intersect.h"

namespace intersect {

bool MousePick(
        const glm::vec3& position,
        const glm::vec3& mn,
        const glm::vec3& mx,
        const glm::vec3& rayPos,
        const glm::vec3& rayDir, glm::vec3* hitPos)

{
    glm::mat4 world(1.0f);
    world = glm::translate(world, position);

    glm::vec4 min = world * glm::vec4(mn, 1);
    glm::vec4 max = world * glm::vec4(mx, 1);
    glm::vec3 rayEnd = rayPos + (rayDir * 1000.0f);

    // initialise to the segment's boundaries.
    float tenter = 0.0f, texit = 1.0f;

    // test X slab
    if (!RaySlabIntersect(min.x, max.x, rayPos.x, rayEnd.x, tenter, texit))
    {
        return false;
    }

    // test Y slab
    if (!RaySlabIntersect(min.y, max.y, rayPos.y, rayEnd.y, tenter, texit))
    {
        return false;
    }

    // test Z slab
    if (!RaySlabIntersect(min.z, max.z, rayPos.z, rayEnd.z, tenter, texit))
    {
        return false;
    }

    *hitPos = rayPos + (rayDir * 1000.0f * tenter);

    return  true;
}

// Based on Gamedev.net line geometry testing
// this is using SLAB testing

bool RaySlabIntersect(float slabmin, float slabmax, float raystart, float rayend, float& tbenter, float& tbexit)
{
    float raydir = rayend - raystart;

    // ray parallel to the slab
    if (fabs(raydir) < 1.0E-9f)
    {
        // ray parallel to the slab, but ray not inside the slab planes
        if(raystart < slabmin || raystart > slabmax)
        {
            return false;
        }
            // ray parallel to the slab, but ray inside the slab planes
        else
        {
            return true;
        }
    }

    // slab's enter and exit parameters
    float tsenter = (slabmin - raystart) / raydir;
    float tsexit = (slabmax - raystart) / raydir;

    // order the enter / exit values.
    if(tsenter > tsexit)
    {
        //swapf(tsenter, tsexit);
        float temp = tsenter;
        tsenter = tsexit;
        tsexit = temp;
    }

    // make sure the slab interval and the current box intersection interval overlap
    if (tbenter > tsexit || tsenter > tbexit)
    {
        // nope. Ray missed the box.
        return false;
    }
        // yep, the slab and current intersection interval overlap
    else
    {
        // update the intersection interval
        tbenter = std::max(tbenter, tsenter);
        tbexit = std::min(tbexit, tsexit);
        return true;
    }
}
}
