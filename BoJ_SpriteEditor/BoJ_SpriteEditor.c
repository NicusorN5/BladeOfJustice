#include "BoJ_SpriteEditor.h"

HWND ColorButtons[16];

HBRUSH ColorBrushes[17];

COLORREF ColorPallete[17];

char PixelsColor[32][32];

HWND EditorWindow;
HINSTANCE g_hInstance;

char CurrentProject[MAX_PATH];

int SelectedColour;

HWND DrawingTable;

int __stdcall wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,_In_ LPWSTR lpCmdLine,_In_ int nShowCmd)
{
	//Main window
	EditorWindow = NULL;
	g_hInstance = hInstance;

	WNDCLASSA mainwindowclass;
	memset(&mainwindowclass, 0, sizeof(WNDCLASSA));

	mainwindowclass.hInstance = hInstance;
	mainwindowclass.lpszClassName = "BOJ_SPRITE_EDITOR";
	mainwindowclass.lpfnWndProc = BoJ_Editor_WndProc;
	
	RegisterClassA(&mainwindowclass);

	HMENU Menu = CreateMenu();

	HMENU FileMenu = CreateMenu();
	AppendMenuA(FileMenu, MF_STRING, 400, "New");
	AppendMenuA(FileMenu, MF_STRING, 401, "Open");
	AppendMenuA(FileMenu, MF_STRING, 402, "Save");
	AppendMenuA(FileMenu, MF_STRING, 403, "Save As");
	AppendMenuA(FileMenu, MF_STRING, 404, "Exit");

	AppendMenuA(Menu, MF_POPUP, (UINT_PTR)FileMenu, "File");

	EditorWindow = CreateWindowA("BOJ_SPRITE_EDITOR", "Blade Of Justice (Dev) - Sprite Editor", WS_VISIBLE | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, 0, 0, 460, 430, NULL, Menu, hInstance, NULL);
	if (EditorWindow == NULL)
	{
		MessageBoxA(NULL, "Failed to create the Editor window!", "Fatal error!", MB_OK | MB_ICONERROR);
		exit(-1);
	}
	//Literally the drawing board control

	WNDCLASSA drawingclass;
	memset(&drawingclass, 0, sizeof(WNDCLASSA));
	drawingclass.hInstance = hInstance;
	drawingclass.lpszClassName = "BOJ_PAINT";
	drawingclass.lpfnWndProc = BoJ_Paint_WndProc;

	RegisterClassA(&drawingclass);

	DrawingTable = CreateWindowExA(0, "BOJ_PAINT", "", WS_VISIBLE | WS_CHILD | SS_OWNERDRAW, 10, 10, 320, 320, EditorWindow, NULL, hInstance, NULL);

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
		ColorButtons[i] = CreateWindowExA(0,"BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_OWNERDRAW, 10 + (25 * i), 340, 20, 20, EditorWindow, NULL, hInstance, NULL);
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
		case WM_COMMAND:
		{
			int a = 0;
			for (size_t i = 0; i < 17; i++)
			{
				if (lparam == ColorButtons[i])
				{
					a = 1;
					SelectedColour = i;
					break;
				}
			}
			if (a) break;
			switch (LOWORD(wparam))
			{
				case 400:
				{
					CurrentProject[0] = 0;
					for (unsigned i = 0; i < 32; i++)
					{
						for (unsigned j = 0; j < 32; j++)
						{
							PixelsColor[i][j] = 16;
						}
					}
					break;
				}
				case 401:
				{
					char file[MAX_PATH+1];
					memset(file, 0, MAX_PATH+1);

					OPENFILENAMEA ofn;
					memset(&ofn, 0, sizeof(ofn));
					ofn.lStructSize = sizeof(OPENFILENAMEA);
					ofn.hwndOwner = EditorWindow;
					ofn.lpstrFile = file;
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrFilter = "BoJ image files (*.bojimg)\0*.bojimg";
					ofn.hInstance = g_hInstance;
					ofn.Flags = OFN_FILEMUSTEXIST;
					ofn.lpstrTitle = "Open a file...";

					if (GetOpenFileNameA(&ofn))
					{
						file[MAX_PATH] = 0;
						
						FILE* fptr = fopen(file, "r");

						for (unsigned i = 0; i < 32; i++)
						{
							for (unsigned j = 0; j < 32; j++)
							{
								int r = fscanf(fptr, "%hhd ", &(PixelsColor[i][j]));
								if (r < 0)
								{
									MessageBoxA(EditorWindow, "Failed to read file!", "Error", MB_ICONERROR | MB_OK);
								}
							}
						}
					}
					break;
				}
				case 402:
				{
					if (CurrentProject[0] != 0)
					{
						SaveProject(CurrentProject);
					}
					else SaveProjectDialog();
					break;
				}
				case 403:
				{
					SaveProjectDialog();
					break;
				}
				case 404:
				{
					PostQuitMessage(0);
					break;
				}
				default:
					break;
			}
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

LRESULT CALLBACK BoJ_Paint_WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{

		case WM_PAINT:
		{
			/*
			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);

			HDC hdc = ps.hdc;
			//pain

			for (int i = 0; i < 32; i++)
			{
				for (int j = 0; j < 32; j++)
				{	
					SelectObject(hdc, ColorBrushes[PixelsColor[i][j]]);
					Rectangle(hdc, 10 * i, 10 * j, 10 * (i + 1), 10 * (j + 1));
				}
			}
			
			EndPaint(hwnd, &ps);
			*/
			PAINTSTRUCT ps;
			BeginPaint(hwnd, &ps);
			FillRect(ps.hdc, &ps.rcPaint, ColorBrushes[17]);
			EndPaint(hwnd, &ps);
			return 0;
		}
		case WM_LBUTTONDOWN:
		{
			POINT cursor;
			GetCursorPos(&cursor);

			RECT r;
			SetRect(&r, 0, 0, 320, 320);

			if (PtInRect(&r,cursor) != 0)
			{
				POINT delta = {cursor.x - r.left,cursor.y - r.top };
				POINT px_coord = { delta.x / 10,delta.y / 10 };
				PixelsColor[px_coord.x][px_coord.y] = SelectedColour;

				PAINTSTRUCT ps;
				BeginPaint(hwnd, &ps);

				HDC hdc = GetDC(hwnd);
				//pain

				for (int i = 0; i < 32; i++)
				{
					for (int j = 0; j < 32; j++)
					{
						SelectObject(hdc, ColorBrushes[PixelsColor[i][j]]);
						Rectangle(hdc, 10 * i, 10 * j, 10 * (i + 1), 10 * (j + 1));
					}
				}

				ReleaseDC(hwnd, hdc);

			}

			break;
		}
	
	default:
		break;
	}
	return DefWindowProcA(hwnd, msg, wparam, lparam);
}

void SaveProjectDialog()
{
	char file[MAX_PATH + 1];
	memset(file, 0, MAX_PATH + 1);

	OPENFILENAMEA ofn;
	memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAMEA);
	ofn.hwndOwner = EditorWindow;
	ofn.lpstrFile = file;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrFilter = "BoJ image files (*.bojimg)\0*.bojimg";
	ofn.nFilterIndex = 1;
	ofn.hInstance = g_hInstance;
	ofn.Flags = OFN_DONTADDTORECENT | OFN_HIDEREADONLY;
	ofn.lpstrTitle = "Save the image...";

	if (GetSaveFileNameA(&ofn))
	{
		memcpy(CurrentProject, file, MAX_PATH);
		SaveProject(CurrentProject);
	}
}

void SaveProject(char *path)
{
	FILE* fptr = fopen(path, "w");

	for (unsigned i = 0; i < 32; i++)
	{
		for (unsigned j = 0; j < 32; j++)
		{
			fprintf(fptr, "%i ", PixelsColor[i][j]);
		}
		fprintf(fptr, "\r\n");
	}
	fclose(fptr);
}

void RedrawEditor()
{
	RECT r;
	SetRect(&r, 0, 0, 320, 320);

	InvalidateRect(DrawingTable, &r, TRUE);
	UpdateWindow(DrawingTable);
}
