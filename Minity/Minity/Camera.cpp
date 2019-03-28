#include "Camera.h"
#include "App.h"

namespace pkr
{
	Camera::Camera(vec3 position) :
		m_position(position)
	{
		//m_worldTransform = glm::translate(m_worldTransform, position);
		updateProjectionView();
	}

	Camera::Camera(vec3 position, vec3 lookAt, float fovAngle, float aspect, float near, float far) :
		m_position(position),
		m_lookAt(lookAt),
		m_fovAngle(fovAngle),
		m_aspect(aspect),
		m_near(near),
		m_far(far)
	{
		//m_worldTransform = glm::translate(m_worldTransform, position);	//Set position
		updateProjectionView();
	}

	Camera::~Camera()
	{
	}

	void Camera::updateProjectionView()
	{
		//TODO redo this method

		//Calculate new view transform; camera may have moved
		setLookAtHARD(getPosition(), m_lookAt, vec3(0, 1, 0));
		m_projectionViewTransform = m_projectionTransform * m_viewTransform;
	}

	void Camera::setProjection(float fovAngDeg, float aspectRatio, float near, float far)
	{
		auto fovRads = glm::pi<float>() * fovAngDeg / 180.f;	//Convert degrees to radians
		m_projectionTransform = glm::perspective(fovRads, aspectRatio, near, far);
	}

	void Camera::setPosition(const vec3 & position)
	{
		//m_worldTransform = glm::translate(m_worldTransform, position);
		m_position = position;
	}

	void Camera::translate(const vec3 & translation)
	{
		m_position += translation;
	}

	void Camera::setLookAt(const vec3 & lookAt)
	{
		m_lookAt = lookAt;
		setLookAtHARD(getPosition(), m_lookAt, vec3(0, 1, 0));
	}
	void Camera::setLookAtHARD(const vec3 & from, const vec3 & to, const vec3 & up)
	{
		m_viewTransform = glm::lookAt(from, to, up);
	}

	//mat4 Camera::getWorldTransform() const
	//{
	//	return m_worldTransform;
	//}

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

	vec3 Camera::getPosition() const
	{
		//return vec3(m_worldTransform[3]);
		return m_position;
	}

}
