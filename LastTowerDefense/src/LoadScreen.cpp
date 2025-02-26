#include "LoadScreen.h"
#include "Game.h"
#include "Graphic/GUI_Overlay.h"
#include<iostream>
#include <glm.hpp>
#include <time.h>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

bool LoadScreen::isFinish = false;
Graphic::GUI* loadGUI;

LoadScreen::LoadScreen()
{
}

LoadScreen::~LoadScreen()
{
}

void LoadScreen::Loading()
{
	Game::InitResources();
	isFinish = true;
}

void LoadScreen::Init()
{
	this->platform = Platform::GetPtr();
	this->manager = GameStateManager::GetPtr();
	
	resourceManager = ResourceManager::GetPtr();
	resourceManager->Add(ResourceType::ImageUI, "LoadingScreen");

	resourceManager->Wait();
	resourceManager->Load();

	camera = new Camera(glm::vec3(10, 10.7, 100.6f), glm::vec3(0.0f, 1.0f, 0.0f), 3.0f, 3.0f, 355.0f, 0.1f);

	shaderManager = ShaderManager::GetPtr();
	shaderManager->InitShader(camera);
	shaderManager->LoadShaders("gui");

	loadGUI = new Graphic::GUI((Graphic::IGUILayer*)resourceManager->GetElement("LoadingScreen"), camera, shaderManager);
	load = new std::thread(&LoadScreen::Loading);
}

void LoadScreen::Draw()
{
}

void LoadScreen::Update(unsigned int delta)
{
	if (load->joinable())
	{
		if (isFinish)
		{
			Game* game = new Game();
			manager->RealaseState();
			GameStateManager::GetPtr()->SetState(game);
		}
	}
}

bool LoadScreen::MouseInput(int x, int y, bool leftbutton)
{	
	return false;
}

bool LoadScreen::Input(std::map<int, bool> keys)
{	
	return false;
}

void LoadScreen::Close()
{
	delete loadGUI;
	std::cout << " Close Init" << std::endl;
}