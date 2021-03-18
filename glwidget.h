#ifndef GLWIDGETS_H
#define GLWIDGETS_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "scenemanager.h"

#include "camera.h"

class GLWidget : public QOpenGLWidget, public QOpenGLFunctions
{
public:
    using OnItemClicked = std::function<void(bool, const std::string& id)>;

    enum class CameraMode : uint8_t {
        Pan,
        Rotate,
        Zoom
    };

    struct CubeEntity {
        glm::vec3 position;
        glm::vec3 size;
        glm::vec3 color;
    };

public:
    GLWidget(QWidget* parent = nullptr);
    ~GLWidget();

    void toggleGrid(bool flag);
    void toggleAxis(bool flag);
    void setCameraMode(CameraMode mode);
    void setItemCallback(OnItemClicked clicked);

    void addCube();

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);

private:
    QOpenGLVertexArrayObject*   m_gridVAO;
    QOpenGLBuffer*              m_gridVBO;
    QOpenGLShaderProgram*       m_gridShader;

    QOpenGLVertexArrayObject*   m_axisVAO;
    QOpenGLBuffer*              m_axisVBO;
    QOpenGLShaderProgram*       m_axisShader;


    int                         m_gridVertCount;
    bool                        m_viewGrid;
    bool                        m_viewAxis;
    Camera*                     m_camera;
    QVector2D                   m_cacheMousePos;
    CameraMode                  m_cameraMode;
    std::vector<CubeEntity>     m_cubeList;
    OnItemClicked               m_onItemClicked;

    /**
     *  Axis coordinates and grid are not part of the 'scene' as they are static,
     *  only created once, does not have a 'scene' functionality and is not portable
     *  to non editor application (such as a game engine). Scene Manager at this point
     *  handles the functioning scene in the 3d world.
     */

    SceneManager                m_sceneManager;

    Renderer                    m_axisRenderer;
    Mesh                        m_axis;
    Renderer                    m_gridRenderer;
    Mesh                        m_grid;

};

#endif // GLWIDGETS_H
