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
	};
}
