#include "MapSys.h"
#include "TileEntity.h"
namespace Alalba{
	int MapSys::mapWidth=0;
	int MapSys::mapHeight=0;
	std::vector<TileEntity*> MapSys::tiles;
	Map MapSys::map = Map{"../../../asset/map.txt"};
	
	Scene* MapSys::m_Scene = nullptr;
	void MapSys::Init(Scene& scene){
		m_Scene = &scene;
		
		mapWidth = map.mapWidth;
		mapHeight = map.mapHeight;
		tiles.assign(mapWidth*mapHeight,nullptr);
		
		while (!map.tiles.empty()) {
			auto tile = map.tiles.front();
			// if (tile->x > camera->right() + CAMERA_WORLD_OFFSET) break;
			TileEntity* entity = new TileEntity(scene.Reg().create(),&scene);
			scene.AddEntity(entity,"MapTile");
			entity->AddComponent<TransformComponent>(tile->x, tile->y, tile->w, tile->h);
	
			Set((int)(tile->x/TILE_SIZE), (int)(tile->y/TILE_SIZE),entity);
			
			if (tile->hasProperty(Properties::VISIBLE)) {
				entity->AddComponent<TextureComponent>(tile->textureId);
			}
			if (tile->hasProperty(KINETIC)) {
					entity->AddComponent<KineticComponent>();
        } else {
					entity->AddComponent<TileComponent>();
					auto& transform = entity->GetComponent<TransformComponent>();
					// tileMap->set(
					// 				(int) (transform->getCenterX() / TILE_SIZE),
					// 				(int) (transform->getCenterY() / TILE_SIZE),
					// 				entity
					// );
        }
			//
			if(tile->textureId == TextureId::FLOOR)
				tile->properties |= Properties::SOLID;
			//

			if (tile->hasProperty(Properties::SOLID)) entity->AddComponent<SolidComponent>();
			map.tiles.pop();
			delete tile;
    }
	}
	void MapSys::OnUpdate(Scene& scene){}
}