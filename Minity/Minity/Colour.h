#pragma once

#include "glm/ext.hpp"

using glm::vec4;

namespace pkr
{
	enum eColours
	{
		eWHITE,
		eRED,
		eGREEN,
		eBLUE,
		eCYAN,
		eMAGENTA,
		eYELLOW,
		eORANGE,
		eLIMEGREEN,
		eMINT,
		eDODGERBLUE,
		eINDIGO,
		ePURPLE,
		eFUSCHIA,
		eGREY,
		COLOUR_COUNT
	};

	class Colour
	{
	public:
		static vec4 get(eColours colour);
		static vec4 random();			//Random colour from full palette
		static vec4 random_nice();		//Random colour from nice palette
		static vec4 shade(float intensity);		//input of 0.5f will return vec4(0.5f, 0.5f, 0.5f, 1);

		static vec4 white() { return vec4(1, 1, 1, 1); }
		static vec4 lightgrey() { return vec4(0.75f, 0.75f, 0.75f, 1); }
		static vec4 grey() { return vec4(0.5f, 0.5f, 0.5f, 1); }
		static vec4 darkgrey() { return vec4(0.25f, 0.25f, 0.25f, 1); }
		static vec4 black() { return vec4(0, 0, 0, 1); }

		static vec4 red() { return vec4(1, 0, 0, 1); }
		static vec4 green() { return vec4(0, 1, 0, 1); }
		static vec4 blue() { return vec4(0, 0, 1, 1); }

		static vec4 cyan() { return vec4(0, 1, 1, 1); }
		static vec4 magenta() { return vec4(1, 0, 1, 1); }
		static vec4 yellow() { return vec4(1, 0.85f, 0, 1); }

		static vec4 orange() { return vec4(1, 0.5f, 0, 1); }
		static vec4 limegreen() { return vec4(0.75f, 1, 0, 1); }
		static vec4 mint() { return vec4(0, 1, 0.5f, 1); }
		static vec4 dodgerblue() { return vec4(0, 0.5f, 1, 1); }
		static vec4 indigo() { return vec4(0.25f, 0, 1, 1); }
		static vec4 purple() { return vec4(0.5f, 0, 1, 1); }
		static vec4 fuschia() { return vec4(1, 0, 0.5f, 1); }
	};
}
