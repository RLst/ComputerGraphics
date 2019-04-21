#pragma once

#include "glm/ext.hpp"
#include "App.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::quat;

namespace pkr
{
class Camera
{
protected:
	//TODO Implement quaternions later, might make lerping easier
	//vec3			m_position;
	//quat			m_rotation;

	mat4			m_world;
	mat4			m_view;
	mat4			m_projection;
	mat4			m_projectionView;

	vec3 m_lookAt;

	float m_fovAngle = 50.f;
	float m_aspect = 16 / 9.0f;
	float m_near = 0.1f, m_far = 1000;

public:
	Camera();
	Camera(vec3 position);
	Camera(vec3 position, vec3 lookAt, float fovAngle, float aspect, float near, float far);
	~Camera();

	void virtual	update() = 0;

	const mat4		getView() const;
	void			setLookAt(const vec3& lookAt, const vec3& up);

	const mat4		getProjection() const;
	void			setProjection(float fovAngDeg, float aspectRatio, float near, float far);

	const mat4		getWorld() const;

	const mat4		getProjectionView() const;
	void			updateProjectionView();

	const vec3		getPosition() const;
	void			setPosition(const vec3& position);
	void			translate(const vec3& translation);

	const vec3		getRotation() const;

	const vec3		up() const;
	const vec3		right() const;
	const vec3		forward() const;
	const vec3		down() const;
	const vec3		left() const;
	const vec3		backward() const;
};

}
