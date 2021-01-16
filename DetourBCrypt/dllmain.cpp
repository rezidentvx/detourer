// dllmain.cpp : Defines the entry point for the DLL application.
#include "main.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason) {
        case DLL_PROCESS_ATTACH:
        {
            OUT_DEBUG(L"Loading...", L"Main INFO");
            //MessageBox(HWND_DESKTOP, L"Loading...", L"Main INFO", MB_OK);
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            Detourer::AttachAll();
            //TRY(Detourer::Init());
            //TRY(Detourer::AttachAll());
            //TRY(Detourer::Commit());
            DetourTransactionCommit();
            OUT_DEBUG(L"Successfully loaded.", L"Main SUCCESS");
            //MessageBox(HWND_DESKTOP, L"Successfully loaded.", L"Main SUCCESS", MB_OK);
            break;
        }
        case DLL_PROCESS_DETACH:
        {
            //MessageBox(HWND_DESKTOP, L"Unloading...", L"Main INFO", MB_OK);
            OUT_DEBUG(L"Unloading...", L"Main INFO");
            //TRY(Detourer::Init());
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            Detourer::DetachAll();
            //TRY(Detourer::DetachAll());
            DetourTransactionCommit();
            //TRY(Detourer::Commit());
            OUT_DEBUG(L"Successfully unloaded.", L"Main SUCCESS");
            //MessageBox(HWND_DESKTOP, L"Successfully unloaded.", L"Main SUCCESS", MB_OK);
            break;
        }
    }
    return true;
}