#ifndef DTR_VIRTUALALLOC
#define DTR_VIRTUALALLOC

#include <memoryprotections.h>
#include <detourermodule.h>

extern auto Real_VirtualAlloc = VirtualAlloc;

#include <modules\wrappers\build\exfil-file.h>

LPVOID WINAPI HookedVirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect) {
    LPVOID addr = nullptr;
    try {
        // [+] Accessed HookedVirtualAlloc @ 00007FFFF7304520 (detourer.dll)
        auto ptrStr = (char*)malloc(sizeof(LPVOID));
        if (ptrStr) { sprintf(ptrStr, "%p", &HookedVirtualAlloc); }
        std::string s = "[+] Accessed HookedVirtualAlloc @ ";
        if (ptrStr) { s += ptrStr; }
        s += " (" + GetModuleNameStr(&HookedVirtualAlloc) + ")\n";
        
        // [*] backTrace[1 /20]: 00007FFF96FD9CBD (C:\Program Files\<target>\module32.dll)
        LPVOID backTrace[100] = { nullptr };
        WORD cBackTrace = RtlCaptureStackBackTrace(0, 100, backTrace, NULL);
        for (USHORT i = 0; i < cBackTrace && backTrace[i] != nullptr; i++) {
            sprintf(ptrStr, "%p", backTrace[i]);
            s += "\t[*] backTrace[" + std::to_string(i) + (i < 10 ? " /" : "/") + std::to_string(cBackTrace - 1) + "]:  "
              + ptrStr + " (" + GetModuleNameStr(backTrace[i]) + ")\n";
        }

        s += "\t[+] Intercepted alloc of " + std::to_string(dwSize) + " B (" + std::to_string(dwSize / 1024) + " KB) of "
          + MemoryProtections::FlToStr(flProtect)
          + " at (offset) " 
          + (lpAddress ? sprintf(ptrStr, "%p", lpAddress), ptrStr : "(Any)") + "\n";

        // Modify and forward original call
        flProtect |= PAGE_EXECUTE_READWRITE;
        addr = Real_VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
        if (!ptrStr)
            return addr;

        // This line crashes the host, but only on about 30% of calls.
        // Is it sprintf? Is addr or ptrStr invalid?
        sprintf(ptrStr, "%p", (void*)addr);
        s += "\t[+] Allocated RWX at (offset) ";
        s += ptrStr;
        s += " (" + GetModuleNameStr(addr) + ")\n";

        Exfil::ToFile(s, "virtualalloc");
    } catch (...) {}
    return addr;
}

namespace { Detourer::Module m(Real_VirtualAlloc, HookedVirtualAlloc); }

#endif