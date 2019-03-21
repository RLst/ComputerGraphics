#pragma once

#include <random>

#include "glm/ext.hpp"

namespace pkr
{
	class Random
	{	//A proper random number generator
	
	//23 Feb 2019 - This is written as a static class. 
	//Maybe make it an instance class too later on
	private:
		static std::random_device	m_rd;
		static std::mt19937			m_engine;		//Non-deterministic
		static std::mt19937			m_det_engine;	//Deterministic 

	public:	//Static class
		Random() {}
		~Random() = default;

		//Range parameters are inclusive
		//Integers
		static int range(const int min, const int max);	
		static int range_det(const int min, const int max);

		//Floats
		static float range(const float min, const float max);
		static float range_det(const float min, const float max);

		//glm::vec2
		static glm::vec2 range_v2(const float min, const float max);
		static glm::vec2 range_v2_det(const float min, const float max);
	};
}