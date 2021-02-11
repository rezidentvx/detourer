/// Note, this will:
/// 1) gather a LOT of junk
/// 2) catch file writes by Detourer because they ultimately use WriteFile

#ifndef DTR_WRITEFILE
#define DTR_WRITEFILE

#include <detourermodule.h>

extern auto Real_WriteFile = WriteFile;

#include <modules\wrappers\build\exfil-file.h>

BOOL WINAPI HookedWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped) {

    char path[MAX_PATH];
    std::string s;
    if(GetFinalPathNameByHandleA(hFile, path, MAX_PATH, VOLUME_NAME_NT) < MAX_PATH)
        s += path;

    Exfil::ToFile("\n[+] Intercepted attempted write (" + s + "). Data:\n", "writefile");
    Exfil::ToFile(lpBuffer, nNumberOfBytesToWrite, "writefile");
    return Real_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

namespace { const Detourer::Module m(Real_WriteFile, HookedWriteFile); }
#endif