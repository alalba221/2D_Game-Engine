#pragma once
#include "Alalba_6160/core/Window.h"
#include "Alalba_6160/core/Object.h"
namespace Alalba
{
  class Renderer
  {
  public:
    static void Init(unsigned int winID) {s_Instance->InitImpl(winID);};
    static void Render() {s_Instance->RenderImpl();};
    inline static Renderer* GetRenderer(){return s_Instance;}
    inline static  void Submit(const Object& obj){s_Instance->SubmitImpl(obj);}
  protected:
    virtual void InitImpl(unsigned int winID)=0;
    virtual void RenderImpl()=0;
    virtual void SubmitImpl(const Object& obj)=0;
  private:
		static Renderer* s_Instance;
    
  };
}
