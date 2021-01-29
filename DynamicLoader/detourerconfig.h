#pragma once

// When TRY() fails...
// Level 0: NOP (silently continue, host function shouldn't break)
// Level 1: Fail caller (return false)
// Level 2: Throw caller (throw)
#define ASSERT_SUCCESS_LEVEL 1

// Include all headers for payloads we want
#include <modules\virtualalloc.h>
#include <modules\crypto.h>
#include <modules\writefile.h>