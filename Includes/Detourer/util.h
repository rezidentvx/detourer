#pragma once
#include <detourerconfig.h>
#include <windows.h>
#include <Psapi.h> // GetModuleInformation
#include <string>

namespace std {
#ifdef UNICODE
	typedef wstring tstring;
#else
	typedef string tstring;
#endif
}

//TRY only provides useful debugging messages when debugging
//Also avoids adding strings to the binary
#ifdef _DEBUG
#define DBGTEXT(text) TEXT(text)
#else
#define DBGTEXT(text) nullptr // TEXT("") ?
#endif

// If an attempt fails...
#if ASSERT_SUCCESS_LEVEL == 2 // throw caller
#define TRY_ASSERT_SUCCESS(...) throw // Throw if bad return value
#define TRY(OPERATION, desVal) TRY1(OPERATION, desVal, DBGTEXT(#OPERATION)) // Allow caller to throw

#elif ASSERT_SUCCESS_LEVEL == 1 // Make the caller return true (DANGEROUS if true is a bad return value in caller) by catching a throw to return true
#define TRY_ASSERT_SUCCESS(...) throw // Throw if bad return value
#define TRY(OPERATION, desVal) try { TRY1(OPERATION, desVal, DBGTEXT(#OPERATION)); } catch (...) { return true; } // Caller returns true, can't throw

#else // Act like it never happened & let caller handle it
#define TRY_ASSERT_SUCCESS(...) return true // Return that there was an error (true)
#define TRY(OPERATION, desVal) try { TRY1(OPERATION, desVal, DBGTEXT(#OPERATION)); } catch (...) {} // Caller carries on, can't throw
#endif

#ifdef _DEBUG

__forceinline void DBG_MBA(LPCSTR message = "", LPCSTR header = "") {
	MessageBoxA(HWND_DESKTOP, message, header, MB_OK);
}

__forceinline void DBG_MB(LPCTSTR message = TEXT(""), LPCTSTR header = TEXT("")) {
	MessageBox(HWND_DESKTOP, message, header, MB_OK);
}

__forceinline void DBG_FAIL(LPCTSTR operation = TEXT(""), LPCTSTR location = TEXT("")) {
	std::tstring message = std::tstring(TEXT("Failed to ")) + std::tstring(operation);
	std::tstring header(TEXT("FAIL"));
	if (location)
		header += std::tstring(TEXT(": ")) + std::tstring(location);

	DBG_MB(message.c_str(), header.c_str());
}
#else
#define DBG_MBA(...) (void)0
#define DBG_MB(...) (void)0
#define DBG_FAIL(...) (void)0
#endif

template<typename T>
__forceinline bool TRY1(T retVal, T desVal, LPCTSTR operation = DBGTEXT("")) {
	if (retVal != desVal) {
		DBG_FAIL(operation);
		TRY_ASSERT_SUCCESS();
	}
	return false;
}

inline std::string ToHexStr(LPBYTE pData, size_t cbData) {
	char* buf = new char[cbData * 2 + 1];
	char* ptr = &buf[0];
	for (UINT i = 0; i < cbData; i++) {
		ptr += sprintf(ptr, "%02X", pData[i]);
	}
	return buf;
}

inline HMODULE GetModuleAtAddress(LPVOID addr) {
    /// Get list of modules in process
    DWORD cbNeeded;
    HMODULE hModuleArr[1024];
    if (!EnumProcessModulesEx(GetCurrentProcess(), hModuleArr, 1024UL * sizeof(HMODULE), &cbNeeded, LIST_MODULES_DEFAULT)) {
        DBG_FAIL(L"EnumProcessModulesEx", L"GetModuleAtAddress");
        return NULL;
    }

    HMODULE hModule;
    MODULEINFO minfo;
    for (SIZE_T i = 0; i <= cbNeeded / sizeof(HMODULE); i++) {
        hModule = hModuleArr[i];

        GetModuleInformation(GetCurrentProcess(), hModule, std::addressof(minfo), sizeof(minfo));

        if (addr > minfo.lpBaseOfDll && (uintptr_t)addr < (uintptr_t)minfo.lpBaseOfDll + minfo.SizeOfImage)
            return hModule;
    }
    return NULL;
}

inline std::string GetModuleNameStr(HMODULE hmod) {
    char moduleName[1024];
    if (!hmod || !GetModuleFileNameA(hmod, moduleName, 1024))
        return "Unidentified module";

    return moduleName;
}

inline std::string GetModuleNameStr(LPVOID addr) {
    HMODULE hmod = GetModuleAtAddress(addr);
    return GetModuleNameStr(hmod);
}