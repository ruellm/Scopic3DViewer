#pragma once

#include <QOpenGLShaderProgram>
#include "common.h"

#include "shape.h"
#include "material.h"

class Renderer {
public:
    Renderer();

    virtual ~Renderer();

    virtual void load(const QString& vshaderFile, const QString& fshaderFile);

    void bind(const glm::mat4& viewMat, const glm::mat4& projMat);

    void draw(Mesh& mesh, GLenum primType);

protected:
    QOpenGLShaderProgram* m_shader;
};

class ShapesRenderer : public Renderer
{
public:
    ShapesRenderer();
    ~ShapesRenderer();


    void drawCubes(ShapesMap shapes);

    void SetLight(const Light& light);

private:
    Light       m_light;

    void draw(QOpenGLVertexArrayObject* vao, ShapesMap shapes);
};


