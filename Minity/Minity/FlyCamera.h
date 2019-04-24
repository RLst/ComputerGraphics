#pragma once

#include "Camera.h"
#include "Input.h"
#include "glm/ext.hpp"
#include "glm/gtx/transform.hpp"

class FlyCamera : public pkr::Camera
{
private:
	float		m_speed = 1;

	float		m_slowSpeedFactor = 0.25f;
	float		m_fastSpeedFactor = 2.5f;
	float		m_lookSpeed = 0.000035f;
	
public:
	FlyCamera(vec3 position) : Camera(position) {};
	FlyCamera(vec3 position, vec3 lookAt, float speed, float fovAngle, float aspect, float near, float far);
	virtual ~FlyCamera() {}

	void		update() override;
	void		setSpeed(float speed) { m_speed = speed; }

	void		adjustYaw(float angle);
	void		adjustPitch(float angle);
};

