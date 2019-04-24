#pragma once

namespace pkr
{
	//Common maths functions
	class Math
	{
	public:
		//Radians to Degrees
		template<typename T>
		static T RadsToDegs(T rads) 
			{ return rads * 57.295754; }
		
		//Degrees to Radians
		template<typename T>
		static T DegsToRads(T angle) 
			{ return angle * 0.0174533; }

		//Re-maps a number from one range to another
		//https://p5js.org/reference/#/p5/map
		template<typename T>
		static T Map(T value, T start1, T stop1, T start2, T stop2) 
			{ return ((value - start1) / (stop1 - start1))*(stop2 - start2) + start2; }
	};
}
