#include "MapSys.h"
#include "TileEntity.h"
namespace Alalba{
	Map MapSys::map = Map{"../../../asset/map.txt"};
	Scene* MapSys::m_Scene = nullptr;
	void MapSys::Init(Scene& scene){
		m_Scene = &scene;
		
		while (!map.tiles.empty()) {
			auto tile = map.tiles.front();
			// if (tile->x > camera->right() + CAMERA_WORLD_OFFSET) break;
			TileEntity* entity = new TileEntity(scene.Reg().create(),&scene);
			scene.AddEntity(entity);
			entity->AddComponent<TransformComponent>(tile->x, tile->y, tile->w, tile->h);
			
			if (tile->hasProperty(VISIBLE)) {
					entity->AddComponent<TextureComponent>(tile->textureId);
			}
		
			if (tile->hasProperty(SOLID)) entity->AddComponent<SolidComponent>();
			map.tiles.pop();
			delete tile;
    }
	}
	void MapSys::OnUpdate(Scene& scene){}
}