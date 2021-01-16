#pragma once

// When TRY() fails...
// Level 0: NOP
// Level 1: Fail caller (return false)
// Level 2: Throw caller (throw)
#define ASSERT_SUCCESS_LEVEL 2