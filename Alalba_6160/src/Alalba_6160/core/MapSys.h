#pragma once


#include <queue>
#include "Components.h"
#include <fstream>
#include <exception>
#include "Scene.h"
#include "TileType.h"
namespace Alalba{
	struct Tile {
		int x, y, w, h;
		TextureId textureId;
		uint32_t properties;
		bool hasProperty(Properties property) const {
			return properties & property;
		}
	};

	class Map {

	public:
		Map() = delete;

		explicit Map(std::string&& mapPath) {
			std::cout << "Parsing" << std::endl;
			std::fstream infile(mapPath, std::ios_base::in);
			if (!infile) throw std::invalid_argument("Map path not found: " + mapPath);

			TileType texture;
			int texture_id;

			infile>>mapWidth;
			infile>>mapHeight;

			for (int x = 0; x < mapWidth; x++) {
				for (int y = 0; y < mapHeight; y++) {
					infile>>texture_id;
					if (texture_id != 0) {
						auto tile = new Tile{x * TILE_SIZE,
																	y * TILE_SIZE,
																	TILE_SIZE,
																	TILE_SIZE,
																	static_cast<TextureId>(texture_id),
																	static_cast<TextureId>(texture_id)
						};
						tiles.emplace(tile);
					}
				}
			}

			infile.close();
		}

		int mapWidth;
		int mapHeight;
		std::queue<Tile*> tiles;
	};

	class MapSys {
	public:
		static void Init(Scene& scene);

		static void OnUpdate(Scene& scene) ;
	private:
		static Map map;
		//CameraComponent* camera{};
		static Scene* m_Scene;
	};
}