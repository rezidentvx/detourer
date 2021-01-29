#pragma once
#include <Windows.h>
//#include <ntdef.h> // Included in Windows.h. Will cause redefinition issues
#include <bcrypt.h> // Included in Windows.h
#include <ncrypt.h>
#include <wincrypt.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

#include <detoursstack.h>
#include <detourermodule.h>

#pragma comment(lib,"bcrypt.lib")
#pragma comment(lib,"ncrypt.lib")
#pragma comment(lib,"crypt32.lib")

extern NTSTATUS(WINAPI* Real_BCryptEncrypt)(BCRYPT_KEY_HANDLE, PUCHAR, ULONG, VOID*, PUCHAR, ULONG, PUCHAR, ULONG, ULONG*, ULONG);

NTSTATUS WINAPI HookedBCryptEncrypt(BCRYPT_KEY_HANDLE hKey, PUCHAR pbInput, ULONG cbInput, VOID* pPaddingInfo, PUCHAR pbIV, ULONG cbIV, PUCHAR pbOutput, ULONG cbOutput, ULONG* pcbResult, ULONG dwFlags);

extern NTSTATUS(WINAPI* Real_NCryptEncrypt)(NCRYPT_KEY_HANDLE, PBYTE, DWORD, VOID*, PBYTE, DWORD, DWORD*, DWORD);

NTSTATUS WINAPI HookedNCryptEncrypt(NCRYPT_KEY_HANDLE hKey, PBYTE pbInput, DWORD cbInput, VOID* pPaddingInfo, PBYTE pbOutput, DWORD cbOutput, DWORD* pcbResult, DWORD dwFlags);

extern BOOL(WINAPI* Real_CryptEncrypt)(HCRYPTKEY, HCRYPTHASH, BOOL, DWORD, BYTE*, DWORD*, DWORD);

BOOL WINAPI HookedCryptEncrypt(HCRYPTKEY hKey, HCRYPTHASH hHash, BOOL Final, DWORD dwFlags, BYTE* pbData, DWORD* pdwDataLen, DWORD dwBufLen);

extern BOOL(WINAPI* Real_CryptEncryptMessage)(PCRYPT_ENCRYPT_MESSAGE_PARA, DWORD, PCCERT_CONTEXT[],
    const BYTE*, DWORD, BYTE*, DWORD*);

BOOL WINAPI HookedCryptEncryptMessage(PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptPara, DWORD cRecipientCert, PCCERT_CONTEXT rgpRecipientCert[],
    const BYTE* pbToBeEncrypted, DWORD cbToBeEncrypted, BYTE* pbEncryptedBlob, DWORD* pcbEncryptedBlob);