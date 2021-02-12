#pragma once
#include <Windows.h>
#include <Detours\detver.h>
#include <Detours\detours.h>
#include <vector>
#include <util.h>

namespace Detourer {

#pragma region MODULES
    class Module {
    public:
        void** _realFunc;
        void* _hookedFunc;

        inline Module(void** realFunc, void* hookedFunc);

        template <typename T>
        Module(T*& realFunc, void* hookedFunc) {
            Module(&(PVOID&)realFunc, hookedFunc);
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

#pragma endregion

#pragma region HOOKING

    inline BOOL NewTransaction();
    inline BOOL Commit();

    inline BOOL AttachAll();
    inline BOOL Attach(Module mod);
    inline BOOL Attach(void** realFunc, void* hookedFunc);

    inline BOOL DetachAll();
    inline BOOL Detach(Module mod);
    inline BOOL Detach(void** realFunc, void* hookedFunc);

    inline BOOL NewTransaction() {
        DBG_MB(L"NewTransaction()...", L"Detourer INFO");
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        return true;
    }

    inline BOOL Commit() {
        DBG_MB(L"Commit()...", L"Detourer INFO");
        DetourTransactionCommit();
        return true;
    }

    inline BOOL AttachAll() {
        DBG_MB(L"AttachAll()...", L"Detourer INFO");
        for (Detourer::Module module : loadedModules) {
            Attach(module);
        }
        return true;
    }

    inline BOOL Attach(Module m) {
        DBG_MB(L"Attach(Module)...", L"Detourer INFO");
        Attach(m._realFunc, m._hookedFunc);
        return true;
    }

    inline BOOL Attach(void** realFunc, void* hookedFunc) {
        DBG_MB(L"Attach(void**,void*)...", L"Detourer INFO");
        DetourAttach(realFunc, hookedFunc);
        return true;
    }

    inline BOOL DetachAll() {
        DBG_MB(L"DetachAll()...", L"Detourer INFO");
        for (Detourer::Module module : loadedModules) {
            Detach(module);
        }
        return true;
    }

    inline BOOL Detach(Module m) {
        DBG_MB(L"Detach(Module)...", L"Detourer INFO");
        Detach(m._realFunc, m._hookedFunc);
        return true;
    }

    inline BOOL Detach(void** realFunc, void* hookedFunc) {
        DBG_MB(L"Detach(void**,void*)...", L"Detourer INFO");
        DetourDetach(realFunc, hookedFunc);
        return true;
    }

#pragma endregion
}