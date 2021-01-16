#include "detourer.h"

namespace Detourer {
    BOOL Init() {
        OUT_DEBUG(L"Init...", L"Detourer INFO");
        TRY(DetourTransactionBegin());
        TRY(DetourUpdateThread(GetCurrentThread()));
        return true;
    }

    BOOL Commit() {
        OUT_DEBUG(L"Commit...", L"Detourer INFO");
        TRY(DetourTransactionCommit());
        return true;
    }

    BOOL AttachAll() {
        OUT_DEBUG(L"AttachAll...", L"Detourer INFO");
        DetourAttach(&(PVOID&)Real_WriteFile, HookedWriteFile);
        DetourAttach(&(PVOID&)Real_VirtualAlloc, HookedVirtualAlloc);
        //DetourAttach(&(PVOID&)Real_BCryptEncrypt, HookedBCryptEncrypt);
        //TRYATTACH(WriteFile);
        //TRYATTACH(VirtualAlloc);
        //TRYATTACH(BCryptEncrypt);
        return true;
    }

    BOOL DetachAll() {
        OUT_DEBUG(L"DetachAll...", L"Detourer INFO");
        DetourDetach(&(PVOID&)Real_WriteFile, HookedWriteFile);
        DetourDetach(&(PVOID&)Real_VirtualAlloc, HookedVirtualAlloc);
        //DetourDetach(&(PVOID&)Real_BCryptEncrypt, HookedBCryptEncrypt);
        /*TRYDETACH(WriteFile);
        TRYDETACH(VirtualAlloc);
        TRYDETACH(BCryptEncrypt);*/
        return true;
    }
}