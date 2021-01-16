#pragma once
#include <fstream>
#include "detoursstack.h"

// Address of the real WriteFile
extern BOOL(WINAPI* Real_WriteFile)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);

BOOL WINAPI HookedWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);

inline BOOL AttachWriteFile() {
    return DetourAttach(&(PVOID&)Real_WriteFile, HookedWriteFile);
}

inline BOOL DetachWriteFile() {
    return DetourDetach(&(PVOID&)Real_WriteFile, HookedWriteFile);
}