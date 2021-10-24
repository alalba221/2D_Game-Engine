#pragma once
#include "Alalba_6160/Renderer/Renderer.h"
#include <SDL2/SDL.h>
#include "Alalba_6160/Renderer/TextureManager.h"
#include "Alalba_6160/core/Entities/Entity.h"
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
    virtual void InitImpl(unsigned int winID, const Scene& scene) override;
    virtual void RenderImpl() override;
    virtual void SubmitImpl(const Object& obj) override;
		virtual void SubmitImpl(const Scene& scene) override;

  private:
    SDL_Renderer* m_Renderer;
    unsigned int lastFrame, 
    frametime, framestart;
		TextureManager* m_TextureManager;
		CameraComponent* m_Camera;
  };
}