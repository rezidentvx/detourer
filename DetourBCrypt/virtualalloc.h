#pragma once
#include <iostream>
#include <fstream>

#include "detoursstack.h"
#include "memoryprotections.h"
#include "util.h"

// Address of the real VirtualAlloc
extern LPVOID(WINAPI* Real_VirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD);

LPVOID WINAPI HookedVirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);

inline BOOL AttachVirtualAlloc() {
    return DetourAttach(&(PVOID&)Real_VirtualAlloc, HookedVirtualAlloc);
}

inline BOOL DetachVirtualAlloc() {
    return DetourDetach(&(PVOID&)Real_VirtualAlloc, HookedVirtualAlloc);
}