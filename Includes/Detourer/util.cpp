#include "util.h"

int TRY1(int retval, LPCTSTR operation) {
    if (retval != NO_ERROR) {
        OUT_FAIL(operation);
        TRY_ASSERT_SUCCESS();
    }
    return true;
}

void OUT_MB(LPCTSTR message, LPCTSTR header) {
    MessageBox(HWND_DESKTOP, message, header, MB_OK);
}

#ifdef _DEBUG
void OUT_DEBUG(LPCTSTR message, LPCTSTR header) {
    OUT_MB(message, header);
}

void OUT_FAIL(LPCTSTR operation, LPCTSTR location) {
    std::tstring message = TEXT("Failed to ");
    message += operation;

    std::tstring header(TEXT("FAIL"));
    if (location) {
        header += TEXT(": ");
        header += location;
    }

    OUT_DEBUG(message.c_str(), header.c_str());
}
#endif

HMODULE GetModuleAtAddress(LPVOID addr) {
    /// Get list of modules in process
    std::vector<HMODULE> hModules;
    DWORD cbNeeded;
    std::array<HMODULE, 1024> hModuleArr{ 0 };
    if (!EnumProcessModulesEx(GetCurrentProcess(), hModuleArr.data(), (DWORD)hModuleArr.size() * sizeof(HMODULE), &cbNeeded, LIST_MODULES_DEFAULT)) {
        OUT_FAIL(L"EnumProcessModulesEx", L"GetModuleAtAddress");
        return NULL;
    }

    // Convert from array to vector, excluding unused slots
    // not really necessary. Could just use the array directly until cbNeeded/sizeof(HMODULE)
    for (SIZE_T i = 0; i <= cbNeeded / sizeof(HMODULE); i++)
        hModules.emplace_back(hModuleArr[i++]);

    if (hModules.empty()) {
        OUT_FAIL(L"Convert HMODULE array to vector", L"GetModuleAtAddress");
        return NULL;
    }

    /// If module is in address range
    MODULEINFO minfo{};
    for (auto& hModule : hModules) {

        GetModuleInformation(GetCurrentProcess(), hModule, std::addressof(minfo), sizeof(minfo));

        if (addr > minfo.lpBaseOfDll && (uintptr_t)addr < (uintptr_t)minfo.lpBaseOfDll + minfo.SizeOfImage)
            return hModule;
    }
    return NULL;
}

std::string GetModuleNameStr(LPVOID addr) {
    HMODULE hmod = GetModuleAtAddress(addr);
    return GetModuleNameStr(hmod);
}

std::string GetModuleNameStr(HMODULE hmod) {
    if (!hmod)
        return std::string("Unidentified module");

    CHAR moduleName[1024] = { 0 };
    if (!GetModuleFileNameA(hmod, moduleName, 1024))
        return std::string("Unidentified module");
    
    return std::string(moduleName);
}