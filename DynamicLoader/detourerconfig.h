#pragma once
#include <string>
// When TRY() fails...
// Level 0: NOP (silently continue, host function shouldn't break)
// Level 1: Fail caller (return false)
// Level 2: Throw caller (throw)
#define ASSERT_SUCCESS_LEVEL 1

// Output files to the desktop -- probably undesirable in the field
const static std::string DTR_DEFAULT_OUTDIR = std::string(getenv("USERPROFILE")) + "\\Desktop\\";