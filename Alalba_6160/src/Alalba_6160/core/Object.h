#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "Vec2.h"
namespace Alalba
{
  class Object
  {
  public:
    Object(std::uint32_t winID,std::string texture)
    {
      //Load image at specified path
      SDL_Surface* loadedSurface = IMG_Load( texture.c_str() );
      if( loadedSurface == NULL )
      {
          printf( "Unable to load image %s! SDL_image Error: %s\n", texture.c_str(), IMG_GetError() );
      }
      else
      {
          //Create texture from surface pixels
          m_Texture = SDL_CreateTextureFromSurface( SDL_GetRenderer(SDL_GetWindowFromID(winID)), loadedSurface );
          if( m_Texture == NULL )
          {
              printf( "Unable to create texture from %s! SDL Error: %s\n", texture.c_str(), SDL_GetError() );
          }
          //Get rid of old loaded surface
          SDL_FreeSurface( loadedSurface );
      }
      m_Rect = new SDL_Rect();
    }
    ~Object()=default;
    inline  void SetScale(int x, int y, int width, int height){
      
      m_Rect->x = x;
      m_Rect->y = y;
      m_Rect->w = width;
      m_Rect->h = height;
      pos = Vec2(x,y);
    }
    inline void SetPosition(int x,int y){
      m_Rect->x = x;
      m_Rect->y = y;
    }
    inline void SetVel(Vec2 vel){
      velocity.x = vel.x;
      velocity.y = vel.y;
    }
    inline void SetPos(Vec2 _pos){
      pos.x = _pos.x;
      pos.y = _pos.y;
    }
    inline SDL_Texture* const  GetTExture()const {return m_Texture;}
    inline SDL_Rect* const GetRect()const {return m_Rect;}
    inline Vec2& GetPos(){return pos;}
    inline Vec2 GetVel(){return velocity;}
  protected:
    std::uint32_t m_winID;
    SDL_Rect* m_Rect;
    Vec2 pos, velocity, acc;
    SDL_Texture* m_Texture;
  };
}

