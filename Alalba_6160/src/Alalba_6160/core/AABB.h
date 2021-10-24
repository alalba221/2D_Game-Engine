#pragma once

#include "Components.h"
namespace Alalba{
	bool AABBCollision(
			const TransformComponent& a,
			const TransformComponent& b
	);

	bool AABBCollision(
			float x, float y, float w, float h,
			const TransformComponent& b
	);
}