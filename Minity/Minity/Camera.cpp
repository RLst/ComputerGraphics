#include "Camera.h"

namespace pkr
{
	Camera::Camera()
	{
	}

	Camera::~Camera()
	{
	}

	void Camera::updateProjectionView()
	{
		m_projectionViewTransform = m_projectionTransform * m_viewTransform;
	}

	void Camera::setProjection(float fovAngDeg, float aspectRatio, float near, float far)
	{
		//auto fovRads = glm::pi<float>() * fovAngDeg / 180.f;
		//m_projectionTransform = glm::perspective(fovRads, aspectRatio, near, far);
		m_projectionTransform = glm::perspective(fovAngDeg, aspectRatio, near, far);
	}

	void Camera::setLookAt(const vec3 & from, const vec3 & to, const vec3 & up)
	{
		m_viewTransform = glm::lookAt(from, to, up);
	}

	void Camera::setPosition(const vec3 & position)
	{
		m_worldTransform = glm::translate(m_worldTransform, position);
	}

	mat4 Camera::getWorldTransform() const
	{
		return m_worldTransform;
	}

	mat4 Camera::getView() const
	{
		return m_viewTransform;
	}

	mat4 Camera::getProjection() const
	{
		return m_projectionTransform;
	}

	mat4 Camera::getProjectionView() const
	{
		return m_projectionViewTransform;
	}

}
