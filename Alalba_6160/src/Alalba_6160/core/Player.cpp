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

	void Player::OnUpdate()
	{
		auto& transform = this->GetComponent<TransformComponent>();
		auto& texture = this->GetComponent<TextureComponent>();
		auto& kinetic = this->GetComponent<KineticComponent>();

		if (duck && this->HasComponent<SuperMarioComponent>()) {
			kinetic.accX = 0;
    } else {
        if (this->HasComponent<BottomCollisionComponent>()) {
            kinetic.speedX = (float) dirX * MARIO_ACCELERATION_X * 1.7f;
            if (sprint) kinetic.accX *= 1.5;
            if (jump) {
                this->GetComponent<KineticComponent>().accY = -MARIO_JUMP_ACCELERATION;
                // world->create()->assign<SoundComponent>(Sound::Id::JUMP);
            }
            if ((bool) std::abs(kinetic.speedX) || (bool) std::abs(kinetic.accX)) {
                if ((kinetic.speedX > 0 && kinetic.accX < 0) ||
                    (kinetic.speedX < 0 && kinetic.accX > 0)) {
                    setAnimation(ANIMATION_STATE::DRIFTING);
                } else {
                    setAnimation(ANIMATION_STATE::RUNNING);
                }
            } else {
                setAnimation(ANIMATION_STATE::STANDING);
            }

        } else {
            kinetic.accX = (float) (dirX) * (MARIO_ACCELERATION_X);
            if (sprint) kinetic.accX *= 1.5;
            //setAnimation(ANIMATION_STATE::JUMPING);
        }
    }

		if (left || right) lookingLeft = left;
		this->GetComponent<TextureComponent>().flipH = lookingLeft;
    jump = false;
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
					//setAnimation(ANIMATION_STATE::RUNNING);
          break;
				case ALALBA_D:
					right = true;
					//setAnimation(ANIMATION_STATE::RUNNING);
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
					//setAnimation(ANIMATION_STATE::STANDING);
          break;
				case ALALBA_D:
					right = false;
					//setAnimation(ANIMATION_STATE::STANDING);
					break;
				case ALALBA_W:
					jump = false;
					break;
				case ALALBA_S:
					duck = false;
          break;
			}

		}
		dirX = right - left;
	}
}
