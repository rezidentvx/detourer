#pragma once
#include <vector>
#include <detoursstack.h>
#include <util.h>

namespace Detourer {

	class Module {
	public:
		template <typename T>
		Module(T*& realFunc, void* hookedFunc) { 
			Module(&(PVOID&) realFunc, hookedFunc);
		}
		Module(void** realFunc, void* hookedFunc);

		void** _realFunc;
		void* _hookedFunc;
	};

	static void AddModule(Module m);

	extern std::vector<Module> loadedModules;
}