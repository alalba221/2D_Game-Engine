#include "SDLRenderer.h"

namespace Alalba
{
  void SDLRenderer::InitImpl(unsigned int winID, const Scene& scene)
  {
		m_Renderer = SDL_CreateRenderer(SDL_GetWindowFromID(winID),-1,0);
		m_TextureManager = new TextureManager(m_Renderer);
		//SDL_RenderSetLogicalSize(m_Renderer, SNES_RESOLUTION_WIDTH*4 , SNES_RESOLUTION_WIDTH*4);
		SDL_SetRenderDrawColor(m_Renderer, SKY_RED, SKY_GREEN, SKY_BLUE, 255);
		SDL_SetTextureBlendMode(m_TextureManager->texture, SDL_BLENDMODE_BLEND);
		
		auto entities = scene.GetEntities();
		// CameraComponent camera;
			// find camera
		for(Entity* entity: entities)	{	
			if(entity->GetComponent<TagComponent>().Tag == "Camera")
				m_Camera = &entity->GetComponent<CameraComponent>();
		}
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
		for(Entity* entity: entities)
		{			
			if(!entity->HasComponent<TextureComponent>())
				continue;
			auto transform = entity->GetComponent<TransformComponent>();
			auto texture = entity->GetComponent<TextureComponent>();

			auto dstRect = SDL_Rect();
			dstRect.x = (transform.left()- m_Camera->left() + texture.offSetX)*Meter2Pix;
		  dstRect.y = (transform.top() - m_Camera->top()+ texture.offSetY)*Meter2Pix;

			dstRect.w = transform.w*Meter2Pix* transform.Scale.x;
			dstRect.h = transform.h*Meter2Pix* transform.Scale.y;
			double angle = transform.Rotation.z *RAD2DEG;
		
			m_TextureManager->renderTexture(texture.id, dstRect, angle, texture.flipH, texture.flipV);
		}
  }
}