//Tony Le
//21 Mar 2019

#include "FlyCamera.h"
#include "Input.h"
#include "glm/ext.hpp"
#include "Time.h"


FlyCamera::FlyCamera(vec3 position, vec3 lookAt, float speed, float smoothing, float fovAngle, float aspect, float near, float far) :
	Camera(position, lookAt, fovAngle, aspect, near, far),
	m_speed(speed),
	m_smoothing(smoothing)
{
	init();
}

void FlyCamera::init()
{
	//Setup input & callbacks etc
	auto input = pkr::Input::getInstance();

}

void FlyCamera::update()
{
	auto input = pkr::Input::getInstance();		//COUPLING, BAD

	//WASD
	if (input->isKeyDown(pkr::INPUT_KEY_W))
		m_position += m_front * m_speed * (float)pkr::Time::deltaTime();
	if (input->isKeyDown(pkr::INPUT_KEY_S))
		m_position -= m_front * m_speed * (float)pkr::Time::deltaTime();
	if (input->isKeyDown(pkr::INPUT_KEY_A))
		m_position -= glm::normalize(glm::cross(m_front, m_up)) * m_speed * (float)pkr::Time::deltaTime();
	if (input->isKeyDown(pkr::INPUT_KEY_D))
		m_position += glm::normalize(glm::cross(m_front, m_up)) * m_speed * (float)pkr::Time::deltaTime();

	//Mouse look
	int dx, dy;
	input->getMouseDelta(&dx, &dy);
	m_front_desired += vec3(dx, dy, 0);

	//Control camera by mouse and WASD
	m_rotation = glm::slerp(m_rotation, glm::quat(m_front_desired), m_smoothing);
	
	m_viewTransform = glm::lookAt(m_position, m_position + m_front, m_up);
	m_projectionViewTransform = m_projectionTransform * m_viewTransform;
	//updateProjectionView();
}
