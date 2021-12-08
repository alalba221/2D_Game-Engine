#include "alalbapch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Alalba_6160/core/Systems/PhysicsSys.h"
// #include "Alalba/Core/Log.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
namespace Alalba{
  #define BIND_ENVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

  Application::Application(){
		s_Instance = this;
		
	  m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_ENVENT_FN(Application::OnEvent));
		
		winID = SDL_GetWindowID((SDL_Window*)m_Window->GetNativeWindow());
		
		m_Scene = new Scene();
		m_Scene->Init();

		Renderer::Init(winID, *m_Scene);
		PhysicsSys::Init(*m_Scene);
		
		player1  = new Entity(m_Scene->Reg().create(),m_Scene);
		player1->AddComponent<PlayerComponent>();
		m_Scene->AddEntity(player1);
		player2  = new Entity(m_Scene->Reg().create(),m_Scene);
		m_Scene->AddEntity(player2);
		
	}
  Application::~Application(){
		// SDL_DestroyRenderer(m_Renderer->GetRenderer());
		SDL_DestroyWindow((SDL_Window*)m_Window->GetNativeWindow());
		SDL_Quit();
  }
  void Application::OnEvent(Event& e){

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_ENVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_ENVENT_FN(Application::OnMousePressed));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_ENVENT_FN(Application::OnKeyPressed));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_ENVENT_FN(Application::OnMouseMove));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_ENVENT_FN(Application::OnMouseReleased));
		auto entities = m_Scene->GetEntities();
	
		// for(auto entity: entities)
		// {
		// 	if(entity->GetComponent<TagComponent>().Tag == "Player")
		// 	{
		// 		entity->OnEvent(e);	
		// 	}
		// }

	}
	void Application::OnUpdate(float t){
		
		PhysicsSys::OnUpdate(*m_Scene , t);
		m_Scene->OnUpdate(t);
		
	}
	bool Application::OnKeyPressed(KeyPressedEvent& e)
	{
		if(Input::IsKeyPressed(ALALBA_SPACE)){
			auto view = m_Scene->Reg().view<Rigidbody2DComponent>();		
			// Check if Arrow already exist
			for(auto en:view)
			{
				Entity entity = {en, m_Scene};
				
				if(entity.GetComponent<TagComponent>().Tag == "Player1" || 
					entity.GetComponent<TagComponent>().Tag == "Player2")
				{
					auto& transform = entity.GetComponent<TransformComponent>();
					auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
					glm::mat4 rotator = glm::rotate(glm::mat4(1.0f),transform.shootDir.z, glm::vec3{0,0,1});
					
					glm::vec4 Vector = rotator * glm::vec4{0,-9.8,0,1};
					PhysicsSys::AddImpluse(entity,transform.Translation, glm::vec3{Vector.x,Vector.y,0.0f}* (float)(rb2d.Mass * 1.0));
					if(entity.GetComponent<TagComponent>().Tag == "Player1")
						entity.GetComponent<TagComponent>().Tag = "Puck1";
					else 
						entity.GetComponent<TagComponent>().Tag = "Puck2";
				}

				// delete Arrow
				if(entity.GetComponent<TagComponent>().Tag == "Arrow")
				{
					entity.GetComponent<TagComponent>().Tag = "UnusedArrow";
					entity.RemoveComponent<TransformComponent>();
					entity.RemoveComponent<Rigidbody2DComponent>();
					entity.RemoveComponent<TextureComponent>();
				}

			}
			// switch shooter
			if(player1->HasComponent<PlayerComponent>()){
				player1->RemoveComponent<PlayerComponent>();
				player2->AddComponent<PlayerComponent>();
				
			} else if(player2->HasComponent<PlayerComponent>()){
				player2->RemoveComponent<PlayerComponent>();
				player1->AddComponent<PlayerComponent>();
				
			}
		}	
	}
	bool Application::OnMousePressed(MouseButtonPressedEvent& e)
	{
		
		if(Input::IsMouseButtonPressed(ALALBA_MOUSE_BUTTON_LEFT)){
			std::cout<<e<<std::endl;
			auto view = m_Scene->Reg().view<Rigidbody2DComponent>();
		
			// Check if Player puck already exist
			for(auto en:view)
			{
				Entity entity = {en, m_Scene};
				if(entity.GetComponent<TagComponent>().Tag == "Player1" || entity.GetComponent<TagComponent>().Tag == "Player2")
				{
					return false;
				}
			}
			// For test: place a puck at mouse position
			Entity* puck  = new Entity(m_Scene->Reg().create(),m_Scene);
			
			float x = (float)e.GetX();
			float y = (float)e.GetY();
			puck->AddComponent<TransformComponent>(glm::vec3(x/Meter2Pix, y/Meter2Pix, 0));
			puck->AddComponent<Rigidbody2DComponent>();
			//Check 2 players
			if(player1->HasComponent<PlayerComponent>())
			{
				puck->AddComponent<TextureComponent>(TextureId::AWESOMEFACE);
				m_Scene->AddEntity(puck,"Player1");
				
			}
			else if(player2->HasComponent<PlayerComponent>())
			{
				puck->AddComponent<TextureComponent>(TextureId::AWESOMEFACEINV);
				m_Scene->AddEntity(puck,"Player2");
				
			}
			
			// Don't forgget add it into the physics system
			PhysicsSys::AddEntity(*puck);
		}

		if(Input::IsMouseButtonPressed(ALALBA_MOUSE_BUTTON_RIGHT)){

			auto view = m_Scene->Reg().view<Rigidbody2DComponent>();		
			// Check if Arrow already exist
			for(auto en:view)
			{
				Entity entity = {en, m_Scene};
				if(entity.GetComponent<TagComponent>().Tag == "Arrow")
				{
					return false;
				}
			}			
			//Place an arrow at mouse position
			Entity* arrow  = new Entity(m_Scene->Reg().create(),m_Scene);
			arrow->AddComponent<TextureComponent>(TextureId::ARROW);
			float x = (float)e.GetX();
			float y = (float)e.GetY();
			arrow->AddComponent<TransformComponent>(glm::vec3(x/Meter2Pix, y/Meter2Pix, 0));
			arrow->GetComponent<TransformComponent>().Scale = glm::vec3{2.0f,2.0f,0.0f} ;
			arrow->AddComponent<Rigidbody2DComponent>();
			m_Scene->AddEntity(arrow,"Arrow");
		}
		return false;
	}
	bool Application::OnMouseReleased(MouseButtonReleasedEvent& e)
	{
	}
	bool Application::OnMouseMove(MouseMovedEvent& e)
	{
		if(Input::IsMouseButtonPressed(ALALBA_MOUSE_BUTTON_LEFT))
		{
			
			float X = e.GetX()/Meter2Pix;
			float Y = e.GetY()/Meter2Pix;
			auto view = m_Scene->Reg().view<Rigidbody2DComponent>();
			// Apply Impulse 
			for(auto en:view)
			{
				Entity entity = {en, m_Scene};
				if(entity.GetComponent<TagComponent>().Tag == "Player1" ||
					entity.GetComponent<TagComponent>().Tag == "Player2" ||
					entity.GetComponent<TagComponent>().Tag == "Arrow")
				{
					entity.GetComponent<TransformComponent>().Translation 
								= glm::vec3{X,Y,0};
				}
				
			}
		}
		if(Input::IsMouseButtonPressed(ALALBA_MOUSE_BUTTON_RIGHT))
		{
			
			float X = e.GetX()/Meter2Pix;
			float Y = e.GetY()/Meter2Pix;
			float theta ;
			auto view = m_Scene->Reg().view<Rigidbody2DComponent>();
			for(auto& en:view)
			{
				Entity entity = {en, m_Scene};
				
				if(entity.GetComponent<TagComponent>().Tag == "Arrow")
				{
					auto& transform = entity.GetComponent<TransformComponent>();
					float origX = transform.Translation.x;
					float origY = transform.Translation.y;
					glm::vec3 norm = glm::vec3{0, -1, 0};
					glm::vec3 Vector = glm::vec3{X-origX, Y-origY, 0};
					float cos = glm::dot(Vector,norm)/glm::length(Vector);
					
					transform.Rotation.z = acos(cos);
					if(X<origX)
						transform.Rotation.z = -transform.Rotation.z;
					theta = transform.Rotation.z;
				}
			}

			// assign direction to player
			for(auto& en:view)
			{
				Entity entity = {en, m_Scene};
				
				if(entity.GetComponent<TagComponent>().Tag == "Player1" ||
					entity.GetComponent<TagComponent>().Tag == "Player2")
				{
					auto& transform = entity.GetComponent<TransformComponent>();
					transform.shootDir = glm::vec3{0,0,theta}; 
				}

			}
		}
		return false;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		return false;
	}

  bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;	
		return true;
	}
  void Application::Run(){
	
		// For collision
		// auto view = m_Scene->Reg().view<Rigidbody2DComponent>();
		// for(auto e:view)
		// {
		// 	Entity entity = {e, m_Scene};
		// 	PhysicsSys::AddEntity(entity);
		// }

		while(m_Running){

			for (int K = 0; K < 10; K++)
				this->OnUpdate(0.0005);
			m_Window->OnUpdate();
			Renderer::Submit(*m_Scene);
			Renderer::Render();
		}
  }
}