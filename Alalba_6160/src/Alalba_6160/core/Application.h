#pragma once
#include "Base.h"
#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Object.h"
#include "Alalba_6160/Renderer/Renderer.h"
#include "Alalba.h"
#include "Scene.h"
#include "Entities/Entity.h"

namespace Alalba{
  class ALALBA_API Application{
		
  public:
		Application();
		virtual ~Application();

		void Run();

		virtual void OnInit() {}
		virtual void OnShutdown() {}
		virtual void OnUpdate(float t);

		virtual void OnEvent(Event& event);

		inline Window& GetWindow() { return *m_Window; }
		
		static inline Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnMousePressed(MouseButtonPressedEvent& e);
		bool OnMouseReleased(MouseButtonReleasedEvent& e);
		bool OnMouseMove(MouseMovedEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);

		void Clear();
	private:
		std::unique_ptr<Window> m_Window;
		unsigned int winID;
		bool m_Running = true;
		Renderer* m_Renderer;
		static Application* s_Instance;
		Scene* m_Scene;
		Scene * s_Scene;
		Entity* player1;
		Entity* player2;
		// temporary
		int count = 8;
  };
}