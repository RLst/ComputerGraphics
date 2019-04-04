#pragma once
#include <glm/ext.hpp>
#include "Texture.h"

namespace pkr
{
	class Mesh
	{
	protected:
		unsigned int triCount;
		unsigned int vao;	//Vertex Array Object
		unsigned int vbo;	//Vertex Buffer Object
		unsigned int ibo;	//Index Buffer Object

	public:
		Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}
		virtual ~Mesh();	

		glm::mat4	transform;
		aie::Texture texture;

		struct Vertex
		{
			glm::vec4 position;
			glm::vec4 normal;
			glm::vec2 texCoord;
		};

		void initialise(unsigned int vertexCount, const Vertex* vertices, unsigned int indexCount = 0, unsigned int* indices = nullptr);
		void initialiseQuad();
		
		virtual void draw();
	};
}
