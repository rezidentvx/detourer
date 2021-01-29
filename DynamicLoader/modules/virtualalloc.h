#pragma once
#include <iostream>
#include <fstream>

#include <detoursstack.h>
#include <memoryprotections.h>
#include <util.h>
#include <detourermodule.h>

extern LPVOID(WINAPI* Real_VirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD);

LPVOID WINAPI HookedVirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);