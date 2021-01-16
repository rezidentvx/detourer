#include "virtualalloc.h"
#include <sstream>

// Address of the real VirtualAlloc
LPVOID(WINAPI* Real_VirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD) = VirtualAlloc;

LPVOID WINAPI HookedVirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect) {

    LPVOID addr = Real_VirtualAlloc(lpAddress, dwSize, flAllocationType, PAGE_EXECUTE_READWRITE);

    std::ofstream fs("C:\\Users\\Guest User12\\Desktop\\valloc.txt", std::ios::out | std::ios::app);
    if (!fs.is_open()) {
        OUT_FAIL(L"open ofstream", L"HookedVirtualAlloc");
        return addr;
    }

    /*CONTEXT cxt;
    RtlCaptureContext(&cxt);  */
    
    std::ios_base::fmtflags fl(fs.flags());
    fs << "[+] Accessed HookedVirtualAlloc @ " /*<< std::flush*/ << std::hex << std::uppercase << &HookedVirtualAlloc/* << std::flush*/;
    fs.flags(fl);
    fs << " (" << GetModuleNameStr(&HookedVirtualAlloc) << ")" << std::endl;

    LPVOID backTrace[100] = { nullptr };
    WORD cBackTrace = RtlCaptureStackBackTrace(0, 100, backTrace, NULL);
    for (USHORT i = 0; i < cBackTrace && backTrace[i] != nullptr; i++) {
        fs << "\t[*] backTrace[" << i << (i < 10 ? " /" : "/") << cBackTrace-1 << "]:  "/* << std::flush */
               << backTrace[i]/* << std::flush*/
               << " (" << GetModuleNameStr(backTrace[i]) << ")" //<< '\n';
               << std::endl;
    }
    fs << "\t[+] Intercepted alloc of " << dwSize << " B (" << dwSize/1024 << " KB) of " 
           << MemoryProtections::FlToStr(flProtect)
           << " at (offset) " << (lpAddress ? lpAddress : "(Any)") 
           << std::endl

       << "\t[+] Allocated RWX at (offset) " << addr 
           << " (" << GetModuleNameStr(addr) << ")"
           << std::endl;

    return addr;
}