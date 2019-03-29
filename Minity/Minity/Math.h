#pragma once

namespace pkr
{

	class Math
	{
	public:
		static float RadsToDegs(float rads) { return rads * 57.295754f; }
		static float DegsToRads(float angle) { return angle * 0.0174533f; }


	};

}
