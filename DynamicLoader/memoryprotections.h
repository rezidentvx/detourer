#pragma once
#include <Windows.h>
#include <map>
#include <string>

namespace MemoryProtections
{
    const std::map<const DWORD, const char*> mProtects = {
        {0x1, "PAGE_NOACCESS"},
        {0x2, "PAGE_READONLY"},
        {0x4, "PAGE_READWRITE"},
        {0x8, "PAGE_WRITECOPY"},
        {0x10, "PAGE_EXECUTE"},
        {0x20, "PAGE_EXECUTE_READ"},
        {0x40, "PAGE_EXECUTE_READWRITE"},
        {0x80, "PAGE_EXECUTE_WRITECOPY"},
        {0x100, "PAGE_GUARD"},
        {0x200, "PAGE_NOCACHE"},
        {0x400, "PAGE_WRITECOMBINE"},
        {0x40000000, "PAGE_TARGETS_NO_UPDATE"}
    };
    inline std::string FlToStr(DWORD flProtect) {
        std::string flags;
        for (std::pair<DWORD, std::string> prot : mProtects) {
            if (flProtect & prot.first)
                flags += (flags.empty() ? "" : " | ") + prot.second;
        }
        return flags;
    }
}