#ifndef SHAPE_H
#define SHAPE_H

#include "common.h"
#include "mesh.h"
#include "material.h"

class Shape
{
public:
    enum class Type : uint8_t {
        Cube
    };

public:
    Shape(Type type, const std::string& id);

    void setMesh(const Mesh& mesh);

    Mesh& mesh();

    Material& material();

    glm::vec3& position();

    glm::mat4 worldTransform();

    Shape::Type type() const;

    std::string id();

private:
    Mesh            m_mesh;
    Material        m_material;
    glm::vec3       m_position;
    //.. Other transform can be added here like scale and rotation

    glm::mat4       m_world;
    Type            m_type;
    std::string     m_id;
};

using ShapesMap = std::map<std::string, Shape>;

#endif // SHAPE_H
