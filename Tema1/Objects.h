
#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

#define WHITE (glm::vec3(0, 0, 0))
#define BROWN (glm::vec3(1, 0.8, 0.8))
#define ARROWLENGTH (100)
#define ARROWWIDTH (2)
#define BOWRADIUS (50)
#define SHURIKENLENGTH (30)
#define BALLOONRADIUS (50)
#define HEARTLENGTH (25)

namespace Objects
{
	// Create square with given bottom left corner, length and color
	Mesh* CreateArrow();
	Mesh* CreateBow();
	Mesh* CreateShuriken();
	Mesh* CreateBalloon(glm::vec3 color, glm::vec3 color2);
	Mesh* CreateHeart();
	Mesh* CreatePowerBar(glm::vec3 color);
	Mesh* CreateBarBox(glm::vec3 color);
	Mesh* CreateCupidon();
	Mesh* CreateHand();
}

