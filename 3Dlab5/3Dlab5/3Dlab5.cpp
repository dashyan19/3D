// 3Dlab5.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "3Dlab5.h"

#include "cmath"

#define MAX_LOADSTRING 100

float prism[12][4] =
{
    {-75, 125, -200, 1},       //0 задняя левая нижняя вершина
    {75, 125, -200, 1},        //1 задняя правая нижняя вершина
    {150, 0, -200,1},           //2 боковая правая нижняя вершина
    {75, -125, -200,1},        //3 передняя правая нижняя вершина
    {-75, -125, -200,1},       //4 передняя левая нижняя вершина
    {-150, 0, -200,1},          //5 боковая левая нижняя вершина

    {-75, 125, 200, 1},        //6 задняя левая нижняя вершина
    {75, 125, 200, 1},         //7 задняя правая нижняя вершина
    {150, 0, 200,1},            //8 боковая правая нижняя вершина
    {75, -125, 200,1},         //9 передняя правая нижняя вершина
    {-75, -125, 200,1},        //10 передняя левая нижняя вершина
    {-150, 0, 200,1},           //11 боковая левая нижняя вершина
};

float R = -400;
float TETA = 90;
float FI = 0;

void view_transformation();
void perspective_transformation();

void drawing_prism(HDC hdc);

float prism_view[12][4];

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY3DLAB5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3DLAB5));

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
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3DLAB5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY3DLAB5);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, SW_SHOWMAXIMIZED); // показываем окно на весь экран
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
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

    case WM_KEYDOWN:
        switch (wParam) {
        
        case VK_F1:
        {
            perspective_transformation();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }

        case VK_F2:
        {
            view_transformation();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }

        case VK_F3:
        {
            if (R > -300)
            {
                R = R - 5;
                perspective_transformation();
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        }
        case VK_F4:
        {
            if (R <= -120)
            {
                R = R + 5;
                perspective_transformation();
                InvalidateRect(hWnd, NULL, TRUE);
            }
            break;
        }

        case VK_LEFT:
        {
           TETA = TETA - 0.1;
           view_transformation();
           InvalidateRect(hWnd, NULL, TRUE);
           break;
        }

        case VK_RIGHT:
        {

            TETA = TETA + 0.1;
            view_transformation();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }

        case VK_UP:
        {
            FI = FI + 0.1;
            view_transformation();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }

        case VK_DOWN:
        {
            FI = FI - 0.1;
            view_transformation();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }

        case VK_NUMPAD1:
        {
            TETA = TETA - 0.1;
            perspective_transformation();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }

        case VK_NUMPAD3:
        {

            TETA = TETA + 0.1;
            perspective_transformation();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }

        case VK_NUMPAD5:
        {
            FI = FI + 0.1;
            perspective_transformation();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }

        case VK_NUMPAD2:
        {
            FI = FI - 0.1;
            perspective_transformation();
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }

        break;
        }

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...

            RECT rect;

            GetWindowRect(hWnd, &rect);
            LONG width = rect.right - rect.left;
            LONG height = rect.bottom - rect.top;

            //переносим началы координат в середину экрана
            SetMapMode(hdc, MM_ANISOTROPIC);
            SetViewportOrgEx(hdc, width / 2, height / 2, NULL);

            //ставим точку в начало координат
            SetPixel(hdc, 0, 0, RGB(255, 0, 0));

            drawing_prism(hdc);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


void drawing_prism(HDC hdc)
{
    MoveToEx(hdc, prism_view[0][0], prism_view[0][1], NULL);
    LineTo(hdc, prism_view[1][0], prism_view[1][1]);
    LineTo(hdc, prism_view[2][0], prism_view[2][1]);
    LineTo(hdc, prism_view[3][0], prism_view[3][1]);
    LineTo(hdc, prism_view[4][0], prism_view[4][1]);
    LineTo(hdc, prism_view[5][0], prism_view[5][1]);
    LineTo(hdc, prism_view[0][0], prism_view[0][1]);

    MoveToEx(hdc, prism_view[6][0], prism_view[6][1], NULL);
    LineTo(hdc, prism_view[7][0], prism_view[7][1]);
    LineTo(hdc, prism_view[8][0], prism_view[8][1]);
    LineTo(hdc, prism_view[9][0], prism_view[9][1]);
    LineTo(hdc, prism_view[10][0], prism_view[10][1]);
    LineTo(hdc, prism_view[11][0], prism_view[11][1]);
    LineTo(hdc, prism_view[6][0], prism_view[6][1]);

    MoveToEx(hdc, prism_view[0][0], prism_view[0][1], NULL);
    LineTo(hdc, prism_view[6][0], prism_view[6][1]);

    MoveToEx(hdc, prism_view[1][0], prism_view[1][1], NULL);
    LineTo(hdc, prism_view[7][0], prism_view[7][1]);

    MoveToEx(hdc, prism_view[2][0], prism_view[2][1], NULL);
    LineTo(hdc, prism_view[8][0], prism_view[8][1]);

    MoveToEx(hdc, prism_view[3][0], prism_view[3][1], NULL);
    LineTo(hdc, prism_view[9][0], prism_view[9][1]);

    MoveToEx(hdc, prism_view[4][0], prism_view[4][1], NULL);
    LineTo(hdc, prism_view[10][0], prism_view[10][1]);

    MoveToEx(hdc, prism_view[5][0], prism_view[5][1], NULL);
    LineTo(hdc, prism_view[11][0], prism_view[11][1]);
}

void view_transformation()
{  // Видовое преобразование
    float matrix[4][4] =
    {
    {-sin(TETA),-cos(FI) * cos(TETA),-sin(FI) * cos(TETA),0},
    {cos(TETA),-cos(FI) * sin(TETA), -sin(FI) * sin(TETA), 0},
    {0, sin(FI), -cos(FI), 0},
    {0, 100, R, 1}
    };

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            prism_view[i][j] = 0;
            for (int k = 0; k < 4; k++)
            {
                prism_view[i][j] += prism[i][k] * matrix[k][j];
            }
        }
    }
}

void perspective_transformation()
{
    float matrix[4][4] =
    {
    {-sin(TETA),-cos(FI) * cos(TETA),-sin(FI) * cos(TETA),0},
    {cos(TETA),-cos(FI) * sin(TETA), -sin(FI) * sin(TETA), 0},
    {0, sin(FI), -cos(FI), 0},
    {0, 100, R, 1}
    };

    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            prism_view[i][j] = 0;
            for (int k = 0; k < 4; k++)
            {
                prism_view[i][j] += prism[i][k] * matrix[k][j];
            }
        };
    }

    int k = 0;

    for (int i = 0; i < 12; i++)
    {
        prism_view[i][k] = prism_view[i][k] * R / (prism_view[i][k + 2] + R);
    }
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
