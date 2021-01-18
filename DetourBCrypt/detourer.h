#pragma once
#include "detourerconfig.h"
#include "detoursstack.h"
#include "util.h"

#include "virtualalloc.h"
#include "crypto.h"
#include "writefile.h"

#define TRYATTACH(FUNC) TRY(ATTACH(FUNC))
#define TRYDETACH(FUNC) TRY(DETACH(FUNC))
#define ATTACH(FUNC) DetourAttach(&(PVOID&)Real_##FUNC, Hooked##FUNC)
#define DETACH(FUNC) DetourDetach(&(PVOID&)Real_##FUNC, Hooked##FUNC)

namespace Detourer {
    BOOL Init();
    BOOL Commit();
    BOOL AttachAll();
    BOOL DetachAll();
}