#include "detourer.h"

namespace Detourer {
    BOOL NewTransaction() {
        OUT_DEBUG(L"NewTransaction()...", L"Detourer INFO");
        TRY(DetourTransactionBegin());
        TRY(DetourUpdateThread(GetCurrentThread()));
        return true;
    }

    BOOL Commit() {
        OUT_DEBUG(L"Commit()...", L"Detourer INFO");
        TRY(DetourTransactionCommit());
        return true;
    }

    BOOL AttachAll() {
        OUT_DEBUG(L"AttachAll()...", L"Detourer INFO");
        for (auto module : loadedModules) {
            Attach(module);
        }
        return true;
    }

    BOOL Attach(Module m) {
        OUT_DEBUG(L"Attach(Module)...", L"Detourer INFO");
        Attach(m._realFunc, m._hookedFunc);
        return true;
    }

    BOOL Attach(void** realFunc, void* hookedFunc) {
        OUT_DEBUG(L"Attach(void**,void*)...", L"Detourer INFO");
        DetourAttach(realFunc, hookedFunc);
        return true;
    }

    BOOL DetachAll() {
        OUT_DEBUG(L"DetachAll()...", L"Detourer INFO");
        for (auto module : loadedModules) {
            Detach(module);
        }
        return true;
    }

    BOOL Detach(Module m) {
        OUT_DEBUG(L"Detach(Module)...", L"Detourer INFO");
        Detach(m._realFunc, m._hookedFunc);
        return true;
    }

    BOOL Detach(void** realFunc, void* hookedFunc) {
        OUT_DEBUG(L"Detach(void**,void*)...", L"Detourer INFO");
        DetourDetach(realFunc, hookedFunc);
        return true;
    }
}