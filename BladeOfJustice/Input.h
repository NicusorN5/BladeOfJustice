#pragma once
#include <Windows.h>
#include "KeyMacros.h"

void PrepareInput();

extern char LastKey;

LRESULT CALLBACK InputHookFunction(const int code, const WPARAM wParam, const LPARAM lParam);
