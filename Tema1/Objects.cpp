


#include "Objects.h"

#include <Core/Engine.h>

Mesh* Objects::CreateArrow()
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), BROWN),
		VertexFormat(glm::vec3(ARROWLENGTH, 0, 0), BROWN),
		VertexFormat(glm::vec3(ARROWLENGTH, ARROWWIDTH, 0), BROWN),
		VertexFormat(glm::vec3(0, ARROWWIDTH, 0), WHITE),

		VertexFormat(glm::vec3(ARROWLENGTH, 5 * ARROWWIDTH, 0), BROWN),
		VertexFormat(glm::vec3(ARROWLENGTH, -5 * ARROWWIDTH, 0), BROWN),
		VertexFormat(glm::vec3(ARROWLENGTH + 7 * ARROWWIDTH, 0.5f * ARROWWIDTH, 0), BROWN)
	};

	std::vector<unsigned short> indices = { 0, 1, 2, 3, 0, 2, 6, 5, 4 };

	Mesh* arrow = new Mesh("arrow");
	arrow->InitFromData(vertices, indices);
	return arrow;
}


Mesh* Objects::CreateBow()
{
	std::vector<VertexFormat> vertices;
	std::vector<GLushort> indices;
	GLfloat degree = 0;

	for (GLushort i = 0; i < 3141; i++)
	{
		degree = i * 0.001f;

		vertices.emplace_back(glm::vec3(BOWRADIUS * cos(degree), BOWRADIUS * sin(degree), 0), BROWN);
		indices.push_back(i);
	}

	Mesh* bow = new Mesh("bow");
	bow->InitFromData(vertices, indices);
	bow->SetDrawMode(GL_LINE_LOOP);
	return bow;
}

Mesh* Objects::CreateShuriken() {
	float middle = SHURIKENLENGTH / 2;
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), WHITE),
		VertexFormat(glm::vec3(0, middle, 0), WHITE),
		VertexFormat(glm::vec3(middle, middle, 0), WHITE),

		VertexFormat(glm::vec3(middle, 0, 0), WHITE),
		VertexFormat(glm::vec3(middle, middle, 0), WHITE),
		VertexFormat(glm::vec3(SHURIKENLENGTH, 0, 0), WHITE),

		VertexFormat(glm::vec3(0, SHURIKENLENGTH, 0), WHITE),
		VertexFormat(glm::vec3(middle, SHURIKENLENGTH, 0), WHITE),
		VertexFormat(glm::vec3(middle, middle, 0), WHITE),

		VertexFormat(glm::vec3(SHURIKENLENGTH, SHURIKENLENGTH, 0), WHITE),
		VertexFormat(glm::vec3(middle, middle, 0), WHITE),
		VertexFormat(glm::vec3(SHURIKENLENGTH, middle, 0), WHITE),


	};

	std::vector<unsigned short> indices = { 
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
	};


	Mesh* shuriken = new Mesh("shuriken");
	shuriken->InitFromData(vertices, indices);
	return shuriken;
}

Mesh* Objects::CreateBalloon(glm::vec3 color, glm::vec3 color2) {
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(10, -BALLOONRADIUS + 2, 0), color),
		VertexFormat(glm::vec3(-10, -BALLOONRADIUS + 2, 0), color),
		VertexFormat(glm::vec3(0, -BALLOONRADIUS - 15, 0), color),

		VertexFormat(glm::vec3(0, -BALLOONRADIUS - 22, 0), color),
		VertexFormat(glm::vec3(15, -BALLOONRADIUS - 40, 0), color),
		VertexFormat(glm::vec3(15, -BALLOONRADIUS - 42, 0), color),

		VertexFormat(glm::vec3(-15, -BALLOONRADIUS - 60, 0), color),
		VertexFormat(glm::vec3(-15, -BALLOONRADIUS - 62, 0), color),

		VertexFormat(glm::vec3(15, -BALLOONRADIUS - 80, 0), color),
		VertexFormat(glm::vec3(15, -BALLOONRADIUS - 82, 0), color),

		VertexFormat(glm::vec3(-15, -BALLOONRADIUS - 100, 0), color),
		VertexFormat(glm::vec3(-15, -BALLOONRADIUS - 102, 0), color),

		VertexFormat(glm::vec3(0, 0, 0), color2)
	};

	std::vector<unsigned short> indices = { 
		0, 1, 2,

		2, 3, 4,
		3, 4, 5,

		4, 5, 6,
		5, 6, 7,

		6, 7, 8,
		7, 8, 9,

		8, 9, 10,
		9, 10, 11
	};

	GLfloat degree = 0;
	for (GLushort i = 0; i < 6281; i++)
	{
		degree = i * 0.001f;
		vertices.emplace_back(glm::vec3(BALLOONRADIUS * cos(degree), BALLOONRADIUS * sin(degree), 0), color);
		indices.push_back(12);
		indices.push_back(i + 13);
		indices.push_back(i + 14);
	}
	vertices.emplace_back(glm::vec3(BALLOONRADIUS, 0, 0), color);

	std::string name = "balloonR";
	if (color != glm::vec3(1, .3, .3)) {
		name = "balloonG";
	}

	Mesh* balloon = new Mesh(name);
	balloon->InitFromData(vertices, indices);
	return balloon;
}

Mesh* Objects::CreateHeart() 
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), WHITE),
		VertexFormat(glm::vec3(-HEARTLENGTH, HEARTLENGTH, 0), WHITE),
		VertexFormat(glm::vec3(HEARTLENGTH, HEARTLENGTH, 0), WHITE),

		VertexFormat(glm::vec3(- HEARTLENGTH / 2, HEARTLENGTH, 0), WHITE),		// centrul buclei 1
		VertexFormat(glm::vec3(HEARTLENGTH / 2 , HEARTLENGTH, 0), WHITE)			// centrul buclei 2
	};

	std::vector<unsigned short> indices = { 0, 1, 2};

	float degree;
	float radius = HEARTLENGTH / 2;
	for (int i = 0; i < 3141; i++) {
		degree = i * 0.001f;
		vertices.emplace_back(glm::vec3( -radius + radius * cos(degree), HEARTLENGTH + radius * sin(degree), 0), WHITE);
		indices.push_back(3);
		indices.push_back(i + 5);
		indices.push_back(i + 6);
	}
	VertexFormat(glm::vec3(0, HEARTLENGTH, 0), WHITE);

	for (int i = 0; i < 3141; i++) {
		degree = i * 0.001f;
		vertices.emplace_back(glm::vec3(radius + radius * cos(degree), HEARTLENGTH + radius * sin(degree), 0), WHITE);
		indices.push_back(4);
		indices.push_back(i + 3147);
		indices.push_back(i + 3148);
	}
	VertexFormat(glm::vec3(HEARTLENGTH, HEARTLENGTH, 0), WHITE);

	Mesh* heart = new Mesh("heart");
	heart->InitFromData(vertices, indices);
	return heart;
}

Mesh* Objects::CreatePowerBar(glm::vec3 color)
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(0, BOWRADIUS / 2, 0), color),
		VertexFormat(glm::vec3(BOWRADIUS, 0, 0), color),
		VertexFormat(glm::vec3(BOWRADIUS, BOWRADIUS / 2, 0), color)
	};

	std::vector<unsigned short> indices = { 0, 1, 2, 1, 2, 3 };
	std::string name;

	if (color == glm::vec3{ 0.3, 0.8, 0.1 }) {
		name = "greenBar";
	}
	else {
		name = "grayBar";
	}

	Mesh* bar = new Mesh(name);
	bar->InitFromData(vertices, indices);
	return bar;
}

Mesh* Objects::CreateBarBox(glm::vec3 color)
{
	std::vector<VertexFormat> vertices;

	std::vector<unsigned short> indices;

	for(int i = 0; i < 5; i++) {
		vertices.emplace_back(glm::vec3((i + 1) * BOWRADIUS / 5, 0, 0), color);
		vertices.emplace_back(glm::vec3(i * BOWRADIUS / 5, BOWRADIUS / 2, 0), color);
		indices.push_back(2 * i);
		indices.push_back(2 * i + 1);
	};

	vertices.emplace_back(glm::vec3(BOWRADIUS, BOWRADIUS / 2, 0), color);
	vertices.emplace_back(glm::vec3(0, 0, 0), color);

	// dreptunghi incadrator
	{
		indices.push_back(1);
		indices.push_back(10);

		indices.push_back(1);
		indices.push_back(11);

		indices.push_back(8);
		indices.push_back(10);

		indices.push_back(8);
		indices.push_back(11);
	}

	Mesh* bar = new Mesh("barBox");
	bar->InitFromData(vertices, indices);
	bar->SetDrawMode(GL_LINES);
	return bar;
}

Mesh* Objects::CreateCupidon() 
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	float degree = 0;
	int n = 630;

	// capul
	{
		vertices.emplace_back(glm::vec3(0, 0, 0), WHITE);
		for (GLushort i = 0; i < 628; i++)
		{
			degree = i * 0.01f;
			vertices.emplace_back(glm::vec3(20 * cos(degree), 20 * sin(degree), 0), WHITE);
			indices.push_back(0);
			indices.push_back(i + 1);
			indices.push_back(i + 2);
		}
		vertices.emplace_back(glm::vec3(20, 0, 0), WHITE);
	}

	// buclele
	{
		for (GLushort j = 0; j < 6; j++)
		{
			vertices.emplace_back(glm::vec3(20 * cos(1 + j * 0.5), 20 * sin(1 + j * 0.5), 0), WHITE);
			for (GLushort i = 0; i < 628; i++)
			{
				degree = i * 0.01f;
				vertices.emplace_back(glm::vec3(static_cast<float>(20 * cos(1 + j * 0.5) + 7 * cos(degree)),
					static_cast<float>(20 * sin(1 + j * 0.5) + 7 * sin(degree)), 0), WHITE);
				indices.push_back(n);
				indices.push_back(i + n + 1);
				indices.push_back(i + n + 2);
			}
			vertices.emplace_back(glm::vec3(20 * cos(1 + j * 0.5) + 7, 20 * sin(1.04 + j * 0.5), 0), WHITE);
			n += 630;
		}
	}

	// corpul 
	{
		vertices.emplace_back(glm::vec3(50 * cos(4.71), 40 * sin(4.71) + 2, 0), WHITE);
		for (GLushort i = 0; i < 628; i++)
		{
			degree = i * 0.01f;
			vertices.emplace_back(glm::vec3(40 * cos(4.71) + 25 * cos(degree),
				50 * sin(4.71) + 30 * sin(degree) + 2, 0), WHITE);
			indices.push_back(n);
			indices.push_back(i + n + 1);
			indices.push_back(i + n + 2);
		}
		vertices.emplace_back(glm::vec3(50 * cos(4.71) + 25, 40 * sin(4.71) + 2, 0), WHITE);
		n += 630;
	}
	
	// mana statica
	{
		vertices.emplace_back(glm::vec3(10, -40, 0), WHITE);
		vertices.emplace_back(glm::vec3(60, -20, 0), WHITE);
		vertices.emplace_back(glm::vec3(60, -30, 0), WHITE);
		vertices.emplace_back(glm::vec3(10, -50, 0), WHITE);


		indices.push_back(n);
		indices.push_back(n + 1);
		indices.push_back(n + 2);

		indices.push_back(n);
		indices.push_back(n + 2);
		indices.push_back(n + 3);

		n += 4;

		vertices.emplace_back(glm::vec3(60, - 25, 0), WHITE);
		for (GLushort i = 0; i < 628; i++)
		{
			degree = i * 0.01f;
			vertices.emplace_back(glm::vec3(60 + 8 * cos(degree), -25 + 8 * sin(degree), 0), WHITE);
			indices.push_back(n);
			indices.push_back(i + n + 1);
			indices.push_back(i + n + 2);
		}
		vertices.emplace_back(glm::vec3(68, -25, 0), WHITE);
		n += 630;
	}

	// picioare
	{
		// dreptul
		{
			vertices.emplace_back(glm::vec3(5, -65, 0), WHITE);
			vertices.emplace_back(glm::vec3(15, -70, 0), WHITE);
			vertices.emplace_back(glm::vec3(-5, -95, 0), WHITE);
			vertices.emplace_back(glm::vec3(5, -100, 0), WHITE);
			vertices.emplace_back(glm::vec3(-20, -120, 0), WHITE);
			vertices.emplace_back(glm::vec3(-30, -115, 0), WHITE);


			indices.push_back(n);
			indices.push_back(n + 1);
			indices.push_back(n + 2);

			indices.push_back(n + 1);
			indices.push_back(n + 2);
			indices.push_back(n + 3);

			indices.push_back(n + 3);
			indices.push_back(n + 2);
			indices.push_back(n + 5);

			indices.push_back(n + 3);
			indices.push_back(n + 4);
			indices.push_back(n + 5);

			n += 6;
		}

		//stangul
		{
			vertices.emplace_back(glm::vec3(-10, -65, 0), WHITE);
			vertices.emplace_back(glm::vec3(-0, -70, 0), WHITE);
			vertices.emplace_back(glm::vec3(-30, -85, 0), WHITE);
			vertices.emplace_back(glm::vec3(-20, -90, 0), WHITE);

			vertices.emplace_back(glm::vec3(-28, -95, 0), WHITE);
			vertices.emplace_back(glm::vec3(-40, -70, 0), WHITE);
			vertices.emplace_back(glm::vec3(-48, -75, 0), WHITE);

			indices.push_back(n);
			indices.push_back(n + 1);
			indices.push_back(n + 2);

			indices.push_back(n + 1);
			indices.push_back(n + 2);
			indices.push_back(n + 3);

			indices.push_back(n + 3);
			indices.push_back(n + 4);
			indices.push_back(n + 6);

			indices.push_back(n + 6);
			indices.push_back(n + 3);
			indices.push_back(n + 5);

			n += 7;
		}
	}
	
	// aripi
	{
		vertices.emplace_back(glm::vec3(0, -40, 0), WHITE);		// 0
		vertices.emplace_back(glm::vec3(-50, 30, 0), WHITE);	// 1
		vertices.emplace_back(glm::vec3(-20, -60, 0), WHITE);	// 2
		vertices.emplace_back(glm::vec3(-70, 0, 0), WHITE);		// 3

		indices.push_back(n);
		indices.push_back(n + 1);
		indices.push_back(n + 2);

		indices.push_back(n);
		indices.push_back(n + 2);
		indices.push_back(n + 3);

		n += 4;
	}

	Mesh* cupidon = new Mesh("cupidon");
	cupidon->InitFromData(vertices, indices);
	return cupidon;
}

Mesh* Objects::CreateHand() {

	std::vector<VertexFormat> vertices;
	std::vector<unsigned short> indices;

	GLfloat degree = 0;

	vertices.emplace_back(glm::vec3(0, 0, 0), WHITE);
	vertices.emplace_back(glm::vec3(40, 0, 0), WHITE);
	vertices.emplace_back(glm::vec3(40, 10, 0), WHITE);
	vertices.emplace_back(glm::vec3(0, 10, 0), WHITE);


	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	vertices.emplace_back(glm::vec3(40, 5, 0), WHITE);
	for (GLushort i = 0; i < 628; i++)
	{
		degree = i * 0.01f;
		vertices.emplace_back(glm::vec3(40 + 8 * cos(degree), 5 + 8 * sin(degree), 0), WHITE);
		indices.push_back(4);
		indices.push_back(i + 5);
		indices.push_back(i + 6);
	}
	vertices.emplace_back(glm::vec3(48, 5, 0), WHITE);


	Mesh* hand = new Mesh("hand");
	hand->InitFromData(vertices, indices);
	return hand;
}