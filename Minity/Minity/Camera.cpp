#include "Camera.h"
#include "App.h"
#include "Math.h"

namespace pkr
{
	Camera::Camera() :
		m_fovAngle(45.0f),
		m_aspect(16 / 9.f),
		m_near(0.1f),
		m_far(1000)
	{
		m_view = glm::lookAt(vec3(0, 0, 10), vec3(0, 0, 0), vec3(0, 1, 0));
		m_world = glm::inverse(m_view);
		float fov = Math::DegsToRads(m_fovAngle);
		m_projection = glm::perspective(m_fovAngle, m_aspect, m_near, m_far);
		m_projectionView = m_projection * m_view;
	}
	Camera::Camera(vec3 position)
	{
		setPosition(position);
		setLookAt(vec3(0), vec3(0, 1, 0));
		setProjection(m_fovAngle, m_aspect, m_near, m_far);
		updateProjectionView();
	}
	Camera::Camera(vec3 position, vec3 lookAt, float fovAngle, float aspect, float near, float far) :
		m_lookAt(lookAt),
		m_fovAngle(fovAngle),
		m_aspect(aspect),
		m_near(near),
		m_far(far)
	{
		setPosition(position);
		setLookAt(m_lookAt, vec3(0, 1, 0));
		setProjection(fovAngle, aspect, near, far);
		updateProjectionView();
	}
	Camera::~Camera()
	{
	}

	const mat4 Camera::getView() const
	{
		return m_view;
	}
	void Camera::setLookAt(const vec3 & lookAt, const vec3& up)
	{
		m_lookAt = lookAt;
		m_view = glm::lookAt(getPosition(), m_lookAt, up);
		m_world = glm::inverse(m_view);
	}	

	const mat4 Camera::getProjection() const
	{
		return mat4();
	}
	void Camera::setProjection(float fovAngDeg, float aspectRatio, float near, float far)
	{
		auto fovRads = glm::pi<float>() * fovAngDeg / 180.f;	//Convert degrees to radians
		m_projection = glm::perspective(fovRads, aspectRatio, near, far);
	}

	const mat4 Camera::getWorld() const
	{
		return m_world;
	}

	const mat4 Camera::getProjectionView() const
	{
		return m_projectionView;
	}
	void Camera::updateProjectionView()
	{
		//Calculate new view transform; camera may have moved
		//m_view = glm::lookAt(getPosition(), m_lookAt, up());
		m_world = glm::inverse(m_view);
		m_projectionView = m_projection * m_view;
	}

	void Camera::setPosition(const vec3 & position)
	{
		m_world[3] = vec4(vec3(position), 1);
		m_view = glm::inverse(m_world);
	}
	const vec3 Camera::getPosition() const
	{
		return m_world[3];
	}
	void Camera::translate(const vec3 & translation)
	{
		setPosition(getPosition() + translation);
	}

	const vec3 Camera::up() const
	{
		return m_world[1];
	}
	const vec3 Camera::right() const
	{
		return m_world[0];
	}
	const vec3 Camera::forward() const
	{
		return -m_world[2];
	}
	const vec3 Camera::down() const
	{
		return -up();
	}
	const vec3 Camera::left() const
	{
		return -right();
	}
	const vec3 Camera::backward() const
	{
		return -forward();
	}
}
