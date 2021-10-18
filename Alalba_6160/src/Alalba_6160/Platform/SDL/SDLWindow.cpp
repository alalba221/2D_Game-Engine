#include "alalbapch.h"
#include "SDLWindow.h"
#include "Alalba_6160/core/Events/Event.h"
#include "Alalba_6160/core/Events/ApplicationEvent.h"
#include "Alalba_6160/core/Events/KeyEvent.h"
#include "Alalba_6160/core/Events/MouseEvent.h"
// #include "Alalba/Core/Log.h"

//#include <glad/glad.h>
namespace Alalba 
{
	static bool s_SDLInitialized = false;

	SDLWindow::SDLWindow(const WindowProps& prop)
	{
		//ALALBA_CORE_INFO("SDL WINDOW API");
		Init(prop);
	}
	SDLWindow::~SDLWindow()
	{
		Shutdown();
	}
	void SDLWindow::OnUpdate()
	{
		//SDL_GL_SwapWindow(m_Window);
		/// Event loop
		SDL_Event sdlevent;
		//SDL_WaitEvent(&sdlevent);
		do {
				WindowData* data = (WindowData*)SDL_GetWindowData(m_Window,"data");
				switch (sdlevent.type) 
				{
					// Window event
					case SDL_WINDOWEVENT:
					{
						switch(sdlevent.window.event)
						{
							case	SDL_WINDOWEVENT_CLOSE:
							{
								WindowCloseEvent event;
								data->EventCallback(event);
								break;
							}
							case SDL_WINDOWEVENT_RESIZED:
							{
								data->Width = sdlevent.window.data1;
								data->Height = sdlevent.window.data2;
								//ALALBA_CORE_INFO("Windowresize {0},{1}",(float)sdlevent.window.data1,(float)sdlevent.window.data2);
								WindowResizeEvent event(sdlevent.window.data1, sdlevent.window.data2);
								data->EventCallback(event);
							}								
						}
						break;
					}
					//Key board
					case SDL_KEYDOWN:
					{
						KeyPressedEvent event(sdlevent.key.keysym.scancode, sdlevent.key.repeat);
						data->EventCallback(event);
						break;
					}
					case SDL_KEYUP:
					{
						KeyReleasedEvent event(sdlevent.key.keysym.scancode);
						data->EventCallback(event);
						break;
					}
					// Mouse Event
					case SDL_MOUSEMOTION:
					{
						MouseMovedEvent event((float)sdlevent.motion.x, (float)sdlevent.motion.y);
						//ALALBA_CORE_INFO("Mouse {0},{1}",(float)sdlevent.motion.xrel,(float)sdlevent.motion.yrel);
						data->EventCallback(event);
						break;
					}
					case SDL_MOUSEBUTTONDOWN:
					{
						MouseButtonPressedEvent event(sdlevent.button.button,sdlevent.button.x,sdlevent.button.y);
						data->EventCallback(event);
						break;
					}
					case SDL_MOUSEBUTTONUP:
					{
						MouseButtonReleasedEvent event(sdlevent.button.button);
						data->EventCallback(event);
						
						break;
					}
					case SDL_MOUSEWHEEL:
					{
						MouseScrolledEvent event((float)sdlevent.wheel.x, (float)sdlevent.wheel.y);
						data->EventCallback(event);
						break;
					}
					default:
						break;
				}
		} while (SDL_PollEvent(&sdlevent));
		
	}
	void SDLWindow::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
	}
	bool SDLWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void SDLWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;


		if (!s_SDLInitialized)
		{
			int sucess = SDL_Init(SDL_INIT_EVERYTHING);
			s_SDLInitialized = true;
		}
		
    m_Window = SDL_CreateWindow(props.Title.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              (int)props.Width,
                              (int)props.Height,
                             0);
		SDL_SetWindowData(m_Window,"data",&m_Data);
		// SetVSync(true);
	}
	void SDLWindow::Shutdown()
	{
		SDL_DestroyWindow(m_Window);
    SDL_Quit();
	}
}
