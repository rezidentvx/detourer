#ifndef DTR_CRYPTO
#define DTR_CRYPTO

#define DTR_BCRYPTENCRYPT

#include <detourermodule.h>
//  #include <Windows.h>
//    #include <bcrypt.h>
//    #include <ncrypt.h>
//    #include <wincrypt.h>

#pragma comment(lib,"bcrypt.lib")

extern auto Real_BCryptEncrypt = BCryptEncrypt;

#include <modules\wrappers\build\exfil-file.h>

NTSTATUS WINAPI HookedBCryptEncrypt(BCRYPT_KEY_HANDLE hKey, PUCHAR pbInput, ULONG cbInput, VOID* pPaddingInfo, PUCHAR pbIV, ULONG cbIV, PUCHAR pbOutput, ULONG cbOutput, ULONG* pcbResult, ULONG dwFlags) {
    // Get key blob size
    ULONG cbBlob;
    BCryptExportKey(hKey, NULL, BCRYPT_KEY_DATA_BLOB, nullptr, NULL, &cbBlob, NULL);

    // Get key blob
    BYTE* pbBlob = (BYTE*)malloc(cbBlob);
    ULONG cbCopied;
    BCryptExportKey(hKey, NULL, BCRYPT_KEY_DATA_BLOB, pbBlob, cbBlob, &cbCopied, NULL);

    // Extract key
    auto cbKey = ((BCRYPT_KEY_DATA_BLOB_HEADER*)pbBlob)->cbKeyData;
    BYTE* pbKey = (BYTE*)memcpy(malloc(cbKey), pbBlob + sizeof(BCRYPT_KEY_DATA_BLOB_HEADER), cbKey);

    std::string s = "[+] Intercepted encrypt of: ";
    s += "\n\t[*] Data (" + std::to_string(cbInput) + "B): 0x" + ToHexStr(pbInput, cbInput) + 
         "\n\t[*] Key  (" + std::to_string(cbKey)   + "B): 0x" + ToHexStr(pbKey, cbKey)     + 
         "\n\t[*] IV   (" + std::to_string(cbIV)    + "B): 0x" + ToHexStr(pbIV, cbIV)       + 
         "\n";

    Exfil::ToFile(s, "bcryptencrypt");

    return Real_BCryptEncrypt(hKey, pbInput, cbInput, pPaddingInfo, pbIV, cbIV, pbOutput, cbOutput, pcbResult, dwFlags);
}

namespace { Detourer::Module m(Real_BCryptEncrypt, HookedBCryptEncrypt); }

// Currently not implemented
//#pragma comment(lib,"ncrypt.lib")
//
//extern NTSTATUS(WINAPI* Real_NCryptEncrypt)(NCRYPT_KEY_HANDLE, PBYTE, DWORD, VOID*, PBYTE, DWORD, DWORD*, DWORD) = NCryptEncrypt;
//
//NTSTATUS WINAPI HookedNCryptEncrypt(NCRYPT_KEY_HANDLE hKey, PBYTE pbInput, DWORD cbInput, VOID* pPaddingInfo, PBYTE pbOutput, DWORD cbOutput, DWORD* pcbResult, DWORD dwFlags);
//
//namespace { Detourer::Module m(Real_NCryptEncrypt, HookedNCryptEncrypt); }
//
//#pragma comment(lib,"crypt32.lib")
//
//extern BOOL(WINAPI* Real_CryptEncrypt)(HCRYPTKEY, HCRYPTHASH, BOOL, DWORD, BYTE*, DWORD*, DWORD) = CryptEncrypt;
//
//BOOL WINAPI HookedCryptEncrypt(HCRYPTKEY hKey, HCRYPTHASH hHash, BOOL Final, DWORD dwFlags, BYTE* pbData, DWORD* pdwDataLen, DWORD dwBufLen);
//
//namespace { Detourer::Module m(Real_CryptEncrypt, HookedCryptEncrypt); }
//
//extern BOOL(WINAPI* Real_CryptEncryptMessage)(PCRYPT_ENCRYPT_MESSAGE_PARA, DWORD, PCCERT_CONTEXT[],
//    const BYTE*, DWORD, BYTE*, DWORD*) = CryptEncryptMessage;
//
//BOOL WINAPI HookedCryptEncryptMessage(PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptPara, DWORD cRecipientCert, PCCERT_CONTEXT rgpRecipientCert[],
//    const BYTE* pbToBeEncrypted, DWORD cbToBeEncrypted, BYTE* pbEncryptedBlob, DWORD* pcbEncryptedBlob);
//
//namespace { Detourer::Module m(Real_CryptEncryptMessage, HookedCryptEncryptMessage); }
#endif