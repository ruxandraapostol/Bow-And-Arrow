#pragma once

#include <Component/SimpleScene.h>
#include <TextRenderer/TextRenderer.h>
#include <Core/Engine.h>
#include <string>

#define TRANSLATE_FACTOR (100)
#define TRANSLATE_LIMIT	(.3f)
#define ROTATE_MOUSE_FACTOR (.008f)

#define RED	(glm::vec3(1, .3, .3))
#define DARKRED (glm::vec3(1, .2, 0))
#define YELLOW (glm::vec3(1, 1, .5))
#define DARKYELLOW (glm::vec3(1, .9, .4))

#define ARROWLEN (114)

#define SHURIKENRADIUS (21.21f)
#define SHURIKENSPEED (100)



class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		void BalloonsTarget(float* balloons, float deltaTimeSeconds,
			float degreeArrow, std::string name);

		glm::mat3 modelMatrix;

		float translateBowX, translateBowY;
		float translateArrowX, translateArrowY;

		float degreeArrow, speedArrow, maximHeight;
		bool releaseArrow;
		float shurikenDegree;
		float powerBarScaleRaport;

		float balloonsG[40];
		float balloonsR[40];
		float shuriken[40];

		int numberOfLives;
		float score;
		TextRenderer* Text;
};
