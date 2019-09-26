#pragma once

#include <list>
#include <string>
#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleEngineGUI.h"
#include "ModulePhysics.h"

#include "SDL\include\SDL.h"
#include "SDL\include\SDL_version.h"

struct GPU_info
{
	struct VRAM_info
	{
		int budget, usage, available;
	};

	unsigned char* vendor = nullptr;
	unsigned char* renderer = nullptr;
	unsigned char* version = nullptr;

	VRAM_info VRAM;
};

struct hardware_info  //Struct to keep data more organized and not add a lot of vars in the class
{
	SDL_version sdl_version;

	Uint8 CPU_logic_cores;
	float RAM;

	GPU_info GPU;
};

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleEngineGUI* engineGUI;
	ModulePhysics* physics;

	hardware_info hardware;
private:

	Timer	ms_timer;
	float	dt;

	std::list <Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};