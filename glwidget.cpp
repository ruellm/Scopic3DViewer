#include <atomic>
#include "glwidget.h"
#include "common.h"
#include "intersect.h"
#include "meshbuilder.h"

static std::atomic<bool>  f_mousePressed = {false};

static float f_distance = 0;
static int f_shapesId = 0;


GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , m_gridVAO(nullptr)
    , m_gridVBO(nullptr)
    , m_gridShader(nullptr)
    , m_axisVAO(nullptr)
    , m_axisVBO(nullptr)
    , m_axisShader(nullptr)
    , m_gridVertCount(0)
    , m_viewGrid (true)
    , m_viewAxis(true)
    , m_cameraMode(CameraMode::Pan)
{}

GLWidget::~GLWidget()
{
    SAFE_DELETE(m_gridVAO);
    SAFE_DELETE(m_gridVBO);
    SAFE_DELETE(m_gridShader);
    SAFE_DELETE(m_axisVAO);
    SAFE_DELETE(m_axisVBO);
    SAFE_DELETE(m_axisShader);

    m_axis.cleanUp();
    m_grid.cleanUp();

    builder::Cleanup();
}

void GLWidget::initializeGL()
{
    f_mousePressed = false;

    /** Load OpenGL function table */
    initializeOpenGLFunctions();

    /** initialize rng*/
    srand (time(NULL));

    /** initialize scene manager*/
    m_sceneManager.load();

    /** Cache the distance to target location to maintain distance */
    auto cameraPosition = glm::vec3(0,5,5);
    auto cameraTarget = glm::vec3(0, 0, 0);
    f_distance = glm::length(cameraTarget - cameraPosition);

    m_camera = m_sceneManager.initCamera(cameraPosition, cameraTarget, glm::vec3(0,1,0));

    m_gridRenderer.load("shaders/grid_vshader", "shaders/grid_fshader");
    m_grid = builder::CreateGrid(50, 50);

    m_axisRenderer.load("shaders/axis_vshader", "shaders/axis_fshader");
    m_axis = builder::CreteAxis(50);
}

void GLWidget::paintGL()
{
    m_camera->update();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    /** Dra Grid */
    if(m_viewGrid) {
        m_gridRenderer.bind(m_camera->getViewMatrix(), m_sceneManager.projectionMatrix());
        m_gridRenderer.draw(m_grid, GL_LINES);
    }

    /** Draw coordinate Axis */
    if(m_viewAxis) {
        m_axisRenderer.bind(m_camera->getViewMatrix(), m_sceneManager.projectionMatrix());
        m_axisRenderer.draw(m_axis, GL_LINES);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    m_sceneManager.renderAll();
    glDisable(GL_DEPTH_TEST);

}

void GLWidget::resizeGL(int w, int h)
{
    m_sceneManager.resizeViewPort(w, h);
}

void GLWidget::setItemCallback(OnItemClicked clicked)
{
    m_onItemClicked = clicked;
}

void GLWidget::mousePressEvent(QMouseEvent * event)
{
    float x = event->x();
    float y = event->y();

    auto shape =  m_sceneManager.pickShape(x, y);
    if(shape) {
        m_onItemClicked(true, shape->id());
        return;
    }

    f_mousePressed = true;
    m_cacheMousePos.setX(x);
    m_cacheMousePos.setY(y);

    m_onItemClicked(false, "");
}

void GLWidget::mouseReleaseEvent(QMouseEvent * event)
{
    f_mousePressed = false;
}

void GLWidget::mouseMoveEvent(QMouseEvent * event)
{
    if(f_mousePressed) {
        QVector2D current =  QVector2D(event->x(), event->y());

        if(m_cameraMode == CameraMode::Pan) {
            float PAN_MOVE = 0.10f;
            auto diffX = (current.x() - m_cacheMousePos.x());
            auto diffY = (current.y() - m_cacheMousePos.y());

            float stepX = diffX < 0 ? PAN_MOVE : -PAN_MOVE;
            float stepY = diffY < 0 ? -PAN_MOVE : PAN_MOVE;

            if(glm::abs<int>(diffX) > glm::abs<int>(diffY))
                m_camera->strafe(stepX);
            else
                m_camera->fly(stepY);

        } else if(m_cameraMode == CameraMode::Zoom) {
            float ZOOM_SENSITIVITY = 0.30f;
            auto diffY = (current.y() - m_cacheMousePos.y())< 0 ? ZOOM_SENSITIVITY: -ZOOM_SENSITIVITY;
            m_camera->walk(diffY);

        } else if (m_cameraMode == CameraMode::Rotate) {
            auto diffX = (current.x() - m_cacheMousePos.x());
            glm::vec3 pivot = m_camera->getPosition() + (m_camera->getLook() * f_distance);
            m_camera->rotatePosition(pivot, diffX);

        }

        m_cacheMousePos.setX(event->x());
        m_cacheMousePos.setY(event->y());

        repaint();
    }
}

void GLWidget::toggleGrid(bool flag)
{
    if(m_viewGrid == flag)
        return;

    m_viewGrid = flag;
    repaint();
}

void GLWidget::toggleAxis(bool flag)
{
    if(m_viewAxis == flag)
        return;

    m_viewAxis = flag;
    repaint();
}

void GLWidget::setCameraMode(CameraMode mode)
{
    m_cameraMode = mode;
}

void GLWidget::addCube()
{
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    std::string id("Cube#" + std::to_string(f_shapesId++));

    auto shape = m_sceneManager.createShape(Shape::Type::Cube, id);
    shape->material().diffuse = glm::vec3(r, g, b);
    shape->material().ambient = glm::vec3(r, g, b);     // not use in shader

    shape->position() = m_camera->getPosition() + (m_camera->getLook() * f_distance);;

    repaint();
}
