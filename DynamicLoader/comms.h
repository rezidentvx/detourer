#pragma once
#ifdef _DEBUG
#include <iostream>
#include <fstream>
#include <windows.h>
#include <io.h> // _open_osfhandle
#include <fcntl.h> // _O_TEXT

void RedirectIOToConsole();

#endif