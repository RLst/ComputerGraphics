//Tony Le
//21 Mar 2019

#include "FlyCamera.h"
#include "Input.h"
#include "glm/ext.hpp"
#include "Time.h"	//Coupled to Time system
#include "Texture.h"

using namespace pkr;

FlyCamera::FlyCamera(vec3 position, vec3 lookAt, float speed, float fovAngle, float aspect, float near, float far) :
	Camera(position, lookAt, fovAngle, aspect, near, far),
	m_speed(speed)
{
}

void FlyCamera::update()
{
	auto input = pkr::Input::getInstance();		//COUPLING, Kinda Bad

	float workingSpeed = m_speed;
	vec3 world = vec3(m_world[3].x, m_world[3].y, m_world[3].z);

	//Unity style camera
	if (input->isMouseButtonDown(KeyCode::Mouse1) ||
		input->isKeyDown(KeyCode::Space))
	{
		//Move faster if holding shift
		if (input->isKeyDown(KeyCode::LeftShift))
			workingSpeed = m_speed * m_fastSpeedFactor;
		else if (input->isKeyDown(KeyCode::LeftControl))
			workingSpeed = m_speed * m_slowSpeedFactor;

		//Normal WASD
		if (input->isKeyDown(KeyCode::W))
			translate(forward() * workingSpeed * (float)Time::deltaTime());
		if (input->isKeyDown(KeyCode::S))
			translate(backward() * workingSpeed * (float)Time::deltaTime());
		if (input->isKeyDown(KeyCode::A))
			translate(left() * workingSpeed * (float)Time::deltaTime());
		if (input->isKeyDown(KeyCode::D))
			translate(right() * workingSpeed * (float)Time::deltaTime());

		//Up and down
		if (input->isKeyDown(KeyCode::E))
			translate(up() * workingSpeed * (float)Time::deltaTime());		
		if (input->isKeyDown(KeyCode::Q))
			translate(down() * workingSpeed * (float)Time::deltaTime());

		//Look around
		adjustYaw(-input->getMouseDeltaX() * m_fovAngle * m_lookSpeed);
		adjustPitch(input->getMouseDeltaY() * m_fovAngle * m_lookSpeed);
	}
	updateProjectionView();
}

void FlyCamera::adjustYaw(float angle)
{
	//Calculate relative world up; requires "glm/gtz/transform.hpp"
	glm::vec4 worldUp = glm::inverse(m_world) * glm::vec4(0, 1, 0, 0);

	//Rotate aroound world up
	auto yaw = glm::rotate(angle, vec3(worldUp.x, worldUp.y, worldUp.z));

	m_world = m_world * yaw;
	m_view = glm::inverse(m_world);
	updateProjectionView();
}

void FlyCamera::adjustPitch(float angle)
{
	//This works for some reason
	vec3 right(1, 0, 0);
	auto pitch = glm::rotate(angle, right);

	m_world = m_world * pitch;
	m_view = glm::inverse(m_world);	
	//m_view = m_view * pitch;
	//m_world = glm::inverse(m_view);
	updateProjectionView();
}
