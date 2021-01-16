#pragma once
#include <Windows.h>
//#include <ntdef.h> // Included in Windows.h. Will cause redefinition issues
#include <bcrypt.h> // Included in Windows.h
#include <vector>
#include <fstream>

#include "detoursstack.h"

// Address of the real BCryptEncrypt
extern NTSTATUS(WINAPI* Real_BCryptEncrypt)(BCRYPT_KEY_HANDLE, PUCHAR, ULONG, VOID*, PUCHAR, ULONG, PUCHAR, ULONG, ULONG*, ULONG);

NTSTATUS WINAPI HookedBCryptEncrypt(BCRYPT_KEY_HANDLE hKey, PUCHAR pbInput, ULONG cbInput, VOID* pPaddingInfo, PUCHAR pbIV, ULONG cbIV, PUCHAR pbOutput, ULONG cbOutput, ULONG* pcbResult, ULONG dwFlags);

inline BOOL AttachBCryptEncrypt() {
    return DetourAttach(&(PVOID&)Real_BCryptEncrypt, HookedBCryptEncrypt);
}

inline BOOL DetachBCryptEncrypt() {
    return DetourDetach(&(PVOID&)Real_BCryptEncrypt, HookedBCryptEncrypt);
}