#include "detourermodule.h"

std::vector<Detourer::Module> Detourer::loadedModules{};

void Detourer::AddModule(Module m) {
	loadedModules.push_back(m);
}

Detourer::Module::Module(void** realFunc, void* hookedFunc)
	: _realFunc(realFunc),
	_hookedFunc(hookedFunc)
{
	loadedModules.push_back(*this);
	OUT_DEBUG(L"Loaded module.", L"Detourer::Module(void*,void*)");
}