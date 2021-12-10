#include "alalbapch.h"
#include "Scene.h"
// #include "Alalba_6160/core/Systems/PhysicsSys.h"

// #include "Hazel/Renderer/Renderer2D.h"
#include "Base.h"
#include "Vec2.h"
#include "Alalba_6160/core/Entities/Entity.h"
#include "Alalba_6160/core/Entities/Camera.h"
#include "Alalba_6160/core/Systems/ScoreSys.h"
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
		this->m_Entities.emplace_back(entity);
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
		if(screenNum == 1 || screenNum == 2)
		{
			//  table
			Entity* table  = new Entity(m_Registry.create(),this);
			table->AddComponent<TextureComponent>(TextureId::TABLE);
			table->AddComponent<TransformComponent>(glm::vec3(15, 12 ,0),0.5,0.5);
			table->GetComponent<TransformComponent>().Scale = glm::vec3(tablewidth, tablelength ,0);
			//table->AddComponent<Rigidbody2DComponent>();
			AddEntity(table,"Table");


			//  Red score table
			Entity* Red  = new Entity(m_Registry.create(),this);
			//table->AddComponent<TextureComponent>(TextureId::TABLE);
			Red->AddComponent<TransformComponent>(glm::vec3(3, 4 ,0),0.5,0.5);
			Red->GetComponent<TransformComponent>().Scale = glm::vec3(2, 2 ,0);
			Red->AddComponent<TextComponent>("Red");
			Red->GetComponent<TextComponent>().color = {255,0,0};
			AddEntity(Red,"Red");

			Entity* RedScore  = new Entity(m_Registry.create(),this);
			//table->AddComponent<TextureComponent>(TextureId::TABLE);
			RedScore->AddComponent<TransformComponent>(glm::vec3(6, 4 ,0),0.5,0.5);
			RedScore->GetComponent<TransformComponent>().Scale = glm::vec3(2, 2 ,0);
			RedScore->AddComponent<TextComponent>("0");
			RedScore->GetComponent<TextComponent>().color = {255,0,0};
			AddEntity(RedScore,"RedScore");



			//  blue score table
			Entity* Blue  = new Entity(m_Registry.create(),this);
			//table->AddComponent<TextureComponent>(TextureId::TABLE);
			Blue->AddComponent<TransformComponent>(glm::vec3(24, 4 ,0),0.5,0.5);
			Blue->GetComponent<TransformComponent>().Scale = glm::vec3(2, 2 ,0);
			Blue->AddComponent<TextComponent>("Blue");
			Blue->GetComponent<TextComponent>().color = {0,255,0};
			AddEntity(Blue,"Blue");
			Entity* BlueScore  = new Entity(m_Registry.create(),this);
			//table->AddComponent<TextureComponent>(TextureId::TABLE);
			BlueScore->AddComponent<TransformComponent>(glm::vec3(27, 4 ,0),0.5,0.5);
			BlueScore->GetComponent<TransformComponent>().Scale = glm::vec3(2, 2 ,0);
			BlueScore->AddComponent<TextComponent>("0");
			BlueScore->GetComponent<TextComponent>().color = {0,255,0};
			AddEntity(BlueScore,"BlueScore");

			//  Strength info
			Entity* info  = new Entity(m_Registry.create(),this);
			//table->AddComponent<TextureComponent>(TextureId::TABLE);
			info->AddComponent<TransformComponent>(glm::vec3(3, 15 ,0),0.5,0.5);
			info->GetComponent<TransformComponent>().Scale = glm::vec3(4, 2 ,0);
			info->AddComponent<TextComponent>();
			info->GetComponent<TextComponent>().text = "Strength";
			info->GetComponent<TextComponent>().color = {0,255,0};
			AddEntity(info,"Info");
			Entity* strength  = new Entity(m_Registry.create(),this);
			strength->AddComponent<TransformComponent>(glm::vec3(6, 15 ,0),0.5,0.5);
			strength->GetComponent<TransformComponent>().Scale = glm::vec3(4, 2 ,0);
			strength->AddComponent<TextComponent>("0.000000");
			AddEntity(strength,"Strength");
			if(screenNum == 2)
			{
				//printf("%d\n", stoi(BlueScore->GetComponent<TextComponent>().text));
				if(ScoreSys::redscore < ScoreSys::bluescore)
				{
					Entity* winner  = new Entity(m_Registry.create(),this);
					winner->AddComponent<TransformComponent>(glm::vec3(23, 10 ,0),0.5,0.5);
					winner->GetComponent<TransformComponent>().Scale = glm::vec3(10, 6 ,0);
					winner->AddComponent<TextComponent>();
					winner->GetComponent<TextComponent>().text = "Blue Wins!";
					winner->GetComponent<TextComponent>().color = {0,0,0};
					AddEntity(winner,"winner");
				}
				else if(ScoreSys::redscore > ScoreSys::bluescore)
				{
					Entity* winner  = new Entity(m_Registry.create(),this);
					winner->AddComponent<TransformComponent>(glm::vec3(23, 10 ,0),0.5,0.5);
					winner->GetComponent<TransformComponent>().Scale = glm::vec3(10, 6 ,0);
					winner->AddComponent<TextComponent>();
					winner->GetComponent<TextComponent>().text = "Red Wins!";
					winner->GetComponent<TextComponent>().color = {0,0,0};
					AddEntity(winner,"winner");
				}
				else
				{
					Entity* winner  = new Entity(m_Registry.create(),this);
					winner->AddComponent<TransformComponent>(glm::vec3(23, 10 ,0),0.5,0.5);
					winner->GetComponent<TransformComponent>().Scale = glm::vec3(10, 6 ,0);
					winner->AddComponent<TextComponent>();
					winner->GetComponent<TextComponent>().text = "It's a Tie!";
					winner->GetComponent<TextComponent>().color = {0,0,0};
					AddEntity(winner,"winner");
				}
			}
		}
		else if(screenNum == 0)
		{
			Entity* sScreen  = new Entity(m_Registry.create(),this);
			sScreen->AddComponent<TextureComponent>(TextureId::START);
														//position of center of image
			sScreen->AddComponent<TransformComponent>(glm::vec3(15, 12 ,0),0.5,0.5);
			sScreen->GetComponent<TransformComponent>().Scale = glm::vec3(60, 50 ,0);
			AddEntity(sScreen,"sScreen");
		}
		

		if(screenNum == 1)
		{
		// init dictator
		for(int i=0;i<4;i++)
		{
			redDictator[i]  = new Entity(m_Registry.create(),this);
			redDictator[i]->AddComponent<TransformComponent>(glm::vec3(3+i, 20 ,0));
			redDictator[i]->AddComponent<TextureComponent>(TextureId::RED);
			this->AddEntity(redDictator[i]);

			blueDictator[i]  = new Entity(m_Registry.create(),this);
			blueDictator[i]->AddComponent<TransformComponent>(glm::vec3(24+i, 20 ,0));
			blueDictator[i]->AddComponent<TextureComponent>(TextureId::BLUE);
			this->AddEntity(blueDictator[i]);
		}
		}

	}

	void Scene::Init_Start()
	{
		Camera* camera = new Camera(m_Registry.create(),this);
		
		camera->AddComponent<CameraComponent>(SNES_RESOLUTION_WIDTH / 2,
																		SNES_RESOLUTION_WIDTH / 2,
																		SNES_RESOLUTION_WIDTH,
																		SNES_RESOLUTION_WIDTH);
		AddEntity(camera, "Camera");

		Entity* sScreen  = new Entity(m_Registry.create(),this);
		sScreen->AddComponent<TextureComponent>(TextureId::START);
													//position of center of image
		sScreen->AddComponent<TransformComponent>(glm::vec3(15, 12 ,0),0.5,0.5);
		sScreen->GetComponent<TransformComponent>().Scale = glm::vec3(60, 50 ,0);
		AddEntity(sScreen,"sScreen");
	}

	void Scene::dictateScreen(int s)
	{
		screenNum = s;
	}

	int Scene::getScreen()
	{
		return screenNum;
	}

	void Scene::clearEntities()
	{
		m_Entities.clear();
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