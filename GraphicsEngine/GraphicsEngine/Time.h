#pragma once

namespace pkr
{

class Time
{
	friend class App;
private:
	static double	m_dt;
	static double	m_fdt;

	static void		updateDeltaTime();
	//static void	updateFixedDeltaTime();

public:
	static double	deltaTime();
	static double	fixedDeltaTime();
};

}
