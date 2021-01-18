#include "virtualalloc.h"

// Address of the real VirtualAlloc
LPVOID(WINAPI* Real_VirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD) = VirtualAlloc;

// TODO: This fails to identify the most immediate calling module now. IDK when this broke
// TODO: This gets the offset from the calling function, but currently does not know the address of the caller.
//          Need to derive from that trace info
LPVOID WINAPI HookedVirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect) {

    // Modify and forward original call
    LPVOID addr = Real_VirtualAlloc(lpAddress, dwSize, flAllocationType, PAGE_EXECUTE_READWRITE);

    // Open file to export to
    std::ofstream fs("C:\\Users\\Guest User12\\Desktop\\valloc.txt", std::ios::out | std::ios::app);
    if (!fs.is_open()) {
        OUT_FAIL(L"open ofstream", L"HookedVirtualAlloc");
        return addr;
    }
    
    // [+] Accessed HookedVirtualAlloc @ 00007FFFF7304520 (detourer.dll)
    std::ios_base::fmtflags fl(fs.flags());
    fs << "[+] Accessed HookedVirtualAlloc @ " << std::hex << std::uppercase << &HookedVirtualAlloc;
    fs.flags(fl);
    fs << " (" << GetModuleNameStr(&HookedVirtualAlloc) << ")" << '\n';

    // [*] backTrace[1 /20]: 00007FFF96FD9CBD (C:\Program Files\<target>\module32.dll)
    LPVOID backTrace[100] = { nullptr };
    WORD cBackTrace = RtlCaptureStackBackTrace(0, 100, backTrace, NULL);
    for (USHORT i = 0; i < cBackTrace && backTrace[i] != nullptr; i++) {
        fs << "\t[*] backTrace[" << i << (i < 10 ? " /" : "/") << cBackTrace - 1 << "]:  "
            << backTrace[i]
            << " (" << GetModuleNameStr(backTrace[i]) << ")"
            << '\n';
    }

    // [+] Intercepted alloc of 4096 B (4 KB) of PAGE_READWRITE at (offset) AAAABBBBCCCCDDDD
    fs << "\t[+] Intercepted alloc of " << dwSize << " B (" << dwSize / 1024 << " KB) of "
            << " at (offset) " << (lpAddress ? lpAddress : "(Any)")
            << '\n';

    // [+] Allocated RWX at (offset) AAAABBBBCCCCDDDD (module.dll)
    fs << "\t[+] Allocated RWX at (offset) " << addr 
            << " (" << GetModuleNameStr(addr) << ")"
            << '\n';

    fs << std::flush;
    return addr;
}