#include "Colour.h"

#include "Random.h"

namespace pkr
{
	vec4 Colour::get(eColours colour)
	{
		switch (colour)
		{
		case eWHITE: return vec4(1, 1, 1, 1); break;
		case eRED: return vec4(1, 0, 0, 1); break;
		case eGREEN: return vec4(0.1f, 0.9f, 0, 1); break;
		case eBLUE: return vec4(0, 0, 1, 1); break;
		case eCYAN: return vec4(0, 1, 1, 1); break;
		case eMAGENTA: return vec4(1, 0, 1, 1); break;
		case eYELLOW: return vec4(1, 0.85f, 0, 1); break;
		case eORANGE: return vec4(1, 0.5f, 0, 1); break;
		case eLIMEGREEN: return vec4(0.75f, 1, 0, 1); break;
		case eMINT: return vec4(0, 1, 0.5f, 1); break;
		case eDODGERBLUE: return vec4(0, 0.5f, 1, 1); break;
		case eINDIGO: return vec4(0.25f, 0, 1, 1); break;
		case ePURPLE: return vec4(0.5f, 0, 1, 1); break;
		case eFUSCHIA: return vec4(1, 0, 0.5f, 1); break;
		case eGREY: return vec4(0.5f, 0.5f, 0.5f, 1); break;
		default: return vec4(1, 1, 1, 0.5f); break;
		}
	}

	vec4 Colour::random()
	{
		int rnd = pkr::Random::range(0, eColours::COLOUR_COUNT - 1);
		return get((eColours)rnd);
	}

	vec4 Colour::random_nice()
	{
		int rnd = pkr::Random::range(0, 6);
		switch (rnd)
		{
		case 0: return get(eGREEN); break;
		case 1: return get(eRED); break;
		case 2: return get(eYELLOW); break;
		case 3: return get(eORANGE); break;
		case 4: return get(eDODGERBLUE); break;
		case 5: return get(ePURPLE); break;
		case 6: return get(eFUSCHIA); break;
		default: return get(eWHITE);	//default to white
		}
	}

	vec4 Colour::shade(float intensity)
	{
		intensity = glm::clamp(intensity, 0.f, 1.f);
		return vec4(intensity, intensity, intensity, 1);
	}

}