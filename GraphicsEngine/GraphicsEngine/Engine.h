#pragma once
#include "App.h"

class Engine : public pkr::App
{
public:
	Engine();
	~Engine();

	bool Awake() override;
	bool Start() override;
	void Update() override;
	void Draw() override;
	bool End() override;
};

