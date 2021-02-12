#ifndef DTR_EXFILFILE
#define DTR_EXFILFILE

#include "util.h"
#include <ctime> // std::time for filename defaulting

namespace Exfil {

    inline HANDLE OpenFile(std::string filename = {}, std::string dir = {}) {
        // Get valid directory (default to path defined in detourerconfig.h if exists)
        if (dir.empty())
            dir = DTR_DEFAULT_OUTDIR;

        // Get valid filename (default to current unix time, floored to 10 mins)
        if (filename.empty())
            filename = std::to_string(std::time(nullptr) / 600);

        if (dir.empty() || filename.empty())
            return nullptr;

        std::string fullpath = dir + filename;
        DBG_MBA(fullpath.c_str());
        HANDLE hf = CreateFileA(
            fullpath.c_str(),
            FILE_APPEND_DATA,       // open for appending
            FILE_SHARE_WRITE,       // simultaneous writes
            NULL,                   // default security
            OPEN_ALWAYS,            // open if exists, else create new
            FILE_ATTRIBUTE_NORMAL,  // normal file
            NULL
        );
        DBG_MBA(hf ? "Good Handle" : "Bad Handle");
        return hf;
    }

    __forceinline bool ToFile(LPCVOID data, DWORD cbData, std::string filename = {}, std::string dir = {}) {
        HANDLE hf = OpenFile(filename, dir);
        if (hf) {
#ifdef DTR_WRITEFILE
            if (!Real_WriteFile(hf, data, cbData, nullptr, nullptr))
#else
            if (!WriteFile(hf, data, cbData, nullptr, nullptr))
#endif
                return false;
            return CloseHandle(hf);
        }
        return true;
    }

    __forceinline bool ToFile(std::string data, std::string filename = {}, std::string dir = {}) {
        return ToFile((void*)data.data(), (DWORD)data.size(), filename, dir);
    }

}
#endif