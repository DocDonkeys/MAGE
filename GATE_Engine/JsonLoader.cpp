#include "JsonLoader.h"
#include "Globals.h"

#include "libs/SDL/include/SDL_assert.h"

#include <fstream>
#include <iomanip>

#ifdef _DEBUG
#ifdef _MMGR_MEM_LEAK
#include "libs/mmgr/mmgr.h"
#endif
#endif

bool JsonLoader::Save(json obj, const char* file) const
{
	bool ret = true;

	if (file == nullptr) {
		SDL_TriggerBreakpoint();	//CHANGE/FIX: Prompt a "Save As" UI
	}
	else {
		std::ofstream stream(file, std::ofstream::out);
		SDL_assert(stream.is_open());

		stream << std::setw(2) << obj << std::endl;
		stream.close();
	}
	
	return ret;
}

json JsonLoader::Load(const char* file) const
{
	SDL_assert(file != nullptr);	//CHANGE/FIX: Add a "File does not exist" UI error message

	json obj;
	std::ifstream stream(file, std::ifstream::in);
	SDL_assert(stream.is_open());

	try {
		obj = json::parse(stream);
	}
	catch (json::parse_error& e) {
		LOG("Parse Error while Loading File: %c", e.what());
	}

	stream.close();

	return obj;
}