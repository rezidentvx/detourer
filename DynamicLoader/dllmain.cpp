#include "main.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason) {
        case DLL_PROCESS_ATTACH:
        {
            DBG_MB(L"Loading...", L"Main INFO");
            Detourer::NewTransaction();
            Detourer::AttachAll();
            Detourer::Commit();
            DBG_MB(L"Successfully loaded.", L"Main SUCCESS");
            break;
        }
        case DLL_PROCESS_DETACH:
        {
            DBG_MB(L"Unloading...", L"Main INFO");
            Detourer::NewTransaction();
            Detourer::DetachAll();
            Detourer::Commit();
            DBG_MB(L"Successfully unloaded.", L"Main SUCCESS");
            break;
        }
    }
    return true;
}