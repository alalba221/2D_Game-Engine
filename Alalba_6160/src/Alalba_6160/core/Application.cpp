#include "alalbapch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
// #include "Alalba/Core/Log.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "Player.h"
#include "AnimateSys.h"
#include "PhysicsSys.h"
namespace Alalba{
  #define BIND_ENVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

  Application::Application(){
		s_Instance = this;
		
	  m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_ENVENT_FN(Application::OnEvent));
		
		winID = SDL_GetWindowID((SDL_Window*)m_Window->GetNativeWindow());
		Renderer::Init(winID);

		m_Scene = new Scene();
		m_Scene->Init();
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

		auto entities = m_Scene->GetEntities();
	
		for(auto entity: entities)
		{
			if(entity->GetComponent<TagComponent>().Tag == "Player")
			{
				entity->OnEvent(e);	
			}
		}

	}
	void Application::OnUpdate(){
		
		PhysicsSys::OnUpdate(*m_Scene);
		AnimateSys::OnUpdate(*m_Scene);
		// auto entity = m_Scene->GetEntities()[0];

		// auto trans=entity->GetComponent<TransformComponent>();
		// auto kinetic = entity->GetComponent<KineticComponent>();
		// m_Scene->OnUpdate();
		
	}
	bool Application::OnMousePressed(MouseButtonPressedEvent& e)
	{
		// if(Input::IsMouseButtonPressed(ALALBA_MOUSE_BUTTON_LEFT)){
		// 	face->SetPosition(e.GetX()-10,e.GetY()-10);
		// 	face->SetVel({0,0});
		// 	face->SetPos({(e.GetX()-10.0)/m_Window->GetWidth(),(e.GetY()-10.0)/m_Window->GetHeight()});
		// }return false;
	}
	bool Application::OnMouseMove(MouseMovedEvent& e)
	{
		if(Input::IsMouseButtonPressed(ALALBA_MOUSE_BUTTON_LEFT))
		{
			std::cout<<e<<std::endl;
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

    while(m_Running){
			this->OnUpdate();
			m_Window->OnUpdate();
			Renderer::Submit(*m_Scene);
			Renderer::Render();
    }
  }
}