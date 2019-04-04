#pragma once

#include "glm/ext.hpp"

using glm::vec4;

namespace pkr
{
	class Colour : public glm::vec4
	{
	public:
		//static vec4 random();			//Random colour from full palette
		static vec4 random();		//Random colour from nice palette
		static vec4 shade(float intensity);		//input of 0.5f will return vec4(0.5f, 0.5f, 0.5f, 1);

		static vec4 white() { return vec4(1, 1, 1, 1); }
		static vec4 lightgrey() { return vec4(0.75f, 0.75f, 0.75f, 1); }
		static vec4 grey() { return vec4(0.5f, 0.5f, 0.5f, 1); }
		static vec4 darkgrey() { return vec4(0.25f, 0.25f, 0.25f, 1); }
		static vec4 black() { return vec4(0, 0, 0, 1); }

		static vec4 redpure() { return vec4(1, 0, 0, 1); }
		static vec4 greenpure() { return vec4(0, 1, 0, 1); }
		static vec4 bluepure() { return vec4(0, 0, 1, 1); }

		static vec4 cyan() { return vec4(0, 1, 1, 1); }
		static vec4 magenta() { return vec4(1, 0, 1, 1); }
		static vec4 yellow() { return vec4(1, 0.85f, 0, 1); }

		static vec4 orange() { return vec4(1, 0.5f, 0, 1); }
		static vec4 lightorange() { return vec4(1, 0.75f, 0.5f, 1); }
		static vec4 darkorange() { return vec4(0.5f, 0.25f, 0, 1); }

		static vec4 limegreen() { return vec4(102 / 255.f, 1.0f, 102 / 255.f, 1); }
		static vec4 green() { return vec4(51 / 255.f, 204 / 255.f, 51 / 255.f, 1); }
		static vec4 darkgreen() { return vec4(0, 102 / 255.f, 0, 1); }
		static vec4 mint() { return vec4(0, 1, 0.5f, 1); }

		static vec4 blue() { return vec4(0, 153 / 255.f, 1, 1); }
		static vec4 skyblue() { return vec4(102 / 255.f, 204 / 255.f, 1, 1); }
		static vec4 dodgerblue() { return vec4(0, 0.5f, 1, 1); }
		static vec4 darkblue() { return vec4(0, 102 / 255.f, 204 / 255.f, 1); }

		static vec4 indigo() { return vec4(0.25f, 0, 1, 1); }
		static vec4 purple() { return vec4(0.5f, 0, 1, 1); }
		static vec4 fuschia() { return vec4(1, 0, 0.5f, 1); }
	};
}
