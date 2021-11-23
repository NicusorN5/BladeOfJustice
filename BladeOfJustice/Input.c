#include "Input.h"

HHOOK keyboardHook;

DWORD LastKey;

void PrepareInput()
{
	keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, InputHookFunction, NULL, 0);
	if (keyboardHook == NULL)
	{
		MessageBoxA(NULL, "Failed to create keyboard hook!", "Fail", MB_ICONERROR | MB_OK);
	}
}

LRESULT CALLBACK InputHookFunction(const int code, const WPARAM wParam, const LPARAM lParam)
{
	switch (wParam)
	{
		case WM_KEYDOWN:
		{
			KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
			DWORD wVirtKey = kbdStruct->vkCode;
			DWORD wScanCode = kbdStruct->scanCode;

			BYTE lpKeyState[256];
			if (GetKeyboardState(lpKeyState))
			{
				if(LastKey != wVirtKey)
					LastKey = wVirtKey;
			}
			break;
		}
	}
	return CallNextHookEx(keyboardHook, code, wParam, lParam);
}