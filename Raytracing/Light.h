#pragma once
#include "Engine/vec3d.h"

struct PointLight
{
public:
	Engine::vf3d pos, color;
	float fStrength;

public:
	PointLight()
	{
		fStrength = 0.0f;
	}

	PointLight(const Engine::vf3d &pos, const Engine::vf3d &color, const float &fStrength)
	{
		this->pos       = pos;
		this->color     = color;
		this->fStrength = fStrength;
	}
};
