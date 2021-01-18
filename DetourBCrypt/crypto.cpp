#include "crypto.h"

// Address of the real BCryptEncrypt
NTSTATUS(WINAPI* Real_BCryptEncrypt)(BCRYPT_KEY_HANDLE, PUCHAR, ULONG, VOID*, PUCHAR, ULONG, PUCHAR, ULONG, ULONG*, ULONG) = BCryptEncrypt;

NTSTATUS WINAPI HookedBCryptEncrypt(BCRYPT_KEY_HANDLE hKey, PUCHAR pbInput, ULONG cbInput, VOID* pPaddingInfo, PUCHAR pbIV, ULONG cbIV, PUCHAR pbOutput, ULONG cbOutput, ULONG* pcbResult, ULONG dwFlags) {
    MessageBoxA(HWND_DESKTOP, "Enterered BCryptEncrypt", "Detourer", MB_OK);
    std::vector<BYTE> input(pbInput, pbInput + cbInput);
    input.push_back('\0');
    std::vector<BYTE> iv(pbIV, pbIV + cbIV);
    iv.push_back('\0');

    std::ofstream f("C:\\Users\\Guest User12\\Desktop\\bcryptencrypt.txt", std::ios::out | std::ios::app);
    f << "[+] Intercepted encrypt of " << input.data() << " with key " << hKey << ", IV " << iv.data() << std::endl;
    return Real_BCryptEncrypt(hKey, pbInput, cbInput, pPaddingInfo, pbIV, cbIV, pbOutput, cbOutput, pcbResult, dwFlags);
}

NTSTATUS(WINAPI* Real_NCryptEncrypt)(NCRYPT_KEY_HANDLE, PBYTE, DWORD, VOID*, PBYTE, DWORD, DWORD*, DWORD) = NCryptEncrypt;

NTSTATUS WINAPI HookedNCryptEncrypt(NCRYPT_KEY_HANDLE hKey, PBYTE pbInput, DWORD cbInput, VOID* pPaddingInfo, PBYTE pbOutput, DWORD cbOutput, DWORD* pcbResult, DWORD dwFlags) {
    MessageBoxA(HWND_DESKTOP, "Enterered NCryptEncrypt", "Detourer", MB_OK);
    std::vector<BYTE> input(pbInput, pbInput + cbInput);
    input.push_back('\0');
    //std::vector<BYTE> key(hKey, hKey + sizeof(hKey));
    //key.push_back('\0');

    std::ofstream f("C:\\Users\\Guest User12\\Desktop\\ncryptencrypt.txt", std::ios::out | std::ios::app);
    f << "[+] Intercepted encrypt of " << input.data() << /*" with key " << hKey << ", IV " << key.data() <<*/ std::endl;
    return Real_NCryptEncrypt(hKey, pbInput, cbInput, pPaddingInfo, pbOutput, cbOutput, pcbResult, dwFlags);
}

BOOL(WINAPI* Real_CryptEncrypt)(HCRYPTKEY, HCRYPTHASH, BOOL, DWORD, BYTE*, DWORD*, DWORD) = CryptEncrypt;

BOOL WINAPI HookedCryptEncrypt(HCRYPTKEY hKey, HCRYPTHASH hHash, BOOL Final, DWORD dwFlags, BYTE* pbData, DWORD* pdwDataLen, DWORD dwBufLen) {
    MessageBoxA(HWND_DESKTOP, "Enterered CryptEncrypt", "Detourer", MB_OK);
    std::vector<BYTE> input(pbData, pbData + *pdwDataLen);
    input.push_back('\0');
    //std::vector<BYTE> key(hKey, hKey + sizeof(hKey));
    //key.push_back('\0');

    std::ofstream f("C:\\Users\\Guest User12\\Desktop\\cryptencrypt.txt", std::ios::out | std::ios::app);
    f << "[+] Intercepted encrypt of " << input.data() /*<< " with key " << hKey << ", IV " << key.data()*/ << std::endl;
    return Real_CryptEncrypt(hKey, hHash, Final, dwFlags, pbData, pdwDataLen, dwBufLen);
}

BOOL(WINAPI* Real_CryptEncryptMessage)(PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptPara, DWORD cRecipientCert, PCCERT_CONTEXT rgpRecipientCert[],
    const BYTE* pbToBeEncrypted, DWORD cbToBeEncrypted, BYTE* pbEncryptedBlob, DWORD* pcbEncryptedBlob) = CryptEncryptMessage;

BOOL WINAPI HookedCryptEncryptMessage(PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptPara, DWORD cRecipientCert, PCCERT_CONTEXT rgpRecipientCert[], 
                               const BYTE* pbToBeEncrypted, DWORD cbToBeEncrypted, BYTE* pbEncryptedBlob, DWORD* pcbEncryptedBlob) {

    MessageBoxA(HWND_DESKTOP, "Enterered CryptEncryptMessage", "Detourer", MB_OK);
    std::vector<BYTE> input(pbToBeEncrypted, pbToBeEncrypted + cbToBeEncrypted);
    input.push_back('\0');

    std::ofstream f("C:\\Users\\Guest User12\\Desktop\\cryptencryptmessage.txt", std::ios::out | std::ios::app);
    f << "[+] Intercepted encrypt of " << input.data() << /*" with key " << hKey << ", IV " << key.data() <<*/ std::endl;
    return Real_CryptEncryptMessage(pEncryptPara, cRecipientCert, rgpRecipientCert, pbToBeEncrypted, cbToBeEncrypted, pbEncryptedBlob, pcbEncryptedBlob);
}