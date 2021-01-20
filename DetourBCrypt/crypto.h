#pragma once
#include <Windows.h>
//#include <ntdef.h> // Included in Windows.h. Will cause redefinition issues
#include <bcrypt.h> // Included in Windows.h
#include <ncrypt.h>
#include <wincrypt.h>
#include <vector>
#include <fstream>

#include "detoursstack.h"

extern NTSTATUS(WINAPI* Real_BCryptEncrypt)(BCRYPT_KEY_HANDLE, PUCHAR, ULONG, VOID*, PUCHAR, ULONG, PUCHAR, ULONG, ULONG*, ULONG);

NTSTATUS WINAPI HookedBCryptEncrypt(BCRYPT_KEY_HANDLE hKey, PUCHAR pbInput, ULONG cbInput, VOID* pPaddingInfo, PUCHAR pbIV, ULONG cbIV, PUCHAR pbOutput, ULONG cbOutput, ULONG* pcbResult, ULONG dwFlags);

//inline BOOL AttachBCryptEncrypt() {
//    return DetourAttach(&(PVOID&)Real_BCryptEncrypt, HookedBCryptEncrypt);
//}
//
//inline BOOL DetachBCryptEncrypt() {
//    return DetourDetach(&(PVOID&)Real_BCryptEncrypt, HookedBCryptEncrypt);
//}

extern NTSTATUS(WINAPI* Real_NCryptEncrypt)(NCRYPT_KEY_HANDLE, PBYTE, DWORD, VOID*, PBYTE, DWORD, DWORD*, DWORD);

NTSTATUS WINAPI HookedNCryptEncrypt(NCRYPT_KEY_HANDLE hKey, PBYTE pbInput, DWORD cbInput, VOID* pPaddingInfo, PBYTE pbOutput, DWORD cbOutput, DWORD* pcbResult, DWORD dwFlags);

//inline BOOL AttachNCryptEncrypt() {
//    return DetourAttach(&(PVOID&)Real_NCryptEncrypt, HookedNCryptEncrypt);
//}
//
//inline BOOL DetachNCryptEncrypt() {
//    return DetourDetach(&(PVOID&)Real_NCryptEncrypt, HookedNCryptEncrypt);
//}

extern BOOL(WINAPI* Real_CryptEncrypt)(HCRYPTKEY, HCRYPTHASH, BOOL, DWORD, BYTE*, DWORD*, DWORD);

BOOL WINAPI HookedCryptEncrypt(HCRYPTKEY hKey, HCRYPTHASH hHash, BOOL Final, DWORD dwFlags, BYTE* pbData, DWORD* pdwDataLen, DWORD dwBufLen);
//
//inline BOOL AttachCryptEncrypt() {
//    return DetourAttach(&(PVOID&)Real_CryptEncrypt, HookedCryptEncrypt);
//}
//
//inline BOOL DetachCryptEncrypt() {
//    return DetourDetach(&(PVOID&)Real_CryptEncrypt, HookedCryptEncrypt);
//}

extern BOOL(WINAPI* Real_CryptEncryptMessage)(PCRYPT_ENCRYPT_MESSAGE_PARA, DWORD, PCCERT_CONTEXT[],
    const BYTE*, DWORD, BYTE*, DWORD*);

BOOL WINAPI HookedCryptEncryptMessage(PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptPara, DWORD cRecipientCert, PCCERT_CONTEXT rgpRecipientCert[],
    const BYTE* pbToBeEncrypted, DWORD cbToBeEncrypted, BYTE* pbEncryptedBlob, DWORD* pcbEncryptedBlob);

//inline BOOL AttachCryptEncryptMessage() {
//    return DetourAttach(&(PVOID&)Real_CryptEncryptMessage, HookedCryptEncryptMessage);
//}
//
//inline BOOL DetachCryptEncryptMessage() {
//    return DetourDetach(&(PVOID&)Real_CryptEncryptMessage, HookedCryptEncryptMessage);
//}