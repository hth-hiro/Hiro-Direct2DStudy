#pragma once
#include "pch.h"

enum Direction
{
	None = -1,
	Top,
	Left,
	Right,
	Bottom
};

struct AABB
{
	float centerX, centerY;		// centerPos
	float halfW, halfH;			// halfPos
					
	float minX, maxX;
	float minY, maxY;

	std::string name;

	AABB(float _centerX, float _centerY, float _halfW, float _halfH,
		const std::string& _name = "")
		: centerX(_centerX), centerY(_centerY), halfW(_halfW), halfH(_halfH), name(_name)
	{
		UpdateBounds();
	}

	void UpdateBounds()
	{
		minX = centerX - halfW;
		maxX = centerX + halfW;
		minY = centerY - halfH;
		maxY = centerY + halfH;
	}

	Direction GetCollisionDirection(const AABB& other)
	{
		if (!Overlaps(other))
			return Direction::None;

		float dx = other.centerX - centerX;
		float dy = other.centerY - centerY;

		float px = (halfW + other.halfW) - std::abs(dx);
		float py = (halfH + other.halfH) - std::abs(dy);

		if (px < py)
		{
			return (dx > 0) ? Direction::Right : Direction::Left;
		}
		else
		{
			return(dy > 0) ? Direction::Top : Direction::Bottom;
		}
	}

	bool Overlaps(const AABB& other) const
	{
		return !(maxX < other.minX || minX > other.maxX ||
			maxY < other.minY || minY > other.maxY);
	}

	bool Blocks(const AABB& other) const
	{
		return Overlaps(other);
	}
};