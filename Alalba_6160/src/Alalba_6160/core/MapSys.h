#pragma once


#include <queue>
#include "Components.h"
#include <fstream>
#include <exception>
#include "Scene.h"
#include "TileType.h"
#include "TileEntity.h"
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
																	Properties::VISIBLE
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
	

    static void Set(int x, int y, TileEntity* value) {
			tiles.at(x + y * mapWidth) = value;
    }

		static TileEntity* Get(int x, int y){
			if (x < 0 || y < 0) return nullptr;
			if (x >= mapWidth || y >= mapHeight) return nullptr;
			return tiles[x + y * mapWidth];
		}
	public:
		// measure unit: tile size
		static int mapWidth;
    static int mapHeight;
		static std::vector<TileEntity*> tiles;
	private:
		static Map map;
		//CameraComponent* camera{};
		static Scene* m_Scene;
		
	};
}