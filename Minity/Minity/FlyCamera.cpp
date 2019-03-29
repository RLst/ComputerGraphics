//Tony Le
//21 Mar 2019

#include "FlyCamera.h"
#include "Input.h"
#include "glm/ext.hpp"
#include "Time.h"




FlyCamera::FlyCamera()
{
}

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
	//auto input = pkr::Input::getInstance();

}

void FlyCamera::update()
{
	auto input = pkr::Input::getInstance();		//COUPLING, Kinda Bad
	vec3 world = vec3(m_world[3].x, m_world[3].y, m_world[3].z);

	//Unity style camera
	if (input->isMouseButtonDown(pkr::INPUT_MOUSE_BUTTON_RIGHT))
	{
		if (input->isKeyDown(pkr::INPUT_KEY_W))
		{
			//setPosition(getPosition() + forward() * m_speed * (float)pkr::Time::deltaTime());
			translate(forward() * m_speed * (float)pkr::Time::deltaTime());
		}
		if (input->isKeyDown(pkr::INPUT_KEY_S))
		{
			//setPosition(getPosition() + forward() * m_speed * (float)pkr::Time::deltaTime());
			translate(backward() * m_speed * (float)pkr::Time::deltaTime());
		}
		if (input->isKeyDown(pkr::INPUT_KEY_A))
		{
			translate(left() * m_speed * (float)pkr::Time::deltaTime());
		}
		if (input->isKeyDown(pkr::INPUT_KEY_D))
		{
			translate(right() * m_speed * (float)pkr::Time::deltaTime());
		}
		adjustYaw(input->getMouseDeltaX() * m_speed * 0.0001f);
		adjustPitch(input->getMouseDeltaY() * m_speed * 0.0001f);
	}
	//if (input->isKeyDown(pkr::INPUT_KEY_1))
	//{
	//	adjustYaw(-0.01f);
	//}	
	//if (input->isKeyDown(pkr::INPUT_KEY_2))
	//{
	//	adjustYaw(0.01f);
	//}

	//Mouse look
	//int dx, dy;
	//input->getMouseDelta(&dx, &dy);
	//m_front_desired += vec3(dx, dy, 0);

	//Control camera by mouse and WASD
	//m_rotation = glm::slerp(m_rotation, glm::quat(m_front_desired), m_smoothing);

	//m_view = glm::lookAt(world , world + forward(), up());
	//m_world = glm::inverse(m_view);
	//m_projectionView = m_projection * m_view;
	updateProjectionView();
}

void FlyCamera::adjustYaw(float angle)
{
	//Calculate relative world up; requires "glm/gtz/transform.hpp"
	glm::vec4 worldUp = glm::inverse(m_world) * glm::vec4(0, 1, 0, 0);

	//Rotate aroound world up
	glm::mat4 yaw(1.0f);
	yaw = glm::rotate(angle, vec3(worldUp.x, worldUp.y, worldUp.z));

	m_view = yaw * m_view;
	m_world = glm::inverse(m_view);
	updateProjectionView();
}

void FlyCamera::adjustPitch(float angle)
{
	//Get the camera's local right axis by getting cross product of world up * local right
	glm::vec4 worldUp = glm::normalize(glm::inverse(m_world) * glm::vec4(0, 1, 0, 0));

	//Get normalized local forward
	glm::vec3 localForward = glm::normalize(forward());

	//Get local right by getting cross product of world up and local foward
	glm::vec3 localRight = glm::cross(vec3(worldUp.x, worldUp.y, worldUp.z), localForward);


	//Rotate camera's right axis
	glm::mat4 pitch(1.0f);
	pitch = glm::rotate(angle, localRight);

	m_view = pitch * m_view;
	m_world = glm::inverse(m_view);
	updateProjectionView();
}
