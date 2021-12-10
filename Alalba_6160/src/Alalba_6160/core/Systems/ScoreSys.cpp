#include "ScoreSys.h"

namespace Alalba
{
	

	void ScoreSys::Init(Scene& scene){
		std::cout<<"ScoreSys system init"<<std::endl;

	}
	
	void ScoreSys:: UpdateScoreTxt(Scene& scene, int score,const std::string& tag){
		
		auto view = scene.Reg().view<TextComponent>();
		for(auto& txt : view){
			Entity txtentity = {txt, &scene};
			if(txtentity.GetComponent<TagComponent>().Tag ==tag)
			{		
				txtentity.RemoveComponent<TextComponent>();
				txtentity.AddComponent<TextComponent>();
				txtentity.GetComponent<TextComponent>().text = std::to_string(score);
				txtentity.GetComponent<TextComponent>().color = {255,255,255};
			}		
		}
	}
	void ScoreSys::OnUpdate(Scene& scene){
		
		int redscore = 0;
		int bluescore = 0;
		
		auto view = scene.Reg().view<Rigidbody2DComponent>();
		for (auto e:view)
		{
			Entity entity = {e, &scene};
			auto& transform = entity.GetComponent<TransformComponent>();

			int score = 0;
			if(transform.Translation.x <15-tablewidth/4 || transform.Translation.x > 15+tablewidth/4|| transform.Translation.y < 12 - tablelength/2)
			{
				
				score = 0;
				
			}
			 else{
			
				if(transform.Translation.y < 12 - (450.0-119.0)/900.0 * tablelength/2)
					score = 3;
				else if(transform.Translation.y < 12 - (450.0-198.0)/900.0 * tablelength/2)
					score = 2;
				else if (transform.Translation.y < 12 - (450.0-521.0)/900.0 * tablelength/2)
					score = 1;
				else
					score = 0;
			}

			if(entity.GetComponent<TagComponent>().Tag=="Puck1"){
				redscore +=score;
				//UpdateScoreTxt(scene,score, "Shooter1");
			} else if(entity.GetComponent<TagComponent>().Tag=="Puck2"){
				bluescore +=score;
				//UpdateScoreTxt(scene, score, "Shooter2");
			}
		}
		//std::cout<<redscore<<std::endl;
		UpdateScoreTxt(scene,redscore, "RedScore");
		UpdateScoreTxt(scene, bluescore, "BlueScore");
	}


}