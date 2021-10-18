#include "Renderer.h"
#include "Alalba_6160/Platform/SDL/SDLRenderer.h"
namespace Alalba
{
  Renderer* Renderer::s_Instance = new SDLRenderer(); 
  
}