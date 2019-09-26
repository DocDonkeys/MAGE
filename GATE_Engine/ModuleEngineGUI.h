#ifndef __MODULEENGINEGUI_H__
#define __MODULEENGINEGUI_H__


#include "Globals.h"
#include "Module.h"

#include "libs/imgui-1.72b/imgui.h"
#include "libs/imgui-1.72b/imgui_internal.h"

#include "libs/imgui-1.72b/examples/imgui_impl_sdl.h"
#include "libs/imgui-1.72b/examples/imgui_impl_opengl3.h"

#include "libs/glew/include/GL/glew.h"

class ModuleEngineGUI : public Module
{
public:
	ModuleEngineGUI(Application* app, bool start_enabled = true);
	~ModuleEngineGUI();

public:
	bool Init();
	bool Start();
	update_status Update(float dt);

	bool show_demo_window = true;
	bool show_another_window = false;

private:
	ImGuiIO* io = nullptr;

};

#endif // !__MODULEENGINEGUI_H__

