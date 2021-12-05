#include "alalbapch.h"
#include "Scene.h"
// #include "Alalba_6160/core/Systems/PhysicsSys.h"

// #include "Hazel/Renderer/Renderer2D.h"
#include "Base.h"
#include "Vec2.h"
#include "Alalba_6160/core/Entities/Entity.h"
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

		//  puck
		Entity* player  = new Entity(m_Registry.create(),this);
		player->AddComponent<TextureComponent>(TextureId::AWESOMEFACE);
		player->AddComponent<TransformComponent>(glm::vec3(7.1, 12.2 ,0));
		player->AddComponent<Rigidbody2DComponent>();
		AddEntity(player,"Puck");
		// puck0
		Entity* puck0  = new Entity(m_Registry.create(),this);
		puck0->AddComponent<TextureComponent>(TextureId::AWESOMEFACE);
		puck0->AddComponent<TransformComponent>(glm::vec3(6.5, 10, 0));
		puck0->AddComponent<Rigidbody2DComponent>();
		AddEntity(puck0,"Puck");
		// puck1
		Entity* puck1  = new Entity(m_Registry.create(),this);
		puck1->AddComponent<TextureComponent>(TextureId::AWESOMEFACE);
		puck1->AddComponent<TransformComponent>(glm::vec3(7.7, 10, 0));
		puck1->AddComponent<Rigidbody2DComponent>();
		AddEntity(puck1,"Puck");		
	}
	void Scene::OnUpdate(float t)
	{
		auto entities = this->GetEntities();
	
		for(auto entity: entities)
		{
			entity->OnUpdate(t);	
		}
		
	}

}