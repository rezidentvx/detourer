#include "main.h"

// Note: Wrapping these Detourer functions in TRY() breaks things at runtime.
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason) {
        case DLL_PROCESS_ATTACH:
        {
            OUT_DEBUG(L"Loading...", L"Main INFO");
            Detourer::NewTransaction();
            Detourer::AttachAll();
            Detourer::Commit();
            OUT_DEBUG(L"Successfully loaded.", L"Main SUCCESS");
            break;
        }
        case DLL_PROCESS_DETACH:
        {
            OUT_DEBUG(L"Unloading...", L"Main INFO");
            Detourer::NewTransaction();
            Detourer::DetachAll();
            Detourer::Commit();
            OUT_DEBUG(L"Successfully unloaded.", L"Main SUCCESS");
            break;
        }
    }
    return true;
}