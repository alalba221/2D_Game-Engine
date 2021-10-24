#pragma once

#include "Base.h"
#include "Events/Event.h"

namespace Alalba
{
	enum class WindowAPI{
		GLFW = 0,
		SDL = 1
	};
	class WindowProps 
	{
	public:
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title="Alalba Engine",
			// unsigned int width = SNES_RESOLUTION_WIDTH * ZOOM,
			// unsigned int height = SNES_RESOLUTION_HEIGHT * ZOOM)
			unsigned int width = 230*TILE_SIZE,
			unsigned int height = 14 * TILE_SIZE)
			: Title(title),Width(width),Height(height)
		{

		}
	};


	class ALALBA_API Window
	{
	public:
	
  	using EventCallbackFn = std::function<void(Event&)>;
		
		Window() = default;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;
		virtual void Shutdown() = 0;
		virtual unsigned int GetWidth()const = 0;
		virtual unsigned int GetHeight() const = 0;

		//Window Attribute
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync()const = 0;

		virtual void* GetNativeWindow() const = 0;
	
		static Window* Create(const WindowProps& props = WindowProps());
		inline static WindowAPI GetAPI(){return s_WindowAPI;}
		inline static WindowAPI SetAPI(WindowAPI api)
		{
			s_WindowAPI = api; 
			return s_WindowAPI;
		}
	private:
		static WindowAPI s_WindowAPI;
	};

}