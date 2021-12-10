#pragma once

#include <utility>
#include <SDL2/SDL.h>
#include "Alalba_6160/Renderer/TextureManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "Alalba_6160/core/Base.h"
namespace Alalba{
  struct Component {
		virtual ~Component() = default;
  };

	struct TagComponent: public Component
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};
  


  struct SolidComponent : public Component {
		SolidComponent() = default;
  };
  struct CollectibleComponent : public Component {
		CollectibleComponent() = default;
  };

  struct FlagPoleComponent : public Component {
  };
  struct FlagComponent : public Component {
  };

  struct SuperMarioComponent : public Component {
		SuperMarioComponent() = default;
  };


  struct KineticComponent : public Component {
		KineticComponent() = default;

		explicit KineticComponent(float speedX,
										float speedY,
										float accX = 0.0,
										float accY = 0.0
		) : speedX(speedX), speedY(speedY), accX(accX), accY(accY) {}


		float speedX = 0;
		float speedY = 0;

		float accX = 0;
		float accY = 0;
  };

  struct GravityComponent : public Component {
		GravityComponent() = default;
  };

  // struct CallbackComponent : public Component {
  //		 CallbackComponent(std::function<void(void)> callback, int time) : callback{std::move(callback)}, time{time} {};

  //		 int time;
  //		 std::function<void(void)> callback;
  // };

  struct FrozenComponent : public Component {
  };

  struct DeadComponent : public Component {
  };
  struct GameOverComponent : public Component {
  };

  struct AnimationComponent : public Component {
		AnimationComponent() = default;
		explicit AnimationComponent(
						std::vector<TextureId>&& textures,
						int duration,
						bool flipH = false,
						bool flipV = false,
						bool loop = true
		) : textures{std::move(textures)},
				duration{duration},
				counter{duration},
				flipH{flipH},
				flipV{flipV},
				loop{loop} {}

		std::vector<TextureId> textures;
		int duration = 0;
		int counter = 0;
		bool flipH = false;
		bool flipV = false;
		bool loop = true;
		size_t currentTexture = 0;
  };

  struct TextureComponent : public Component {
		TextureComponent() =  default;
		explicit TextureComponent(TextureId id) : id{id} {};

		TextureId id;

		bool flipV = false;
		bool flipH = false;

		int w = 0;
		int h = 0;
		int offSetX = 0;
		int offSetY = 0;

		~TextureComponent() override = default;
  };

  namespace Enemy {
		enum Type {
			GOOMBA,
			TURTLE,
			TURTLE_SHELL
	};
  }


  enum class Direction {
		NONE,
		TOP,
		BOTTOM,
		LEFT,
		RIGHT
  };

  struct LeftCollisionComponent : public Component {
  };
  struct RightCollisionComponent : public Component {
  };
  struct TopCollisionComponent : public Component {
  };
  struct BottomCollisionComponent : public Component {
		BottomCollisionComponent() = default;
  };



  struct BreakableComponent : public Component {
		bool hit = false;

		int getHeight() {
				frames--;
				return height[frames];
		}

		 bool finished() const {
				return frames == 0;
		}

		void reset() {
				frames = 13;
		}

  private:
		int frames = 13;
		int height[13] = {-2, 1, 3, 2, 1, 1, 1, 0, 0, -1, -1, -4, -1};
  };

  // struct MusicComponent : public Component {
  //		 explicit MusicComponent(Music::Id music) : music{music} {};
  //		 Music::Id music;
  // };

  // struct SoundComponent : public Component {
  //		 explicit SoundComponent(Sound::Id sound) : sound{sound} {}

  //		 Sound::Id sound;
  // };

  struct TileComponent : public Component {
		TileComponent() = default;
  };

  struct CrushedComponent : public Component {
  };

  enum Points {
		ONEHOUNDRED,
		TWOHOUNDRED,
		ONEUP,
		ONETHOUSAND
  };

  struct CameraComponent : public Component {

		CameraComponent() = default;
	
		CameraComponent(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

		int x, y, width, height;

		 int left() const {
			return std::max(0, x - width / 2);
		}

		 int right() const {
			return x + width / 2;
		}

		 int top() const {
			return y - height / 2;
		}

		 int bottom() const {
			return y + height / 2;
		}

  };

	// struct Rigidbody2DComponent : public Component
	// {
	// 	enum class BodyType { Static = 0, Dynamic, Kinematic };
	// 	BodyType Type = BodyType::Dynamic;
	// 	bool FixedRotation = false;

	// 	// Storage for runtime
	// 	void* RuntimeBody = nullptr;

	// 	Rigidbody2DComponent() = default;
	// 	Rigidbody2DComponent(const Rigidbody2DComponent&) = default;
	// };

	// struct BoxCollider2DComponent : public Component
	// {
	// 	glm::vec2 Offset = { 0.0f, 0.0f };
	// 	glm::vec2 Size = { 0.5f, 0.5f };

	// 	// TODO(Yan): move into physics material in the future maybe
	// 	float Density = 1.0f;
	// 	float Friction = 0.5f;
	// 	float Restitution = 0.6f;
	// 	float RestitutionThreshold = 0.5f;

	// 	// Storage for runtime
	// 	void* RuntimeFixture = nullptr;

	// 	BoxCollider2DComponent() = default;
	// 	BoxCollider2DComponent(const BoxCollider2DComponent&) = default;
	// };
	struct TransformComponent : public Component {

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation , float _w = pucksize, float _h = pucksize)
			: Translation(translation) {
			w = _w ; h = _h;
			x =  translation.x;
			y = translation.y;
		}
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };// CenterPosition
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f }; // RotationAngle
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };
		
		glm::vec3 AngularVelocity = {0.0f,0.0f,0.0f};
		glm::vec3 CenterVelocity = { 0.0f, 0.0f, 0.0f };// CenterPosition

		glm::vec3 dV = {0.0f,0.0f,0.0f};
		glm::vec3 dW = { 0.0f, 0.0f, 0.0f };

		float right() const {
			return Translation.x + w/2.0;
		}

		float left() const {
			return Translation.x - w*Scale.x/2.0;
		}

		float top() const {
			return Translation.y - h*Scale.y/2.0;
		}

		float bottom() const {
			return Translation.y + h/2.0;
		}

		float getCenterX() const {
			return Translation.x;
		}

		float getCenterY() const {
			return Translation.y;
		}
		float getWidth() const{
			return w*Scale.x;
		}
		float getHeight() const{
			return h*Scale.y;
		}

		float w, h;
		float x, y;
		glm::vec3 shootDir = glm::vec3{0,-1,0};
		float strength = 0.1f;

		~TransformComponent() override = default;
  };
	
	struct CurrentPuck : public Component
	{
		CurrentPuck() = default;
	};
	struct PlayerComponent : public Component {
		PlayerComponent() = default;
		bool Enable = true;
		int score = 0;
		int scores[4];
		int count = 4;
  };

	struct TextComponent : public Component {

		

		TextComponent() = default;
		TextComponent(const TextComponent&) = default;
		TextComponent(const std::string& text)
			: text(text) {}


		// TextComponent() = default;
		// TextComponent(const TextComponent&) = default;
    std::string text;
    SDL_Texture* texture = nullptr;
		SDL_Color color = {255, 255, 255};
    ~TextComponent() override {
        SDL_DestroyTexture(texture);
    }
};
	struct Rigidbody2DComponent : public Component
	{
		enum class BodyType { Static = 0, Dynamic, Kinematic };
		enum class BodyShape { Circle = 0, Polygon };
		BodyType Type = BodyType::Dynamic;
		BodyShape Shape = BodyShape::Circle;
		bool FixedRotation = false;
		glm::vec2 Offset = { 0.0f, 0.0f };
		glm::vec2 Size = { 0.5f, 0.5f };
		float CircleRadius = pucksize/2;

		// TODO(Yan): move into physics material in the future maybe
		float Density = 1.0f;
		float Friction = 0.0f;
		float Restitution = 0.5f;
		float RestitutionThreshold = 0.5f;
		
		// Only for circle
		float Mass = Density * CircleRadius * CircleRadius * pi;
		float MomentOfInertia = Density * 
														CircleRadius * CircleRadius * CircleRadius * CircleRadius
														 * pi / 2.0; ;
		// Storage for runtime
		void* RuntimeBody = nullptr;
		Rigidbody2DComponent() = default;
		Rigidbody2DComponent(const Rigidbody2DComponent&) = default;
	};

}