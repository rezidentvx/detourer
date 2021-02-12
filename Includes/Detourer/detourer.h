#pragma once
//#include <detourerconfig.h>
//#include <detoursstack.h>
//#include <util.h>
#include <detourermodule.h>

namespace Detourer {

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
}