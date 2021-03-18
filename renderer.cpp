#include <QOpenGLFunctions>

#include "renderer.h"
#include "meshbuilder.h"

Renderer::Renderer()
    : m_shader(nullptr)
{
}

Renderer::~Renderer()
{
    SAFE_DELETE(m_shader);
}

void Renderer::load(const QString& vshaderFile, const QString& fshaderFile)
{
    m_shader = new QOpenGLShaderProgram;
    m_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, vshaderFile);
    m_shader->addShaderFromSourceFile(QOpenGLShader::Fragment,  fshaderFile);
    m_shader->link();
}


void Renderer::bind(const glm::mat4& viewMat, const glm::mat4& projMat)
{
    if(m_shader == nullptr)
        return;

    m_shader->bind();

    int projection      = m_shader->uniformLocation("projection");
    int view            = m_shader->uniformLocation("view");

    m_shader->setUniformValue(projection, QMatrix4x4(glm::value_ptr(projMat)).transposed());
    m_shader->setUniformValue(view, QMatrix4x4(glm::value_ptr(viewMat)).transposed());
}

void Renderer::draw(Mesh& mesh, GLenum primType)
{
    QOpenGLFunctions* glFuncs = QOpenGLContext::currentContext()->functions();

    QMatrix4x4 world;
    world.setToIdentity();

    int model = m_shader->uniformLocation("model");
    m_shader->setUniformValue(model, world);

    mesh.vao()->bind();
    glFuncs->glDrawArrays(primType, 0, mesh.vertexCount());
    mesh.vao()->release();
}

ShapesRenderer::ShapesRenderer()
    : Renderer()
{
}

ShapesRenderer::~ShapesRenderer()
{
}


void ShapesRenderer::drawCubes(ShapesMap shapes)
{
    /** Get the original vao for our cloned object */
    auto vao = builder::GetCubeMeshVao();
    if(vao == nullptr)
        return;

    draw(vao, shapes);
}

void ShapesRenderer::SetLight(const Light& light)
{
    m_light = light;
}

void ShapesRenderer::draw(QOpenGLVertexArrayObject* vao, ShapesMap shapes)
{
    QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();

    // bind the buffer
    vao->bind();

    int lightPosId = m_shader->uniformLocation("light.position");
    int lightAmbientId= m_shader->uniformLocation("light.ambient");
    int lightDiffuseId = m_shader->uniformLocation("light.diffuse");
    int lightAmbientStrengthId =  m_shader->uniformLocation("light.ambientStrength");

    QVector3D lightPos(m_light.position.x,
                       m_light.position.y,
                       m_light.position.z);

    m_shader->setUniformValue(lightPosId, lightPos);

    QVector3D lightAmbient(m_light.material.ambient.x,
                           m_light.material.ambient.y,
                           m_light.material.ambient.y);

    m_shader->setUniformValue(lightAmbientId, lightAmbient);

    QVector3D lightDiffuse(m_light.material.diffuse.x,
                           m_light.material.diffuse.y,
                           m_light.material.diffuse.y);

    m_shader->setUniformValue(lightDiffuseId, lightDiffuse);

    m_shader->setUniformValue(lightAmbientStrengthId, m_light.ambientStrength);

    int objectColorId   = m_shader->uniformLocation("objectColor");
    int model = m_shader->uniformLocation("model");

    ShapesMap::iterator it = shapes.begin();

    while(it != shapes.end())
    {
        auto diffuseColor = it->second.material().diffuse;

        m_shader->setUniformValue(objectColorId, QVector3D(diffuseColor.x,
                                                               diffuseColor.y,
                                                               diffuseColor.z));

        auto world = it->second.worldTransform();

        m_shader->setUniformValue(model, QMatrix4x4(glm::value_ptr(world)).transposed());
        glFuncs->glDrawArrays(GL_TRIANGLES, 0, 36);

        it++;
    }
}
