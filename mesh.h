#pragma once

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class Mesh
{
public:
    Mesh();
    Mesh(QOpenGLVertexArrayObject* vao, QOpenGLBuffer* vbo, int count, bool cloned = false);

    QOpenGLVertexArrayObject* vao();

    int vertexCount() const;

    void cleanUp();

private:
    QOpenGLVertexArrayObject*   m_vao;
    QOpenGLBuffer*              m_vbo;
    int                         m_vertexCount;
    bool                        m_isCloned;
};
