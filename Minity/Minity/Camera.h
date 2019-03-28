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
		vec3 m_position;
		vec3 m_lookAt;

		quat m_rotation;
		vec3 m_direction;

		float m_fovAngle, m_aspect, m_near, m_far;

		//mat4			m_worldTransform;
		mat4			m_viewTransform;
		mat4			m_projectionTransform;
		mat4			m_projectionViewTransform;

		void			updateProjectionView();
	public:
		Camera(vec3 position);
		Camera(vec3 position, vec3 lookAt, float fovAngle, float aspect, float near, float far);
		~Camera();

		void virtual	update() = 0;
		void			setProjection(float fovAngDeg, float aspectRatio, float near, float far);

		void			setPosition(const vec3& position);
		void			translate(const vec3& translation);

		void			setLookAt(const vec3& lookAt);
		void			setLookAtHARD(const vec3& from, const vec3& to, const vec3& up);	//Hard set look at (probably avoid)

		//mat4			getWorldTransform() const;	//TODO is this neccessary?
		mat4			getView() const;
		mat4			getProjection() const;
		mat4			getProjectionView() const;

		vec3			getPosition() const;
	};

}
