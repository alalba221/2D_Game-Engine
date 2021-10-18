#include "alalbapch.h"
#include "Window.h"

#include "Alalba_6160/Platform/SDL/SDLWindow.h"
namespace Alalba{
  //WindowAPI Window::s_WindowAPI = WindowAPI::SDL;
  Window* Window::Create(const WindowProps& props)
	{
    // #ifdef SDL_WINDOW_API
      return new SDLWindow(props);
    // #else
    //   return new GlfwWindow(props);
    // #endif
	}
}