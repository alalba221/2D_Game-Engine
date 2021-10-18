#include "alalbapch.h"
#include "Input.h"
#include "Alalba_6160/Platform/SDL/SDLInput.h"
//#include "Alalba/Platforms/Windows/GlfwInput.h"
namespace Alalba{

//  #ifdef SDL_WINDOW_API
    Input* Input::s_Instance = new SDLInput();
  // #else
  //   Input* Input::s_Instance = new GlfwInput();
  // #endif
}