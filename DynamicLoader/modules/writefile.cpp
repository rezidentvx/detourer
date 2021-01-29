#include "writefile.h"

BOOL(WINAPI* Real_WriteFile)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED) = WriteFile;

BOOL WINAPI HookedWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
    HANDLE hf = CreateFile(
        TEXT("C:\\Users\\Guest User12\\Desktop\\writefile.txt"),
        FILE_APPEND_DATA,       // open for appending
        FILE_SHARE_WRITE,       // simultaneous writes
        NULL,                   // default security
        OPEN_ALWAYS,            // open if exists, else create new
        FILE_ATTRIBUTE_NORMAL,  // normal file
        NULL
    );
    if (hf) {
        auto s = "\n[+] Intercepted attempted write. Data:\n";
        Real_WriteFile(hf, s, static_cast<DWORD>(strlen(s)), nullptr, nullptr);
        Real_WriteFile(hf, lpBuffer, nNumberOfBytesToWrite, nullptr, nullptr);
        CloseHandle(hf);
    }
    
    return Real_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

namespace { Detourer::Module m(Real_WriteFile, HookedWriteFile); }