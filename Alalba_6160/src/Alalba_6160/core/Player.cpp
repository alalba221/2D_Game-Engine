#include "alalbapch.h"
#include "Player.h"
#include "Events/KeyEvent.h"
#include "KeyCodes.h"
namespace Alalba {

	Player::Player(entt::entity handle, Scene* scene)
		: Entity(handle, scene)
	{
	}

	void Player::setAnimation(ANIMATION_STATE state)
	{
		if (currentState == state) return;
    this->RemoveComponent<AnimationComponent>();

		switch (state) {
			case ANIMATION_STATE::RUNNING: {
				if (this->HasComponent<SuperMarioComponent>()) {
					this->AddComponent<AnimationComponent>(
						std::vector<TextureId>{
							TextureId::SUPER_MARIO_RUN_1,
							TextureId::SUPER_MARIO_RUN_2,
							TextureId::SUPER_MARIO_RUN_3},
						RUNNING_ANIMATION_SPEED
					);
				} else {
					this->AddComponent<AnimationComponent>(
						std::vector<TextureId>{
							TextureId::MARIO_RUN_1,
							TextureId::MARIO_RUN_2,
							TextureId::MARIO_RUN_3},
						RUNNING_ANIMATION_SPEED
					);
				}

				break;
			}
			case ANIMATION_STATE::STANDING:
				this->AddComponent<TextureComponent>(
					this->HasComponent<SuperMarioComponent>() ?
					TextureId::SUPER_MARIO_STAND :
					TextureId::MARIO_STAND);
				break;
			case ANIMATION_STATE::JUMPING:
				this->AddComponent<TextureComponent>(
					this->HasComponent<SuperMarioComponent>() ?
					TextureId::SUPER_MARIO_JUMP :
					TextureId::MARIO_JUMP);
				break;
			case ANIMATION_STATE::DRIFTING:
				this->AddComponent<TextureComponent>(
					this->HasComponent<SuperMarioComponent>() ?
					TextureId::SUPER_MARIO_DRIFT :
					TextureId::MARIO_DRIFT);
				break;
			case ANIMATION_STATE::DUCKING:
				if (this->HasComponent<SuperMarioComponent>()) {
					this->AddComponent<TextureComponent>(TextureId::SUPER_MARIO_DUCK);
				}
				break;
			case ANIMATION_STATE::BLINKING:
				break;
    }

    if (this->HasComponent<SuperMarioComponent>()) {
			this->GetComponent<TextureComponent>().h = TILE_SIZE * 2;
			this->GetComponent<TextureComponent>().offSetY = -3;
    } else {
			this->GetComponent<TextureComponent>().h = TILE_SIZE;
			this->GetComponent<TextureComponent>().offSetY = -1;
    }
    this->GetComponent<TextureComponent>().w = TILE_SIZE;
    this->GetComponent<TextureComponent>().offSetX = -2;
    currentState = state;
	}

	void Player::OnEvent(Event& event)
	{
		if (event.GetEventType() == Alalba::EventType::KeyPressed)
		{
			Alalba::KeyPressedEvent& e = (Alalba::KeyPressedEvent&)event;
			
			switch(e.GetKeyCode())
			{
				case ALALBA_A:
					left = true;
          break;
				case ALALBA_D:
					right = true;
					break;
				case ALALBA_W:
					jump = true;
					break;
				case ALALBA_S:
					duck = true;
          break;
			}
		}
		if (event.GetEventType() == Alalba::EventType::KeyReleased)
		{
			Alalba::KeyPressedEvent& e = (Alalba::KeyPressedEvent&)event;
			switch(e.GetKeyCode())
			{
				case ALALBA_A:
					left = false;
          break;
				case ALALBA_D:
					right = false;
					break;
				case ALALBA_W:
					jump = false;
					break;
				case ALALBA_S:
					duck = false;
          break;
			}

		}
	}
}
