#pragma once
#include <glm/ext.hpp>

namespace tut
{
	class Mesh
	{
	protected:
		unsigned int triCount;
		unsigned int vao, vbo, ibo;

	public:
		Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}
		virtual ~Mesh();	

		struct Vertex
		{
			glm::vec4 position;
			glm::vec4 normal;
			glm::vec2 texCoord;
		};

		void initialiseQuad();
		
		virtual void draw();
	};
}
