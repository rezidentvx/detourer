#include "bcryptencrypt.h"

// Address of the real BCryptEncrypt
NTSTATUS(WINAPI* Real_BCryptEncrypt)(BCRYPT_KEY_HANDLE, PUCHAR, ULONG, VOID*, PUCHAR, ULONG, PUCHAR, ULONG, ULONG*, ULONG) = BCryptEncrypt;

NTSTATUS WINAPI HookedBCryptEncrypt(BCRYPT_KEY_HANDLE hKey, PUCHAR pbInput, ULONG cbInput, VOID* pPaddingInfo, PUCHAR pbIV, ULONG cbIV, PUCHAR pbOutput, ULONG cbOutput, ULONG* pcbResult, ULONG dwFlags) {
    std::vector<BYTE> input(pbInput, pbInput + cbInput);
    input.push_back('\0');
    std::vector<BYTE> iv(pbIV, pbIV + cbIV);
    iv.push_back('\0');

    //std::stringstream ss;
    std::ofstream f("C:\\Users\\Guest User12\\Desktop\\bcryptencrypt.txt", std::ios::out | std::ios::app);
    /*ss*/f << "[+] Intercepted encrypt of " << input.data() << " with key " << hKey << ", IV " << iv.data() << std::endl;
    //MessageBoxA(HWND_DESKTOP, ss.str().c_str(), "DetourVirtualAlloc", MB_OK);
    f.close();
    return Real_BCryptEncrypt(hKey, pbInput, cbInput, pPaddingInfo, pbIV, cbIV, pbOutput, cbOutput, pcbResult, dwFlags);
}