#include "SDLRenderer.h"

namespace Alalba
{
  void SDLRenderer::InitImpl(unsigned int winID)
  {
    m_Renderer = SDL_CreateRenderer(SDL_GetWindowFromID(winID),-1,0);
  };

  void SDLRenderer::RenderImpl()
  {
    
    framestart = SDL_GetTicks();
    
    frametime = SDL_GetTicks()-lastFrame;
    if (frametime < FRAME_DURATION) 
      SDL_Delay(FRAME_DURATION - frametime);
    SDL_RenderPresent(m_Renderer);
    lastFrame = framestart;
  };
  void SDLRenderer::SubmitImpl(const Object& obj){

    SDL_RenderCopy(m_Renderer,obj.GetTExture(),NULL,obj.GetRect());
  }
}