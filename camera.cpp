#include "camera.h"


Camera::Camera(void)
{
    m_position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_look = glm::vec3(0.0f, 0.0f, 1.0f);
    m_right = glm::vec3(1.0f, 0.0f, 0.0f);

    m_viewmat = glm::mat4(1.0f);
}

Camera::~Camera(void)
{
}

void Camera::updateViewMtx()
{
    // align axises
    m_look = glm::normalize(m_look);
    m_up = glm::vec3(0,1,0);
    m_right = glm::normalize(glm::cross(m_look, m_up));
    m_up = glm::cross(m_right, m_look);

    m_viewmat[0][0] = m_right.x;
    m_viewmat[1][0] = m_right.y;
    m_viewmat[2][0] = m_right.z;
    m_viewmat[0][1] = m_up.x;
    m_viewmat[1][1] = m_up.y;
    m_viewmat[2][1] = m_up.z;
    m_viewmat[0][2] =-m_look.x;
    m_viewmat[1][2] =-m_look.y;
    m_viewmat[2][2] =-m_look.z;
    m_viewmat[3][0] =-glm::dot(m_right, m_position);
    m_viewmat[3][1] =-glm::dot(m_up, m_position);
    m_viewmat[3][2] = glm::dot(m_look, m_position);
}

void Camera::update()
{
    updateViewMtx();
}

void Camera::lookAt(const glm::vec3& pos,
                    const glm::vec3& up, const glm::vec3& look)
{
    m_look = glm::normalize(look - pos);
    m_up = glm::normalize(up);
    m_position = pos;

    update();
}

void Camera::walk( float amount )
{
    m_position += (m_look * amount);
}

void Camera::strafe (float amount)
{
    m_position += (m_right * amount);
}

void Camera::fly (float amount)
{
    m_position += (m_up * amount);
}

void Camera::rotatePosition(const glm::vec3& axis, float amount)
{
    // prepare matrices for translation to axis origin
    glm::mat4 translate(1.0f);
    translate = glm::translate(translate, -axis);

    glm::mat4 rotmatx = glm::mat4(1.0f);
    amount = glm::radians(amount);
    rotmatx = glm::rotate(rotmatx, amount, glm::vec3(0, 1, 0));

    // translate the current position to origin space
    glm::vec4 newpos = translate * glm::vec4(m_position,1.0f);
    newpos = rotmatx * newpos;

    // translate back
    glm::mat4 translateBack(1.0f);
    translateBack = glm::translate(translateBack, axis);
    newpos = translateBack * newpos;

    m_position = glm::vec3(newpos);
    m_look = glm::normalize(axis - m_position);
}

