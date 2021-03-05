#pragma once
#include "Engine/vec3d.h"

struct Circle
{
	Engine::vf3d pos, color;
	float fRadius, fReflectiveIndex;

public:
	Circle() noexcept
	{
		fRadius = fReflectiveIndex = 0.0f;
	}

	Circle(const Engine::vf3d &pos, const Engine::vf3d &color, const float &radius, const float &fReflectiveIndex)
	{
		this->pos = pos;
		this->color = color;
		fRadius = radius;
		this->fReflectiveIndex = fReflectiveIndex;
	}
};

struct GameObject
{
public:
	Engine::vf3d pos, size, color;
	float fReflectiveIndex;

public:
	GameObject() noexcept
	{
		fReflectiveIndex = 0.0f;
	}

	GameObject(const Engine::vf3d &pos, const Engine::vf3d &size, const Engine::vf3d &color, const float &reflective) noexcept
	{
		this->pos  = pos;
		this->size = size;
		this->color = color;
		fReflectiveIndex = reflective;
	}

public:
	virtual bool collides(const Engine::vf3d &point)
	{
		return point.x > pos.x && point.x < pos.x + size.x
			&& point.y > pos.y && point.y < pos.y + size.y
			&& point.z > pos.z && point.z < pos.z + size.z;
	}

	virtual bool collides(const GameObject &object)
	{
		return pos.x < object.pos.x + object.size.x && pos.x + size.x > object.pos.x
			&& pos.y < object.pos.y + object.size.y && pos.y + size.y > object.pos.y
			&& pos.z < object.pos.z + object.size.z && pos.z + size.z > object.pos.z;
	}

	virtual bool collides(const Engine::vf3d &ray_origin, const Engine::vf3d &ray_dir, float &dist, Engine::vf3d &ray_hit, Engine::vf3d &contact_normal)
	{
		const Engine::vf3d invDir = ray_dir.inv();
		const Engine::vf3d lb = pos;
		const Engine::vf3d rt = lb + size;

		const float t1 = (lb.x - ray_origin.x) * invDir.x;
		const float t2 = (rt.x - ray_origin.x) * invDir.x;
		const float t3 = (lb.y - ray_origin.y) * invDir.y;
		const float t4 = (rt.y - ray_origin.y) * invDir.y;
		const float t5 = (lb.z - ray_origin.z) * invDir.z;
		const float t6 = (rt.z - ray_origin.z) * invDir.z;

		const float tminx = std::min(t1, t2);
		const float tminy = std::min(t3, t4);
		const float tminz = std::min(t5, t6);

		const float tmaxx = std::max(t1, t2);
		const float tmaxy = std::max(t3, t4);
		const float tmaxz = std::max(t5, t6);

		const float tmin = std::max(std::max(tminx, tminy), tminz);
		const float tmax = std::min(std::min(tmaxx, tmaxy), tmaxz);

		ray_hit = ray_origin + ray_dir * tmin;
		dist = tmin;

		const float fValX = 1.0f - 2.0f * (ray_origin.x < ray_hit.x);
		const float fValY = 1.0f - 2.0f * (ray_origin.y < ray_hit.y);
		const float fValZ = 1.0f - 2.0f * (ray_origin.z < ray_hit.z);
		contact_normal = Engine::vf3d(fValX * (tmin == tminx), fValY * (tmin == tminy), fValZ * (tmin == tminz));

		return !(tmax < 0.0f || tmin > tmax);
	}
};
