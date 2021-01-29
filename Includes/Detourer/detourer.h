#pragma once
#include <detourerconfig.h>
#include <detoursstack.h>
#include <util.h>
#include <detourermodule.h>

namespace Detourer {
    BOOL NewTransaction();
    BOOL Commit();

    BOOL AttachAll();
    BOOL Attach(Module mod);
    BOOL Attach(void** realFunc, void* hookedFunc);

    BOOL DetachAll();
    BOOL Detach(Module mod);
    BOOL Detach(void** realFunc, void* hookedFunc);
}