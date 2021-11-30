#include "alalbapch.h"
#include "Scene.h"
// #include "Alalba_6160/core/Systems/PhysicsSys.h"

// #include "Hazel/Renderer/Renderer2D.h"
#include "Base.h"
#include "Vec2.h"
#include "Alalba_6160/core/Entities/Entity.h"
#include "Alalba_6160/core/Entities/Camera.h"
namespace Alalba {

	// static b2BodyType Rigidbody2DTypeToBox2DBody(Rigidbody2DComponent::BodyType bodyType)
	// {
	// 	switch (bodyType)
	// 	{
	// 		case Rigidbody2DComponent::BodyType::Static:		return b2_staticBody;
	// 		case Rigidbody2DComponent::BodyType::Dynamic:   return b2_dynamicBody;
	// 		case Rigidbody2DComponent::BodyType::Kinematic: return b2_kinematicBody;
	// 	}
	// 	return b2_dynamicBody;
	// }

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
		//PhysicsSys::Init(*this);
		// camera
		Camera* camera = new Camera(m_Registry.create(),this);
		
		camera->AddComponent<CameraComponent>(SNES_RESOLUTION_WIDTH / 2,
																		SNES_RESOLUTION_WIDTH / 2,
																		SNES_RESOLUTION_WIDTH,
																		SNES_RESOLUTION_WIDTH);
		AddEntity(camera, "Camera");

		// Player puck
		Entity* player  = new Entity(m_Registry.create(),this);
		player->AddComponent<TextureComponent>(TextureId::MARIO_STAND);
		player->AddComponent<TransformComponent>(glm::vec3(6.3, 10,0));
		player->AddComponent<Rigidbody2DComponent>();
		AddEntity(player,"Player");

		// puck0
		Entity* puck0  = new Entity(m_Registry.create(),this);
		puck0->AddComponent<TextureComponent>(TextureId::MARIO_STAND);
		puck0->AddComponent<TransformComponent>(glm::vec3(8.4,17.7,0));
		puck0->AddComponent<Rigidbody2DComponent>();
		AddEntity(puck0,"Puck");
		// puck1
		Entity* puck1  = new Entity(m_Registry.create(),this);
		puck1->AddComponent<TextureComponent>(TextureId::MARIO_STAND);
		puck1->AddComponent<TransformComponent>(glm::vec3(7,15,0));
		puck1->AddComponent<Rigidbody2DComponent>();
		AddEntity(puck1,"Puck");
		// ground
		Entity* ground  = new Entity(m_Registry.create(),this);
		ground->AddComponent<TextureComponent>(TextureId::BLOCK);
		ground->AddComponent<TransformComponent>(glm::vec3(20,20,0),40,1);
		// ground->AddComponent<Rigidbody2DComponent>();
		// ground->AddComponent<BoxCollider2DComponent>();
		AddEntity(ground,"Ground");

		// ground
		Entity* ground1  = new Entity(m_Registry.create(),this);
		ground1->AddComponent<TextureComponent>(TextureId::BLOCK);
		ground1->AddComponent<TransformComponent>(glm::vec3(1,10,0),1,20);
		// ground1->AddComponent<Rigidbody2DComponent>();
		// ground1->AddComponent<BoxCollider2DComponent>();
		AddEntity(ground1,"Ground");

// /// Physics with Box2D
// 		m_PhysicsWorld = new b2World({ 0.0f, 9.8f });
// 		// puck1
// 		Entity* puck  = new Entity(m_Registry.create(),this);
// 		puck->AddComponent<TextureComponent>(TextureId::MARIO_STAND);
// 		puck->AddComponent<TransformComponent>(glm::vec3(6.5,10,0));
// 		puck->AddComponent<Rigidbody2DComponent>();
// 		puck->AddComponent<BoxCollider2DComponent>();
// 		AddEntity(puck,"Puck");

// 		// puck2
// 		Entity* puck1  = new Entity(m_Registry.create(),this);
// 		puck1->AddComponent<TextureComponent>(TextureId::MARIO_STAND);
// 		puck1->AddComponent<TransformComponent>(glm::vec3(7,15,0));
// 		puck1->AddComponent<Rigidbody2DComponent>();
// 		puck1->AddComponent<BoxCollider2DComponent>();
// 		AddEntity(puck1,"Puck");
// 		// ground
// 		Entity* ground  = new Entity(m_Registry.create(),this);
// 		ground->AddComponent<TextureComponent>(TextureId::BLOCK);
// 		ground->AddComponent<TransformComponent>(glm::vec3(20,20,0),40,1);
// 		ground->AddComponent<Rigidbody2DComponent>();
// 		ground->AddComponent<BoxCollider2DComponent>();
// 		AddEntity(ground,"Ground");

// 		// ground
// 		Entity* ground1  = new Entity(m_Registry.create(),this);
// 		ground1->AddComponent<TextureComponent>(TextureId::BLOCK);
// 		ground1->AddComponent<TransformComponent>(glm::vec3(1,10,0),1,20);
// 		ground1->AddComponent<Rigidbody2DComponent>();
// 		ground1->AddComponent<BoxCollider2DComponent>();
// 		AddEntity(ground1,"Ground");
// 		// test
		
// 		auto view = m_Registry.view<Rigidbody2DComponent>();
		
// 		for(auto e:view)
// 		{
// 			Entity entity = { e, this };
// 			auto& transform = entity.GetComponent<TransformComponent>();
// 			auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
// 			auto& bc2d = entity.GetComponent<BoxCollider2DComponent>();

// 			b2BodyDef bodyDef;
// 			if(entity.GetComponent<TagComponent>().Tag=="Ground")
// 				rb2d.Type = Rigidbody2DComponent::BodyType::Static;
// 			if(entity.GetComponent<TagComponent>().Tag=="Puck")
// 				transform.Rotation.z = 0.7;

// 			bodyDef.type = Rigidbody2DTypeToBox2DBody(rb2d.Type);
// 			bodyDef.position.Set(transform.Translation.x, transform.Translation.y);
// 			bodyDef.angle = transform.Rotation.z;

// 			b2Body* body = m_PhysicsWorld->CreateBody(&bodyDef);
// 			body->SetFixedRotation(rb2d.FixedRotation);
// 			rb2d.RuntimeBody = body;

// 			b2PolygonShape boxShape;
// 			boxShape.SetAsBox(transform.w * 0.5, transform.h * 0.5);


// 			b2CircleShape circle;
// 			//circle.m_p.Set(transform.x, transform.y);
// 			circle.m_radius = 0.5f;

// 			b2FixtureDef fixtureDef;
// 			if(entity.GetComponent<TagComponent>().Tag=="Puck")
// 				fixtureDef.shape = &circle;
// 			else
// 				fixtureDef.shape = &boxShape;
// 			fixtureDef.density = bc2d.Density;
// 			fixtureDef.friction = bc2d.Friction;
// 			fixtureDef.restitution = bc2d.Restitution;
// 			fixtureDef.restitutionThreshold = bc2d.RestitutionThreshold;
// 			body->CreateFixture(&fixtureDef);
// 		}

		
	}
	void Scene::OnUpdate(float t)
	{
		auto entities = this->GetEntities();
	
		for(auto entity: entities)
		{
			entity->OnUpdate(t);	
		}
		//PhysicsSys::OnUpdate(*this);
		
	}

}