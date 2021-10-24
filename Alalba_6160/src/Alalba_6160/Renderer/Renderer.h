#pragma once
#include "Alalba_6160/core/Window.h"
#include "Alalba_6160/core/Object.h"
#include "entt.hpp"
#include "Alalba_6160/core/Scene.h"
namespace Alalba
{
  class Renderer
  {
  public:
    static void Init(unsigned int winID, const Scene& scene) {s_Instance->InitImpl(winID,scene);};
    static void Render() {s_Instance->RenderImpl();};
    inline static Renderer* GetRenderer(){return s_Instance;}
    inline static  void Submit(const Object& obj){s_Instance->SubmitImpl(obj);}
		inline static  void Submit(const Scene& scene){s_Instance->SubmitImpl(scene);}
  protected:
    virtual void InitImpl(unsigned int winID, const Scene& scene)=0;
    virtual void RenderImpl()=0;
    virtual void SubmitImpl(const Object& obj)=0;
		virtual void SubmitImpl(const Scene& scene)=0;
  private:
		static Renderer* s_Instance;
    
  };
}
