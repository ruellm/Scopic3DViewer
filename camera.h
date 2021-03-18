
#pragma once

#include "common.h"

class Camera
{
public:
	Camera(void);
	~Camera(void);

    virtual void update();

    void lookAt(const glm::vec3& pos,
		const glm::vec3& up, 
		const glm::vec3& look);		//NOTE: The lookup in camera is NOT normalize vector

    void walk( float amount);
    void strafe (float amount);
    void pitch(float amount);
    void yaw(float amount);
    void fly (float amount);

    void rotatePosition(const glm::vec3& axis, float amount);

    inline glm::mat4 getViewMatrix() const {
		return m_viewmat;
	}

    inline virtual glm::vec3& getPosition() {
        return m_position;
    }

    inline glm::vec3 getLook() const {
        return  m_look;
    }

    inline glm::vec3 getRight() const {
        return m_right;
    }

    inline glm::vec3 getUp() const {
        return m_up;
    }

    inline void setPosition(glm::vec3 position) {
        m_position = position;
    }

private:

    glm::vec3 m_position;
    glm::vec3 m_up;
    glm::vec3 m_look;
    glm::vec3 m_right;
    glm::mat4 m_viewmat;

    void updateViewMtx();

};

