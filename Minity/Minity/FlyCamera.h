#pragma once

#include "Camera.h"

class FlyCamera : public pkr::Camera
{
private:
	float		m_speed = 0;
	vec3		m_up;

public:
	FlyCamera() = default;
	FlyCamera(vec3 position) : Camera(position) {};
	virtual ~FlyCamera() {}

	void		update() override;
	void		setSpeed(float speed) { m_speed = speed; }
};

