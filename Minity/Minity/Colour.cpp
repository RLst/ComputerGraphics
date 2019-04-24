#include "Colour.h"

#include "Random.h"

namespace pkr
{
	vec4 Colour::random()
	{
		int rnd = pkr::Random::range(0, 6);
		switch (rnd)
		{
		case 0: return green(); break;
		case 1: return redpure(); break;
		case 2: return yellow(); break;
		case 3: return orange(); break;
		case 4: return dodgerblue(); break;
		case 5: return purple(); break;
		case 6: return fuschia(); break;
		default: return magenta();	//magenta if error
		}
	}

	vec4 Colour::shade(float intensity)
	{
		intensity = glm::clamp(intensity, 0.f, 1.f);
		return vec4(intensity, intensity, intensity, 1);
	}

}