#include "BoJ_SpriteEditor.h"

HWND ColorButtons[16];

HBRUSH ColorBrushes[17];

COLORREF ColorPallete[17];

char PixelsColor[64][64];

int __stdcall wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR lpCmdLine,_In_ int nShowCmd)
{
	//Main window
	HWND EditorWindow = NULL;

	WNDCLASSA mainwindowclass;
	memset(&mainwindowclass, 0, sizeof(WNDCLASSA));

	mainwindowclass.hInstance = hInstance;
	mainwindowclass.lpszClassName = "BOJ_SPRITE_EDITOR";
	mainwindowclass.lpfnWndProc = BoJ_Editor_WndProc;
	
	RegisterClassA(&mainwindowclass);

	EditorWindow = CreateWindowA("BOJ_SPRITE_EDITOR", "Blade Of Justice (Dev) - Sprite Editor", WS_VISIBLE | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, 0, 0, 800, 600, NULL, NULL, hInstance, NULL);
	if (EditorWindow == NULL)
	{
		MessageBoxA(NULL, "Failed to create the Editor window!", "Fatal error!", MB_OK | MB_ICONERROR);
		exit(-1);
	}
	//Pixels


	//Buttons to choose pixels
	ColorPallete[0]  = RGB(0   ,0  ,0  );
	ColorPallete[1]  = RGB(0,  55 ,218);
	ColorPallete[2]  = RGB(19 ,161,14);
	ColorPallete[3]  = RGB(58 ,150,221);
	ColorPallete[4]  = RGB(197,15 ,31 );
	ColorPallete[5]  = RGB(136,23 ,152);
	ColorPallete[6]  = RGB(193,156,0  );
	ColorPallete[7]  = RGB(204,204,204);
	ColorPallete[8]  = RGB(118,118,118);
	ColorPallete[9]  = RGB(59 ,120,255);
	ColorPallete[10] = RGB(22 ,198 ,12 );
	ColorPallete[11] = RGB(97 ,214 ,214);
	ColorPallete[12] = RGB(321,72 ,86 );
	ColorPallete[13] = RGB(180,0  ,158);
	ColorPallete[14] = RGB(249,249,165);
	ColorPallete[15] = RGB(242,242,242);
	ColorPallete[16] = RGB(255,128,255);

	for (int i = 0; i < 17; i++)
	{
		ColorBrushes[i] = CreateSolidBrush(ColorPallete[i]);
		ColorButtons[i] = CreateWindowExA(0,"BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | SS_OWNERDRAW, 10 + (20 * i), 500, 20, 20, EditorWindow, NULL, hInstance, NULL);
		if (ColorButtons[i] == NULL)
		{
			MessageBoxA(NULL, "Failed to create the editor!", "Fatal error!", MB_OK | MB_ICONERROR);
			exit(-1);
		}
	}

	ShowWindow(EditorWindow, SW_NORMAL);
	MSG msg;
	while (GetMessageA(&msg, EditorWindow, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

LRESULT CALLBACK BoJ_Editor_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hwnd,&ps);
			FillRect(ps.hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW+1));
			EndPaint(hwnd, &ps);
			break;
		}
		case WM_CTLCOLORBTN:
		{
			HDC hdc = (HDC)wparam;
			HWND button = (HWND)lparam;
			for (unsigned i = 0; i < 17; i++)
			{
				if (ColorButtons[i] == button)
				{
					SetBkColor(hdc, ColorPallete[i]);
					SetTextColor(hdc, ColorPallete[0]);
					return (INT_PTR)ColorBrushes[i];
				}
			}
			return 0;
			break;
		}
		case WM_CLOSE:
		case WM_QUIT:
		{
			exit(0);
			break;
		}
		default:
			break;
	}
	return DefWindowProcA(hwnd, msg, wparam, lparam);
}