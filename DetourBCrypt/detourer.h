#pragma once
#include "detourerconfig.h"
#include "detoursstack.h"
#include "util.h"

#include "virtualalloc.h"
#include "bcryptencrypt.h"
#include "writefile.h"

#define TRYATTACH(FUNC) TRY(Attach##FUNC())
#define TRYDETACH(FUNC) TRY(Detach##FUNC())

// An attempt at making added modules (e.g., writefile.h) even more lightweight
//#define TRYATTACH(FUNC) TRY(Attach(FUNC))
//#define TRYDETACH(FUNC) TRY(Detach(FUNC))
//#define Attach(FUNC) DetourDetach(&(PVOID&)Real_##FUNC, Hooked##FUNC);
//#define Detach(FUNC) DetourDetach(&(PVOID&)Real_##FUNC, Hooked##FUNC);

namespace Detourer {
    BOOL Init();
    BOOL Commit();
    BOOL AttachAll();
    BOOL DetachAll();
}