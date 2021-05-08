#define DTR_WRITEFILE

#include <detourer.h>

extern auto Real_WriteFile = WriteFile;

#include <modules\wrappers\build\exfil-file.h>

BOOL WINAPI HookedWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped) {
    const char* outfile = "writefile";
    char path[MAX_PATH];
    if (GetFinalPathNameByHandleA(hFile, path, MAX_PATH, VOLUME_NAME_DOS) < MAX_PATH 
        && !DTR_DEFAULT_OUTDIR.compare(0, DTR_DEFAULT_OUTDIR.length(), path)) {
        
        Exfil::ToFile("\n[+] Intercepted attempted write (" + std::string(path) + "). Data:\n", outfile);
        Exfil::ToFile(lpBuffer, nNumberOfBytesToWrite, outfile);
    }
    return Real_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

static const Detourer::Module m(Real_WriteFile, HookedWriteFile);