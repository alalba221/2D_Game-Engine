#pragma once

#include "Components.h"
namespace Alalba{
	bool AABBCollision(
			TransformComponent* a,
			TransformComponent* b
	);

	bool AABBCollision(
			float x, float y, float w, float h,
			TransformComponent* b
	);
}