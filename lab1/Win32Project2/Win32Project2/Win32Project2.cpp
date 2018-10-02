// Win32Project2.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Win32Project2.h"
#include <windows.h>
#include <windef.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
int left = 100, right = 150, top = 200, bottom = 250;
const int move = 1;
bool flag, space = true;
int idTimer = -1;
int moveSide, i = 0, j;
HBITMAP hBitmap = NULL;


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);




// Раздел пользовательских функций
void ChangeSpritePose(HWND hWnd, int &first, int &second, bool plus)
{
	if (!plus)
	{
		first -= move;
		second -= move;
	}
	else
	{
		first += move;
		second += move;
	}
	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);
}

// Изменение размеров квадрата
void ChangeSize(HWND hWnd, int &Height, int &Widht)
{
	right = Height;
	bottom = Widht;
	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);
}

void SpriteMove(HWND hWnd, bool &plus, bool plusValue, bool flag, int side, int &first, int &second)
{
	plus = plusValue;
	if (flag)
	{
		moveSide = side;
		SetTimer(hWnd, 1, 10, NULL);
	}
	ChangeSpritePose(hWnd, first, second, plus);
}

int DisplayConfirmSaveAsMessageBox(int &value)
{
	int msgboxID = MessageBox(
		NULL,
		L"Use Reactangle?",
		L"You're to choose the figure to use",
		MB_ICONEXCLAMATION | MB_YESNO
	);


	if (msgboxID == IDYES)
	{
		value = 1;
	}
	else
		value = 0;

	return value;
}





int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: разместите код здесь.
	

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
	

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT2));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}



//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	 
	
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

	case WM_CREATE:
		hBitmap = (HBITMAP)LoadImage(hInst, L"c:\\test.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		break;
    
	case WM_PAINT:
        {
			PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			SelectObject(hdc, GetStockObject(BLACK_PEN));
			SelectObject(hdc, GetStockObject(BLACK_BRUSH));
			if (i == 0)
			{
				DisplayConfirmSaveAsMessageBox(j);
				i++;
			}	
			if (j == 1)
				Rectangle(hdc, left, top, right, bottom);
			else
				Ellipse(hdc, left, top, right, bottom);
            EndPaint(hWnd, &ps); 
			/*PAINTSTRUCT ps;
			HDC             hdc;
			BITMAP          bitmap;
			HDC             hdcMem;
			HGDIOBJ         oldBitmap;

			hdc = BeginPaint(hWnd, &ps);

			hdcMem = CreateCompatibleDC(hdc);
			oldBitmap = SelectObject(hdcMem, hBitmap);

			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt(hdc, 100, 150, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
			SelectObject(hdcMem, oldBitmap);
			DeleteDC(hdcMem);

			EndPaint(hWnd, &ps);*/		
        }
        break;
    
	case WM_LBUTTONUP:
		{
			HDC hdc = GetDC(hWnd);
			WORD xPos, yPos;
			xPos = LOWORD(lParam);
			yPos = HIWORD(lParam);
			left = xPos - 25;
			right = xPos + 25;
			top = yPos + 25;
			bottom = yPos - 25;
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			ReleaseDC(hWnd, hdc);
		}
		break;

	case WM_SIZE:
		{
			switch (wParam)
			{
				case SIZE_MINIMIZED:
					KillTimer(hWnd, 1);
					idTimer = -1;
					break;
				case SIZE_RESTORED:
					if (right > (int)LOWORD(lParam))
					{
						left = (right = (int)LOWORD(lParam)) -50 ;
					}
					if (bottom > (int)HIWORD(lParam))
					{
						top = (bottom = (int)HIWORD(lParam)) - 50;
					}
				/*case SIZE_MAXIMIZED:
					if (idTimer = -1)
						SetTimer(hWnd, 1, 10, NULL);
					break;*/
			}
			break;
		}
	
	case WM_KEYDOWN:
		{
			bool plus;
			switch (wParam)
			{
				case VK_LEFT:
				{
					SpriteMove(hWnd, plus, false, flag, 1, left, right);
					break;
				}
				case VK_RIGHT:
				{
					SpriteMove(hWnd, plus, true, flag, 2, right, left);
					break;
				}
				case VK_UP:
				{
					if (GetKeyState(VK_SHIFT) < 0)
					{
						SpriteMove(hWnd, plus, false, flag, 1, left, right);
					}
					else
					{
						SpriteMove(hWnd, plus, false, flag, 3, top, bottom);
					}
					break;
				}
				case VK_DOWN:
				{
					if (GetKeyState(VK_SHIFT) < 0)
					{
						SpriteMove(hWnd, plus, true, flag, 2, right, left);
					}
					else
					{
						SpriteMove(hWnd, plus, true, flag, 4, bottom, top);
					}
					break;
				}
				case VK_SPACE:
				{
					switch(space)
					{
						case true:
							moveSide = 1;
							SetTimer(hWnd, 1, 10, NULL);
							flag = true;
							space = false;
							break;
						case false:
							KillTimer(hWnd, 1);
							space = true;
							flag = false;
							break;
					}
					break;
				}
				default:
					break;
			}	
		}
		break;

	case WM_TIMER:
		{	
			bool plus;
			RECT rect;
			int width, height;
			if (GetClientRect(hWnd, &rect))
			{
				width = rect.right - rect.left;
				height = rect.bottom - rect.top;
			}
			switch (moveSide)
			{
			case 1:
				plus = false;
				if (left <= 0)
				{
					SpriteMove(hWnd, plus, true, true, 2, right, left);
				}
				else
					ChangeSpritePose(hWnd, left, right, plus);
				break;
			case 2:
				plus = true;
				if (right >= width)
				{
					SpriteMove(hWnd, plus, false, true, 1, left, right);
				}
				else
					ChangeSpritePose(hWnd, right, left, plus);
				break;
			case 3:
				plus = false;
				if (top <= 0)
				{
					SpriteMove(hWnd, plus, true, true, 4, top, bottom);
				}
				else
					ChangeSpritePose(hWnd, top, bottom, plus);
				break;
			case 4:
				plus = true;
				if (bottom >= height)
				{
					SpriteMove(hWnd, plus, false, true, 3, left, right);
				}
				else
					ChangeSpritePose(hWnd, bottom, top, plus);
				break;

			}
			//if (left == 0)
				//plus = true;
			//while(1)					
			break;
		}

	case WM_MOUSEWHEEL:
		{
			bool plus;
				
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			{
				plus = false;
				if (GetKeyState(VK_CONTROL) < 0)
					ChangeSize(hWnd, ++right, ++bottom);
				else
					if (GetKeyState(VK_SHIFT) < 0)
						ChangeSpritePose(hWnd, left, right, plus);
					else
						ChangeSpritePose(hWnd, top, bottom, plus);
			}
			else
			{
				plus = true;
				if (GetKeyState(VK_CONTROL) < 0)
					ChangeSize(hWnd, --right, --bottom);
				else
					if (GetKeyState(VK_SHIFT) < 0)
						ChangeSpritePose(hWnd, right, left, plus);
					else
						ChangeSpritePose(hWnd, bottom, top, plus);
			}
		}
		break;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		break;
    
	default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
