#pragma once

#include "Camera.h"
#include "Input.h"
#include "glm/ext.hpp"

class FlyCamera : public pkr::Camera
{
private:
	float		m_speed = 0;
	float		m_smoothing = 0.5f;

	glm::vec3	m_up = vec3(0, 1, 0);
	glm::vec3	m_front = vec3(0, 0, -1);
	glm::ivec3	m_front_desired = m_front;

	
	FlyCamera() = default;

	pkr::Input::MouseMoveCallback lookCB();


	void		init();
	
public:
	FlyCamera(vec3 position) : Camera(position) {};
	FlyCamera(vec3 position, vec3 lookAt, float speed, float smoothing, float fovAngle, float aspect, float near, float far);
	virtual ~FlyCamera() {}

	void		update() override;
	void		setSpeed(float speed) { m_speed = speed; }
};

