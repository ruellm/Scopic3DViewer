#include "mesh.h"
#include "common.h"

Mesh::Mesh()
    : m_vao(nullptr)
    , m_vbo(nullptr)
    , m_vertexCount(0)
    , m_isCloned(false)
{
}

Mesh::Mesh(QOpenGLVertexArrayObject* vao, QOpenGLBuffer* vbo, int count, bool cloned)
    : m_vao(vao)
    , m_vbo(vbo)
    , m_vertexCount(count)
    , m_isCloned(cloned)
{
}

QOpenGLVertexArrayObject* Mesh::vao()
{
    return m_vao;
}

int Mesh::vertexCount() const
{
    return m_vertexCount;
}

void Mesh::cleanUp() {
    if(!m_isCloned) {
        SAFE_DELETE(m_vao);
        SAFE_DELETE(m_vbo);
    }
}
