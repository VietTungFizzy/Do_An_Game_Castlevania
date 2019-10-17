#pragma once
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <string>
void DebugOut(const wchar_t *fmt, ...);
std::wstring stringToWString(const std::string& s);