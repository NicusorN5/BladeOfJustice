#pragma once
#include <Windows.h>

void PrepareInput();

extern DWORD LastKey;

LRESULT CALLBACK InputHookFunction(const int code, const WPARAM wParam, const LPARAM lParam);
