#include "shape.h"

Shape::Shape(Shape::Type type, const std::string& id)
    : m_type(type)
    , m_id(id)
{
    m_position = glm::vec3(0, 0, 0);
}

void Shape::setMesh(const Mesh& mesh)
{
    m_mesh = mesh;
}

Mesh& Shape::mesh()
{
    return m_mesh;
}

Material& Shape::material()
{
    return m_material;
}

glm::vec3& Shape::position()
{
    return m_position;
}

Shape::Type Shape::type() const
{
    return m_type;
}

std::string Shape::id() {
    return m_id;
}

glm::mat4 Shape::worldTransform()
{
    glm::mat4 world(1.0f);
    world = glm::translate(world, m_position);

    //.. Other transform can be added here like scale and rotation

    return world;
}
