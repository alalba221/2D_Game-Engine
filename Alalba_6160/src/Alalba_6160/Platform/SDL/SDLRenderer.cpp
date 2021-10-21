#include "SDLRenderer.h"

namespace Alalba
{
  void SDLRenderer::InitImpl(unsigned int winID)
  {
    m_Renderer = SDL_CreateRenderer(SDL_GetWindowFromID(winID),-1,0);
		m_TextureManager = new TextureManager(m_Renderer);
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
  
		// auto group1 = scene.Reg().group<TransformComponent>(entt::get<TextureComponent>);
		
		// for (auto entity : group1)
		// {
		// 	auto[transform, texture] = scene.Reg().get<TransformComponent, TextureComponent>(entity);
		// 	auto dstRect = SDL_Rect();
    // // if (followCamera) {
    // //     dstRect.x = transform->left() - camera->left() + texture->offSetX;
    // //     dstRect.y = transform->top() - camera->top() + texture->offSetY;
    // // } else {
    //     dstRect.x = transform.left() + texture.offSetX;
    //     dstRect.y = transform.top() + texture.offSetY;
    // // }

		// 	dstRect.w = texture.w > 0 ? texture.w : transform.w;
		// 	dstRect.h = texture.h > 0 ? texture.h : transform.h;

		// 	m_TextureManager->renderTexture(texture.id, dstRect, texture.flipH, texture.flipV);
		// }
		auto entities = scene.GetEntities();
		for(Entity* entity: entities)
		{
			//auto[transform, texture] = scene.Reg().get<TransformComponent, TextureComponent>(entity);
			
			if(!entity->HasComponent<TextureComponent>())
				continue;
			auto transform = entity->GetComponent<TransformComponent>();
			auto texture = entity->GetComponent<TextureComponent>();
			auto dstRect = SDL_Rect();
			dstRect.x = transform.left() + texture.offSetX;
      dstRect.y = transform.top() + texture.offSetY;
			dstRect.w = texture.w > 0 ? texture.w : transform.w;
			dstRect.h = texture.h > 0 ? texture.h : transform.h;

			m_TextureManager->renderTexture(texture.id, dstRect, texture.flipH, texture.flipV);
		}


  }
}