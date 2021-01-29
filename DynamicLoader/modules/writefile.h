/// Note, this will:
/// 1) gather a LOT of junk
/// 2) catch file writes by Detourer because they ultimately use WriteFile

#pragma once
#include <detoursstack.h>
#include <detourermodule.h>

extern BOOL(WINAPI* Real_WriteFile)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);

BOOL WINAPI HookedWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);