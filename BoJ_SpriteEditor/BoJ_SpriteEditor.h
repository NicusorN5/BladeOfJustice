#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

//enable visual styles
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int __stdcall wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd);

LRESULT CALLBACK BoJ_Editor_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

LRESULT CALLBACK BoJ_Paint_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

void SaveProjectDialog();

void SaveProject(char* path);

void RedrawEditor();