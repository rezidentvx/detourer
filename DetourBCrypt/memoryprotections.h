#pragma once
#include <Windows.h>
#include <map>
#include <string>

namespace MemoryProtections
{
    extern const std::map<DWORD, std::string> mProtects;
    std::string FlToStr(DWORD flProtect);
}