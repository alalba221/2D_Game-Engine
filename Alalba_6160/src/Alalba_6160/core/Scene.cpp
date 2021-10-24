#include "alalbapch.h"
#include "Scene.h"


// #include "Hazel/Renderer/Renderer2D.h"
#include "Base.h"
#include "Vec2.h"
#include "Alalba_6160/core/Entities/Entity.h"
#include "Alalba_6160/core/Entities/Player.h"
#include "Alalba_6160/core/Entities/Camera.h"
namespace Alalba {
	Scene::Scene()
	{
		m_Entities.clear();
	}

	Scene::~Scene()
	{
	}

	void Scene::AddEntity(Entity* entity,const std::string& name)
	{
		this->m_Entities.emplace_front(entity);
		auto& tag = entity->AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
	}
	void Scene::Init()
	{
		
		// camera
		Camera* camera = new Camera(m_Registry.create(),this);
		
		camera->AddComponent<CameraComponent>(SNES_RESOLUTION_WIDTH / 2,
                                    SNES_RESOLUTION_WIDTH / 2,
                                    SNES_RESOLUTION_WIDTH,
                                    SNES_RESOLUTION_WIDTH);
		AddEntity(camera, "Camera");
		// player
		Player* player = new Player(m_Registry.create(),this);
		AddEntity(player,"Player");

		player->AddComponent<TextureComponent>(TextureId::MARIO_STAND);
		
		player->AddComponent<PlayerComponent>();
		player->AddComponent<GravityComponent>();
		player->AddComponent<SolidComponent>();
		player->AddComponent<KineticComponent>();
		player->AddComponent<TransformComponent>(40, 140, 
																						TILE_SIZE-4, 
																						SMALL_MARIO_COLLIDER_HEIGHT);
	
	}
	void Scene::OnUpdate()
	{
		auto entities = this->GetEntities();
	
		for(auto entity: entities)
		{
			entity->OnUpdate();	
		}

	}

}