#define DTR_VIRTUALALLOC

#ifdef _DEBUG
#include <memoryprotections.h>
#endif
#include <detourer.h>

extern auto Real_VirtualAlloc = VirtualAlloc;

#include <modules\wrappers\build\exfil-file.h>

LPVOID WINAPI HookedVirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect) {
    // [+] Accessed HookedVirtualAlloc @ 00007FFFF7304520 (detourer.dll)
    auto ptrStr = (char*)malloc(sizeof(LPVOID) + 1);
    if (ptrStr)
        sprintf(ptrStr, "%p", &HookedVirtualAlloc);
    std::string s = "[+] Accessed HookedVirtualAlloc @ ";
    if (ptrStr)
        s += ptrStr;
    s += " (" + GetModuleNameStr(&HookedVirtualAlloc) + ")\n";

    // [*] backTrace[1 /20]: 00007FFF96FD9CBD (C:\Program Files\<target>\module32.dll)
    LPVOID backTrace[100] = { nullptr };
    WORD cBackTrace = RtlCaptureStackBackTrace(0, 100, backTrace, NULL);
    for (USHORT i = 0; i < cBackTrace && backTrace[i] != nullptr; i++) {
        sprintf(ptrStr, "%p", backTrace[i]);
        s += "\t[*] backTrace[" + std::to_string(i) + (i < 10 ? " /" : "/") + std::to_string(cBackTrace - 1) + "]:  "
            + ptrStr + " (" + GetModuleNameStr(backTrace[i]) + ")\n";
    }

    // [+] Intercepted alloc of 4096 B (4 KB) of PAGE_READWRITE at(offset) 000001D5728E3000
    s += "\t[+] Intercepted alloc of " + std::to_string(dwSize) + " B (";
    s += std::to_string(dwSize / 1024) + " KB) of "
#ifdef _DEBUG
        + MemoryProtections::FlToStr(flProtect)
#else
        + std::to_string((ULONGLONG) flProtect)
#endif
        + " at (offset) ";
    if (ptrStr)
        s += (lpAddress ? sprintf(ptrStr, "%p", lpAddress), ptrStr : "(Any)");
    s += "\n";

    LPVOID addr = Real_VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
    if (!ptrStr)
        return addr;
    sprintf(ptrStr, "%p", (void*)addr);

    // [+] Allocated at(offset) 000001D5728E3000(Unidentified module)
    s += "\t[+] Allocated at (offset) ";
    s += ptrStr;
    s += " (" + GetModuleNameStr(addr) + ")\n";

    Exfil::ToFile(s, "virtualalloc");
    return addr;
}

static const Detourer::Module m(Real_VirtualAlloc, HookedVirtualAlloc); 