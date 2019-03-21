//#pragma once
//
//#include <glm/ext.hpp>
//
//using glm::vec3;
//using glm::vec4;
//using glm::mat4;
//
//namespace pkr
//{
//	class Camera
//	{
//		friend class Time;
//	private:
//		mat4 m_worldTransform;
//		mat4 m_viewTransform;
//		mat4 m_projectionTransform;
//		mat4 m_projectionViewTransform;
//
//		void			updateProjectionView();
//	public:
//		Camera();
//		~Camera();
//
//		void virtual	update() = 0;
//		void			setPerspective(float fov, float aspectRatio, float near, float far);
//		void			setLookAt(const vec3& from, const vec3& to, const vec4& up);
//		void			setPosition(const vec3& position);
//		mat4			getWorldTransform() const;
//		mat4			getView() const;
//		mat4			getProjection() const;
//		mat4			getProjectionView() const;
//	};
//
//}
