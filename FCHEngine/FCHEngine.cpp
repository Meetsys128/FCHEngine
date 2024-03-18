#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "glm/vec2.hpp"
struct Atom {


};
struct Molecule {
	std::vector<Atom> atoms;
	glm::vec2 pos;
	float temperature;
	olc::Pixel color;
};
class GameObject {
public:
	glm::vec2 pos;
	glm::vec2 vel;
	float rotation;
	std::vector<Molecule> molecules;
};
class FCHEngine2D : public olc::PixelGameEngine
{
public:
	std :: vector<GameObject> gameobjects;
public:
	FCHEngine2D()
	{
		sAppName = "FCHE";
		GameObject gb;
		gb = GameObject();
		gb.pos = { 40.0f,40.0f };
		gb.rotation = 0;
		gb.vel ={10.0f, 1.0f};
		gb.molecules = std::vector<Molecule>{};
		Molecule mol;
		mol.temperature = 100.0f;
		mol.color = olc::Pixel(255, 255, 255, 255);
		mol.pos = { 10.0f,0 };
		mol.atoms = std::vector<Atom>{};
		Atom atom;
		mol.atoms.push_back(atom);
		gb.molecules.push_back(mol);
		mol.pos = { -10.0f,0 };
		gb.molecules.push_back(mol);
		gameobjects.push_back(gb);
	}

public:
	bool OnUserCreate() override
	{
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		//drawing
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(64,64,64,255));
		for (int i = 0; i < gameobjects.size(); i++) {
			for (int j = 0; j < gameobjects[i].molecules.size(); j++) {
				glm::vec2 position = gameobjects[i].pos + glm::vec2(gameobjects[i].molecules[j].pos.x*cos(gameobjects[i].rotation) - (gameobjects[i].molecules[j].pos.y * sin(gameobjects[i].rotation)),   gameobjects[i].molecules[j].pos.y * cos(gameobjects[i].rotation) + (gameobjects[i].molecules[j].pos.x * sin(gameobjects[i].rotation)));
				Draw((int)position.x, (int)position.y, gameobjects[i].molecules[j].color);
			}
			gameobjects[i].rotation += fElapsedTime;
			gameobjects[i].pos += gameobjects[i].vel * fElapsedTime;
			gameobjects[i].vel += glm::vec2(0, 9.81f) * fElapsedTime;
		}
		
		return true;
	}
};


int main()
{
	FCHEngine2D app;
	if (app.Construct(640, 360, 3, 3))
		app.Start();

	return 0;
}
