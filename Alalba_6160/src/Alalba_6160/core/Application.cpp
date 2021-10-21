#include "alalbapch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
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
		Renderer::Init(winID);

		m_Scene = new Scene();
		m_Scene->Init();
		// std::string prefix = "../../../asset/"	;
		// background = new Object(winID, prefix+"sky.png");
		// background->SetScale(0,0,m_Window->GetWidth(),m_Window->GetHeight());

		// face = new Object(winID, prefix+"awesomeface.png");
		// face->SetScale(100,100,20,20);
	}
  Application::~Application(){
		// SDL_DestroyRenderer(m_Renderer->GetRenderer());
    SDL_DestroyWindow((SDL_Window*)m_Window->GetNativeWindow());
    SDL_Quit();
  }
  void Application::OnEvent(Event& e){
		std::cout<<e<<std::endl;
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_ENVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_ENVENT_FN(Application::OnMousePressed));
	
	}
	void Application::OnUpdate(){

		// float t = 0.001;

    // face->SetVel( face->GetVel()+(Vec2(0,9.8))*t );
		// face->SetPos( face->GetPos()+face->GetVel()*t);

		// face->SetPosition((face->GetPos().x)*m_Window->GetWidth(),
		// 				(face->GetPos().y)*m_Window->GetHeight());

		// if(face->GetPos().y>1-20.0/m_Window->GetHeight())
		// {
		// 	face->SetPos({face->GetPos().x,1-20.0/m_Window->GetHeight()});
		// 	face->SetVel( {face->GetVel().x,-face->GetVel().y*0.5} );
		// }
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