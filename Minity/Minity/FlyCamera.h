#pragma once

#include "Camera.h"

class FlyCamera : public pkr::Camera
{
private:
	float		m_speed;
	vec3		m_up;

public:
	FlyCamera();
	~FlyCamera();

	void		update() override;
	void		setSpeed(float speed) { m_speed = speed; }
};

