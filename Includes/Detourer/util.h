#pragma once
#include <detourerconfig.h>
#include <windows.h>
#include <Psapi.h> // GetModuleInformation
#include <libloaderapi.h> // GetModuleFileName
#include <string>
#include <vector>
#include <array>
//#include <winerror.h>
//#include <WinUser.h>

namespace std {
	#ifdef UNICODE
		typedef wstring tstring;
	#else
		typedef string tstring;
	#endif
}
// Stringizing
#define _CAT(A, B) A ## B
#define CAT(A, B) _CAT(A, B)

// Select overloaded macro
#define SELECT( NAME, NUM ) CAT( NAME ## _, NUM )
#define GET_COUNT( _1, _2, _3, _4, _5, _6, COUNT, ... ) COUNT
#define VA_SIZE( ... ) GET_COUNT( __VA_ARGS__, 6, 5, 4, 3, 2, 1 )
#define VA_SELECT( NAME, ... ) SELECT( NAME, VA_SIZE(__VA_ARGS__) )(__VA_ARGS__)

#define TRY(...) VA_SELECT(TRY, __VA_ARGS__)

// If an attempt fails...
#if ASSERT_SUCCESS_LEVEL == 2 // Generate an exception in the caller
#define TRY_ASSERT_SUCCESS(...) throw
#define TRY_1(OPERATION) TRY1(OPERATION, TEXT(#OPERATION));

#elif ASSERT_SUCCESS_LEVEL == 1 // Make the caller return false (DANGEROUS if false is a bad return value in caller) by catching a throw to return false
#define TRY_ASSERT_SUCCESS(...) throw
#define TRY_1(OPERATION) try { TRY1(OPERATION, TEXT(#OPERATION)); } catch (...) { return false; }

#else // Act like it never happened & carry on
#define TRY_ASSERT_SUCCESS(...) (void)0
#endif

int TRY1(int retval, LPCTSTR operation);
#define TRY_2(OPERATION, FUNC) TRY_1(OPERATION##FUNC()) //TRY_1(CAT(OPERATION,CAT(FUNC, STR(())))

void OUT_MB(LPCTSTR message, LPCTSTR header);

#ifdef _DEBUG
void OUT_DEBUG(LPCTSTR message, LPCTSTR header);
void OUT_FAIL(LPCTSTR operation, LPCTSTR location = TEXT(""));
#else
#define OUT_DEBUG(...) (void)0
#define OUT_FAIL(...) (void)0
#endif

// Somewhere in this stack, Debug builds are unable to resolve the module name from pointer
HMODULE GetModuleAtAddress(LPVOID addr);
std::string GetModuleNameStr(LPVOID addr);
std::string GetModuleNameStr(HMODULE hmod);