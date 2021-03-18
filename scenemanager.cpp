#include "scenemanager.h"
#include "meshbuilder.h"
#include "intersect.h"

SceneManager::SceneManager()
{
    /** Default light settings */
    m_defaultLight.ambientStrength = 0.1f;
    m_defaultLight.material.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    m_defaultLight.material.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
}

void SceneManager::load() {

    m_shapesRenderer.load("shaders/shape_vshader", "shaders/shape_fshader");

    /** We make sure all the objects are created within the rendering context */
    builder::LoadPrefab();
}

Shape* SceneManager::createShape(Shape::Type type, const std::string& id)
{
    ShapesMap::iterator it = m_shapes.find(id);
    if (it != m_shapes.end()) {
        throw("Shape ID already exist");
    }

    switch(type) {
    case Shape::Type::Cube:
    {
        Shape shape(type, id);

        /** Setting the mesh for cloned items is useless as original VAO are used for rendering*/
        auto mesh = builder::CloneCubeMesh();
        shape.setMesh(mesh);

        m_shapes.insert(std::make_pair(id, shape));
        return &m_shapes.find(id)->second;
    };
    }

    throw("Shape Type not supported");

}

void SceneManager::renderAll()
{
    /** For this demo light is on the camera's position*/
    m_defaultLight.position = m_camera.getPosition();
    m_shapesRenderer.SetLight(m_defaultLight);

    m_shapesRenderer.bind(m_camera.getViewMatrix(), m_projMatrix);
    m_shapesRenderer.drawCubes(m_shapes);
}

Shape* SceneManager::pickShape(int x, int y)
{
    /** perform ray test */
    glm::vec3 hitPos;
    glm::vec3 startRay, dir;

    BuildRay(x, y, startRay, dir);

    /** The minimum and maximum coordinate of the cube (before any resize is applied) */
    glm::vec3 min(-0.5f, -0.5f, -0.5f);
    glm::vec3 max(0.5f, 0.5f, 0.5f);

    ShapesMap::iterator it = m_shapes.begin();
    while (it != m_shapes.end()) {
        if(intersect::MousePick(it->second.position(), min, max, startRay, dir, &hitPos)) {
            return &it->second;
        }
        it++;
    }

    return nullptr;
}

Shape* SceneManager::getShape(const std::string& id)
{
    ShapesMap::iterator it = m_shapes.find(id);
    if (it == m_shapes.end()) {
        return NULL;
    }

    return &it->second;
}

void SceneManager::removeShape(const std::string& id)
{
    ShapesMap::iterator it = m_shapes.find(id);
    if (it != m_shapes.end()) {
        m_shapes.erase(it);
    }
}

Camera* SceneManager::initCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up)
{
    m_camera.lookAt(position, up, target);
    return &m_camera;
}

Camera& SceneManager::camera()
{
    return m_camera;
}

void SceneManager::resizeViewPort(int width, int height)
{
    m_cacheWidth = width;
    m_cacheHeight = height;
    m_projMatrix = glm::perspective(glm::radians(45.0f), GLfloat(width) / height, 0.01f, 100.0f);
}

glm::mat4 SceneManager::projectionMatrix()
{
    return m_projMatrix;
}

void SceneManager::BuildRay(int x, int y, glm::vec3& start, glm::vec3& dir)
{
    glm::mat4 viewMatrix = m_camera.getViewMatrix();

    glm::vec4 viewport = glm::vec4(0, 0, m_cacheWidth, m_cacheHeight);

    start = glm::unProject(
                glm::vec3(x, m_cacheHeight - y, 0.0),
                viewMatrix, m_projMatrix, viewport);

    glm::vec3 end = glm::unProject(
                glm::vec3(x, m_cacheHeight - y, 1.0),
                viewMatrix, m_projMatrix, viewport);

    dir = glm::normalize(end - start);
}

void SceneManager::setLight(const Light& light)
{
    m_defaultLight = light;
}
