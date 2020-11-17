#include "Tema1.h"

#include <vector>
#include <iostream>
#include <ctime>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Objects.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}


void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);



	Text = new TextRenderer(resolution.x, resolution.y);
	Text->Load("Source/TextRenderer/Fonts/Arial.ttf", 25);

	// initializare variabile
	{
		translateBowX = 125;
		translateBowY = 500;

		translateArrowX = 100;
		translateArrowY = 500;

		degreeArrow = 0;
		shurikenDegree = 0;

		speedArrow = 10;
		releaseArrow = false;

		numberOfLives = 3;
		score = 0;
		powerBarScaleRaport = 0;
	}

	srand(time(0));
	for (int i = 0; i < 40; i+=4) {
		balloonsG[i] = float(250 + rand() % (window->GetResolution().x - 200));				// coordonata x
		balloonsG[i + 1] = float(-100 + rand() % (100 + window->GetResolution().y));		// coordonata y
		balloonsG[i + 2] = (3 + (rand() % 5)) * 0.1f;										// factor de scalare
		balloonsG[i + 3] = 0;																// tintit sau nu 

		balloonsR[i] = float(250 + rand() % (window->GetResolution().x - 200));				// coordonata x
		balloonsR[i + 1] = float (-100 + rand() % (100 + window->GetResolution().y));		// coordonata y
		balloonsR[i + 2] = (3 + (rand() % 5)) * 0.1f;										// factor de scalare
		balloonsR[i + 3] = 0;																// tintit sau nu 
	}

	for (int i = 0; i < 40; i += 4) {
		shuriken[i] = float(window->GetResolution().x + rand() % 1000);						// coordonata x
		shuriken[i + 1] = float(rand() % window->GetResolution().y);						// coordonata y
		shuriken[i + 2] = 0;																// unghiul deplasarii
		shuriken[i + 3] = 0;																// a atins arcul
	}


	// initializare obiecte 
	{
		Mesh* arrow = Objects::CreateArrow();
		AddMeshToList(arrow);

		Mesh* bow = Objects::CreateBow();
		AddMeshToList(bow);

		Mesh* shuriken = Objects::CreateShuriken();
		AddMeshToList(shuriken);

		Mesh* balloonG = Objects::CreateBalloon(YELLOW, DARKYELLOW);
		AddMeshToList(balloonG);

		Mesh* balloonR = Objects::CreateBalloon(RED, DARKRED);
		AddMeshToList(balloonR);

		Mesh* heart = Objects::CreateHeart();
		AddMeshToList(heart);

		Mesh* greenBar = Objects::CreatePowerBar(glm::vec3{ 0.3, 0.8, 0.1 });
		AddMeshToList(greenBar);

		Mesh* grayBar = Objects::CreatePowerBar(glm::vec3{ 0.3, 0.4, 0.5 });
		AddMeshToList(grayBar);

		Mesh* boxBar = Objects::CreateBarBox(glm::vec3{ 0.9, 0.8, 0.7 });
		AddMeshToList(boxBar);

		Mesh* cupidon = Objects::CreateCupidon();
		AddMeshToList(cupidon);

		Mesh* hand = Objects::CreateHand();
		AddMeshToList(hand);
	}
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::BalloonsTarget(float* balloons, float deltaTimeSeconds, 
	float degreeArrow, std::string name) {
	for (int i = 0; i < 40; i += 4) {
		// deplasare baloane
		{
			balloons[i + 1] += 20 * deltaTimeSeconds;
		}

		// animatie baloane nimerite 
		{
			if (balloons[i + 3]) {
				balloons[i + 2] -= 0.05f;
				Text->RenderText(to_string(balloons[i + 3]).substr(0, size(to_string(balloons[i + 3])) - 4),
					balloons[i], window->GetResolution().y - balloons[i + 1] - 50, 1.0f, glm::vec3(1.0, 1.0, 1.0));

			}
		}

		// desenare baloane
		{
			glm::mat3 modelMatrix = Transform2D::Translate(balloons[i], balloons[i + 1]);
			modelMatrix *= Transform2D::Scale(balloons[i + 2], balloons[i + 2] + 0.1f);
			RenderMesh2D(meshes[name], shaders["VertexColor"], modelMatrix);
		}

		// iesire baloane din scena 
		{
			if (balloons[i + 1] > window->GetResolution().y || balloons[i + 2] <= 0) {
				balloons[i] = float(250 + rand() % (window->GetResolution().x - 200));
				balloons[i + 1] = float(-200 + rand() % 100);
				balloons[i + 2] = (3 + (rand() % 5)) * 0.1f;
				balloons[i + 3] = 0;

			}
		}

		// balon tintit 
		{
			float coordonateX = translateArrowX + ARROWLEN * cos(degreeArrow) - balloons[i];
			coordonateX *= coordonateX;
			coordonateX /= (2500 * balloons[i + 2] * balloons[i + 2]);

			float coordonateY = translateArrowY + ARROWLEN * sin(degreeArrow) - balloons[i + 1];
			coordonateY *= coordonateY;
			coordonateY /= (2500 * (balloons[i + 2] + 0.1f)* (balloons[i + 2] + 0.1f));

			if (coordonateX * coordonateX + coordonateY * coordonateY <= 1) {
				if (name == "balloonR") {
					score += 20 * (1 - balloons[i + 2]);
					balloons[i + 3] = 20 * (1 - balloons[i + 2]);
					cout << "SCOR: " + to_string(score).substr(0, size(to_string(score)) - 4) + "\n";
				}
				else {
					score -= 10 * balloons[i + 2];
					balloons[i + 3] = - 10 * (1 - balloons[i + 2]);
					cout << "SCOR: " + to_string(score).substr(0, size(to_string(score)) - 4) + "\n";
				}
			}
		}
	}
}

void Tema1::Update(float deltaTimeSeconds)
{
	// desen vieti 
	{
		for (int i = 0; i < numberOfLives; i++) {
			modelMatrix = Transform2D::Translate(float(50 + 50 * i), float( window->GetResolution().y - 50));
			RenderMesh2D(meshes["heart"], shaders["Simple"], modelMatrix);
		}
	}


	// desen scor
	{
		string payload = "SCOR: " + to_string(score).substr(0, size(to_string(score)) - 4);
		Text->RenderText(payload, float(window->GetResolution().x - 15 * size(payload)), 20.0f, 1.0f, glm::vec3(1.0, 1.0, 1.0));
	}
	
	// desen sageata 
	{
		if (releaseArrow) {
			translateArrowX += speedArrow * cos(degreeArrow);
			translateArrowY += speedArrow * sin(degreeArrow);

			if (translateArrowY < 0 || translateArrowX > window->GetResolution().x ||
				translateArrowY > window->GetResolution().y) {
				releaseArrow = false;
				speedArrow = 0;
				powerBarScaleRaport = 0;

				translateArrowX = 100;
				translateArrowY = translateBowY;
			}
		}

		modelMatrix = Transform2D::Translate(translateArrowX, translateArrowY);
		modelMatrix *= Transform2D::Translate(-50, 0);
		modelMatrix *= Transform2D::Rotate(degreeArrow);
		modelMatrix *= Transform2D::Translate(50, 0);
		RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);
	}


	// desen arc
	{
		modelMatrix = Transform2D::Translate(translateBowX - 50, translateBowY);
		modelMatrix *= Transform2D::Rotate(degreeArrow);
		modelMatrix *= Transform2D::Scale(1.2f, 1.2f);
		RenderMesh2D(meshes["hand"], shaders["Simple"], modelMatrix);

		// mana mobila a personajului 
		modelMatrix = Transform2D::Translate(translateBowX, translateBowY);
		modelMatrix *= Transform2D::Rotate(-1.57f);
		RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);
	}

	// desen personaj
	{
		modelMatrix = Transform2D::Translate(translateBowX - 10, translateBowY + 80);
		modelMatrix *= Transform2D::Rotate(-0.5);
		modelMatrix *= Transform2D::Scale(1.2f, 1.2f);
		RenderMesh2D(meshes["cupidon"], shaders["Simple"], modelMatrix);
	}

	// desen PowerBar
	{

		modelMatrix = Transform2D::Translate(translateBowX, translateBowY - 100);
		RenderMesh2D(meshes["barBox"], shaders["VertexColor"], modelMatrix);

		modelMatrix = Transform2D::Translate(translateBowX, translateBowY - 100);
		modelMatrix *= Transform2D::Scale(powerBarScaleRaport, 1);
		RenderMesh2D(meshes["greenBar"], shaders["VertexColor"], modelMatrix);


		modelMatrix = Transform2D::Translate(translateBowX, translateBowY - 100);
		RenderMesh2D(meshes["grayBar"], shaders["VertexColor"], modelMatrix);
	}

	// desen baloane si tinta
	{
		BalloonsTarget(balloonsG, deltaTimeSeconds, degreeArrow, "balloonG");
		BalloonsTarget(balloonsR, deltaTimeSeconds, degreeArrow, "balloonR");
	}

	// desen shurikenuri
	for (int i = 0; i < 40; i += 4) {
		// deplasare si rotire 
		{
			shuriken[i] -= SHURIKENSPEED * (shuriken[i + 2] + 1) * deltaTimeSeconds * cos(shuriken[i + 2]);
			shuriken[i + 1] += SHURIKENSPEED * (shuriken[i + 2] + 1) * deltaTimeSeconds * sin(shuriken[i + 2]);
			shurikenDegree += 1.5f * deltaTimeSeconds;
		}

		// desenare
		{
			modelMatrix = Transform2D::Translate(shuriken[i], shuriken[i + 1]);
			modelMatrix *= Transform2D::Translate(15, 15);
			modelMatrix *= Transform2D::Rotate(shurikenDegree);
			modelMatrix *= Transform2D::Translate(-15, -15);
			RenderMesh2D(meshes["shuriken"], shaders["Simple"], modelMatrix);
		}

		// disparitie
		{
			if (shuriken[i] < 0 || shuriken[i + 1] > window->GetResolution().y) {
				shuriken[i] = float(window->GetResolution().x + rand() % 1000);
				shuriken[i + 1] = float(rand() % (1 + window->GetResolution().y));
				shuriken[i + 2] = 0;
				shuriken[i + 3] = 0;
			}
		}

		// ciocnire sageata
		{
			float coordonateX = translateArrowX + ARROWLEN * cos(degreeArrow) - (shuriken[i] + 15);
			float coordonateY = translateArrowY + ARROWLEN * sin(degreeArrow) - (shuriken[i + 1] + 15);

			if (coordonateX * coordonateX + coordonateY * coordonateY < SHURIKENRADIUS * SHURIKENRADIUS) {
				shuriken[i + 2] = 2.09f;
				score += 30;
				cout << "SCOR: " + to_string(score).substr(0, size(to_string(score)) - 4) + "\n";
			}
		}

		// ciocnire arc
		{
			float distanceCentersX = translateBowX - (shuriken[i] + 15);
			float distanceCentersY = translateBowY - (shuriken[i + 1] + 15);
			float distanceCenters = distanceCentersX * distanceCentersX + distanceCentersY * distanceCentersY;

			float radiusSum = (BOWRADIUS + SHURIKENRADIUS) * (BOWRADIUS + SHURIKENRADIUS);

			if (distanceCenters - radiusSum <= 0 && !shuriken[i + 3]) {
				numberOfLives --;
				shuriken[i + 3] = 1;
				if (numberOfLives == 0) {
					exit(0);
				}
			}
		}
	}
}


void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	// miscari arc
	{
		float newPosition = deltaTime * TRANSLATE_FACTOR;

		// se ridica pana la marginea ecranului 
		if (window->KeyHold(GLFW_KEY_W) && (translateBowY + BOWRADIUS + 10) < window->GetResolution().y) {
			translateBowY += newPosition;
			translateArrowY += newPosition;
		}

		// coboara pana la marginea ecranului 
		if (window->KeyHold(GLFW_KEY_S) && (translateBowY - BOWRADIUS - 10) > 0) {
			translateBowY -= newPosition;
			translateArrowY -= newPosition;
		}
	}


	// stabilire viteza sageata
	{
		if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT) && !releaseArrow)
		{
			if (speedArrow < 20) {
				speedArrow += deltaTime * 20;
				powerBarScaleRaport += 0.0165f;
			}
		}
	}
}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	float newDegree = degreeArrow - deltaY * ROTATE_MOUSE_FACTOR;

	// add mouse move event
	if(newDegree < 0.40f && newDegree > -0.40f && !releaseArrow) 
	degreeArrow = newDegree;
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event

	// click dreapta pentru a elibera sageata
	if (button == 2) {
		releaseArrow = true;
	}
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
