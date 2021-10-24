#include "SDLRenderer.h"

namespace Alalba
{
  void SDLRenderer::InitImpl(unsigned int winID)
  {
    m_Renderer = SDL_CreateRenderer(SDL_GetWindowFromID(winID),-1,0);
		m_TextureManager = new TextureManager(m_Renderer);
		SDL_RenderSetLogicalSize(m_Renderer, SNES_RESOLUTION_WIDTH , SNES_RESOLUTION_WIDTH);
		SDL_SetRenderDrawColor(m_Renderer, SKY_RED, SKY_GREEN, SKY_BLUE, 255);
		SDL_SetTextureBlendMode(m_TextureManager->texture, SDL_BLENDMODE_BLEND);
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
	void SDLRenderer::SubmitImpl(const Scene& scene){
		
		SDL_RenderClear(m_Renderer);
		auto entities = scene.GetEntities();
		CameraComponent camera ;
		for(Entity* entity: entities)
		{			
			// find camera
			if(entity->GetComponent<TagComponent>().Tag == "Camera")
				camera = entity->GetComponent<CameraComponent>();
			if(!entity->HasComponent<TextureComponent>())
				continue;
			auto transform = entity->GetComponent<TransformComponent>();
			auto texture = entity->GetComponent<TextureComponent>();
			
			auto dstRect = SDL_Rect();
			dstRect.x = transform.left()+ texture.offSetX;
      dstRect.y = transform.top() + texture.offSetY;
			// dstRect.x = transform.left()- camera.left() + texture.offSetX;
      // dstRect.y = transform.top() - camera.top()+ texture.offSetY;
			dstRect.w = texture.w > 0 ? texture.w : transform.w;
			dstRect.h = texture.h > 0 ? texture.h : transform.h;

			m_TextureManager->renderTexture(texture.id, dstRect, texture.flipH, texture.flipV);
		}


  }
}