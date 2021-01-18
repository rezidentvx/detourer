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
        TRYATTACH(WriteFile);
        TRYATTACH(VirtualAlloc);
        TRYATTACH(BCryptEncrypt);
        TRYATTACH(NCryptEncrypt);
        TRYATTACH(CryptEncrypt);
        TRYATTACH(CryptEncryptMessage);
        return true;
    }

    BOOL DetachAll() {
        OUT_DEBUG(L"DetachAll...", L"Detourer INFO");
        TRYDETACH(WriteFile);
        TRYDETACH(VirtualAlloc);
        TRYDETACH(BCryptEncrypt);
        TRYDETACH(NCryptEncrypt);
        TRYDETACH(CryptEncrypt);
        TRYDETACH(CryptEncryptMessage);
        return true;
    }
}