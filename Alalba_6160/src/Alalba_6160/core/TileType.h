#pragma once

#include "Base.h"
#include "Alalba_6160/Renderer/TextureManager.h"
namespace Alalba{
	enum Properties {
			NONE 				= 0,
			VISIBLE 		= BIT(0),
			SOLID 			= BIT(1),
			MASS 				= BIT(2),
			KINETIC 		= BIT(3),
			BREAKABLE 	= BIT(4),
			QUESTION 		= BIT(5),
			SPAWN 			= BIT(6),
			COIN 				= BIT(7),
			ENEMY 			= BIT(8),
			SPAWN_ONE_UP= BIT(9),
			POLE 				= BIT(10),
			FLAG 				= BIT(11),
	};

	struct TileType {
			TileType() = default;

			TileType(TextureId texture, Properties properties) :
							texture{texture},
							editor_texture{texture},
							properties{properties} {}

			TileType(TextureId texture, Properties properties, TextureId editor_texture) :
							texture{texture},
							editor_texture{editor_texture},
							properties{properties} {}

			TextureId texture = TextureId::EMPTY;
			TextureId editor_texture = texture;
			uint32_t properties = Properties::NONE;
	};

	
}