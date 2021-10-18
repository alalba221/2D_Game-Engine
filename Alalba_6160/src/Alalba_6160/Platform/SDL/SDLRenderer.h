#pragma once
#include "Alalba_6160/Renderer/Renderer.h"
#include <SDL2/SDL.h>
namespace Alalba
{
  constexpr int FPS = 60;
  constexpr int FRAME_DURATION = 1000 / FPS;
  
  class SDLRenderer : public Renderer
  {
  public:
    SDLRenderer(){
      lastFrame = SDL_GetTicks();
    }
    ~SDLRenderer(){}
    virtual void InitImpl(unsigned int winID) override;
    virtual void RenderImpl() override;
    virtual void SubmitImpl(const Object& obj) override;

  private:
    SDL_Renderer* m_Renderer;
    unsigned int lastFrame, 
    frametime, framestart;
  };
}