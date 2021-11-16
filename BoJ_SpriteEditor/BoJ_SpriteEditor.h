#pragma once
#include <Windows.h>

int __stdcall wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd);

LRESULT CALLBACK BoJ_Editor_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

void CreateDrawingControl(HINSTANCE hInstance);

LRESULT CALLBACK BoJ_Editor_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);