#pragma once
#include <vector>
#include <detoursstack.h>
#include <util.h>

namespace Detourer {

	class Module {
	public:
		void** _realFunc;
		void* _hookedFunc;

		inline Module(void** realFunc, void* hookedFunc);

		template <typename T>
		Module(T*& realFunc, void* hookedFunc) { 
			Module(&(PVOID&) realFunc, hookedFunc);
		}
	};

	extern std::vector<Module> loadedModules;

	inline Module::Module(void** realFunc, void* hookedFunc)
		: _realFunc(realFunc),
		_hookedFunc(hookedFunc) {
		loadedModules.push_back(*this);
		DBG_MB(L"Loaded module.", L"Detourer::Module(void*,void*)");
	}

	inline void AddModule(Module m) {
		loadedModules.push_back(m);
		DBG_MB((std::wstring(L"Pushed back") + std::to_wstring((ULONG_PTR)m._hookedFunc) + std::to_wstring((ULONG_PTR)m._realFunc)).c_str(), L"Detourer::AddModule(Module)");
		DBG_MB((std::wstring(L"Modules loaded: ") + std::to_wstring(loadedModules.size())).c_str(), L"Detourer::AddModule(Module)");
	}

}