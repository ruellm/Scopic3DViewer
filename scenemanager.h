#pragma once

#include <vector>
#include "shape.h"
#include "camera.h"
#include "renderer.h"
#include "material.h"

class SceneManager
{
public:
    SceneManager();

    void load();

    Shape* createShape(Shape::Type type, const std::string& id);

    void renderAll();

    Shape* pickShape(int x, int y);

    Shape* getShape(const std::string& id);

    void removeShape(const std::string& id);

    void resizeViewPort(int width, int height);

    Camera* initCamera(const glm::vec3& position, const glm::vec3& target, const glm::vec3& Up);

    Camera& camera();

    glm::mat4 projectionMatrix();

    /**
     *  For simplicity of this sample we only have one light already added
     *  users will only need to set its parameters instead of creating lights
     *  supporting createLight() means we need to support multiple lights as well
    */
    void setLight(const Light& light);

public:

    ShapesMap       m_shapes;           // represents a Cube list
    Camera          m_camera;
    glm::mat4       m_projMatrix;

    int             m_cacheWidth;
    int             m_cacheHeight;

    Light           m_defaultLight;

    ShapesRenderer  m_shapesRenderer;

    void BuildRay(int x, int y, glm::vec3& start, glm::vec3& dir);
};


