#pragma once
#include "Alalba_6160/core/Scene.h"
#include "Alalba_6160/core/Entities/Entity.h"
#include "Alalba_6160/core/Components.h"

namespace Alalba
{

	class ScoreSys
	{
	public:
		static void Init(Scene& scene);
		static void OnUpdate(Scene& scene);
		static void UpdateScoreTxt(Scene& scene, int score, const std::string& tag);
	};


}