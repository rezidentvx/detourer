#include "writefile.h"
#include <sstream>

// Address of the real WriteFile
BOOL(WINAPI* Real_WriteFile)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED) = WriteFile;

// IDK, there's good code in here somewhere.
BOOL WINAPI HookedWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped)
{
    //const char* pdata = reinterpret_cast<const char*>(lpBuffer);
    ////std::string ps(pdata);
    //if (pdata && *pdata) { // If the buffer exists and isn't empty
    //    std::ofstream f("C:\\Users\\Guest User12\\Desktop\\writefile.txt", std::ios::out | std::ios::app);
    //    /*std::stringstream ss;
    //    ss << pdata;*/

    //    char c;
    //    for (SIZE_T i = 0; i < nNumberOfBytesToWrite; i++) {
    //        c = ((CHAR*)lpBuffer)[i];
    //        if (c) {
    //            f << c;
    //        }
    //    }
    //    f << reinterpret_cast<const char*>(lpBuffer) << std::endl;
    //    //f << /*ss.str()*/ ps << std::endl;
    //}

    //HANDLE hf = CreateFile(TEXT("C:\\Users\\Guest User12\\Desktop\\writefile.txt"),
    //    GENERIC_WRITE,          // open for writing
    //    FILE_SHARE_WRITE,       // simultaneous writes
    //    NULL,                   // default security
    //    OPEN_ALWAYS,            // create new file only
    //    FILE_ATTRIBUTE_NORMAL,  // normal file
    //    NULL);
    //if (hf) {
    //    DWORD dwPos = SetFilePointer(hf, 0, NULL, FILE_END);
    //    LockFile(hf, dwPos, 0, nNumberOfBytesToWrite, 0);
    //    Real_WriteFile(hf, lpBuffer, nNumberOfBytesToWrite, nullptr, nullptr);
    //    UnlockFile(hf, dwPos, 0, nNumberOfBytesToWrite, 0);
    //    CloseHandle(hf);
    //}
    //MessageBoxA(HWND_DESKTOP, ss.str().c_str(), "DetourWriteFile", MB_OK);
    return Real_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}