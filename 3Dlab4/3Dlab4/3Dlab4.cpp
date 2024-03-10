// 3Dlab4.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "3Dlab4.h"

#define MAX_LOADSTRING 100

LONG width = 250, height = 250;
void brightness_gradation(HDC hdc);
void contrast_ratio(HDC hdc);
int flag = 0;

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
    LoadStringW(hInstance, IDC_MY3DLAB4, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3DLAB4));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3DLAB4));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY3DLAB4);
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
            case IDM_BRIGHTNESS_GRADATION:
                flag = 1;
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);

            case IDM_CONTRAST_RATIO:
                flag = 2;
                InvalidateRect(hWnd, NULL, TRUE);
                UpdateWindow(hWnd);

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            
            HDC memdc;
            memdc = CreateCompatibleDC(hdc);

            HBITMAP bmw = (HBITMAP)LoadImage(NULL, L"fractal2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR);
            SelectObject(memdc, bmw);
            BitBlt(hdc, 10, 10, width, height, memdc, 0, 0, SRCCOPY);

            HBITMAP bmw1 = (HBITMAP)LoadImage(NULL, L"fractal2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR);
            SelectObject(memdc, bmw1);
            BitBlt(hdc, width + 70, 10, width, height, memdc, 0, 0, SRCCOPY);

            HBITMAP bmw2 = (HBITMAP)LoadImage(NULL, L"fractal2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR);
            SelectObject(memdc, bmw1);
            BitBlt(hdc, width + 380, 10, width, height, memdc, 0, 0, SRCCOPY);

            HBITMAP bmw3 = (HBITMAP)LoadImage(NULL, L"fractal2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR);
            SelectObject(memdc, bmw1);
            BitBlt(hdc, width + 690, 10, width, height, memdc, 0, 0, SRCCOPY);

            HBITMAP bmw4 = (HBITMAP)LoadImage(NULL, L"fractal2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR);
            SelectObject(memdc, bmw1);
            BitBlt(hdc, width + 1000, 10, width, height, memdc, 0, 0, SRCCOPY);
            
            switch (flag)
            {
            case 1:
                brightness_gradation(hdc);
                break;
            default:
                break;
            }

            switch (flag)
            {
            case 2:
                contrast_ratio(hdc);
                break;
            default:
                break;
            }

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

void brightness_gradation(HDC hdc) 
{ 
    int averege = 0;
    int color, r, g, b;
    for (int i = width + 70; i < width * 2 + 70; i++)
    {
        for (int j = 10; j < height + 10; j++)
        {
            color = GetPixel(hdc, i, j);
            r = GetRValue(color);
            g = GetGValue(color);
            b = GetBValue(color);

            averege = (r + g + b) / 3;
            SetPixel(hdc, i, j, RGB(averege, averege, averege));
        }
    }

    for (int i = width + 380; i < width * 2 + 380; i++)
    {
        for (int j = 10; j < height + 10; j++)
        {
            color = GetPixel(hdc, i, j);
            r = GetRValue(color);
            g = GetGValue(color);
            b = GetBValue(color);

            averege = (r + g + b) / 3;
            SetPixel(hdc, i, j, RGB(r, 0, 0));
        }
    }

    for (int i = width + 690; i < width * 2 + 690; i++)
    {
        for (int j = 10; j < height + 10; j++)
        {
            color = GetPixel(hdc, i, j);
            r = GetRValue(color);
            g = GetGValue(color);
            b = GetBValue(color);

            averege = (r + g + b) / 3;
            SetPixel(hdc, i, j, RGB(0, g, 0));
        }
    }

    for (int i = width + 1000; i < width * 2 + 1000; i++)
    {
        for (int j = 10; j < height + 10; j++)
        {
            color = GetPixel(hdc, i, j);
            r = GetRValue(color);
            g = GetGValue(color);
            b = GetBValue(color);

            averege = (r + g + b) / 3;
            SetPixel(hdc, i, j, RGB(0, 0, b));
        }
    }

    //система координат для первого результирующего изображения:
    MoveToEx(hdc, width + 70, height + 20, NULL);
    LineTo(hdc, width + 70, height * 2 + 20);
    LineTo(hdc, width * 2 + 70, height * 2 + 20);

    //система координат для второго результирующего изображения:
    MoveToEx(hdc, width + 380, height + 20, NULL);
    LineTo(hdc, width + 380, height * 2 + 20);
    LineTo(hdc, width * 2 + 380, height * 2 + 20);

    //система координат для третьего результирующего изображения:
    MoveToEx(hdc, width + 690, height + 20, NULL);
    LineTo(hdc, width + 690, height * 2 + 20);
    LineTo(hdc, width * 2 + 690, height * 2 + 20);

    //система координат для четвертого результирующего изображения:
    MoveToEx(hdc, width + 1000, height + 20, NULL);
    LineTo(hdc, width + 1000, height * 2 + 20);
    LineTo(hdc, width * 2 + 1000, height * 2 + 20);

    int aver_sum = 0, aver_per_pix = 0, aver_color = 0;

    for (int i = width + 70; i < width * 2 + 70; i++)
    {
        aver_sum = 0;
        MoveToEx(hdc, i, 270, NULL);
        for (int j = 0; j < height; j++)
        {
            color = GetPixel(hdc, i, j);
            aver_per_pix = (GetRValue(color) + GetGValue(color) + GetBValue(color)) / 3;
            aver_sum += aver_per_pix;
        }
        aver_color = aver_sum / height;
        LineTo(hdc, i, (aver_sum / 100) + height);
    }

    for (int i = width + 380; i < width * 2 + 380; i++)
    {
        aver_sum = 0;
        MoveToEx(hdc, i, 270, NULL);
        for (int j = 0; j < height; j++)
        {
            color = GetPixel(hdc, i, j);
            aver_per_pix = (GetRValue(color) + GetGValue(color) + GetBValue(color)) / 3;
            aver_sum += aver_per_pix;
        }
        aver_color = aver_sum / height;
        LineTo(hdc, i, (aver_sum / 100) + height);
    }

    for (int i = width + 690; i < width * 2 + 690; i++)
    {
        aver_sum = 0;
        MoveToEx(hdc, i, 270, NULL);
        for (int j = 0; j < height; j++)
        {
            color = GetPixel(hdc, i, j);
            aver_per_pix = (GetRValue(color) + GetGValue(color) + GetBValue(color)) / 3;
            aver_sum += aver_per_pix;
        }
        aver_color = aver_sum / height;
        LineTo(hdc, i, (aver_sum / 100) + height);
    }

    for (int i = width + 1000; i < width * 2 + 1000; i++)
    {
        aver_sum = 0;
        MoveToEx(hdc, i, 270, NULL);
        for (int j = 0; j < height; j++)
        {
            color = GetPixel(hdc, i, j);
            aver_per_pix = (GetRValue(color) + GetGValue(color) + GetBValue(color)) / 3;
            aver_sum += aver_per_pix;
        }
        aver_color = aver_sum / height;
        LineTo(hdc, i, (aver_sum / 100) + height);
    }

}

void contrast_ratio(HDC hdc)
{
    int averege;
    int color, r, g, b;
    int contrast;

    int lower_threshold = 80;
    int upper_threshold = 155;

    //int lower_threshold = 15;
    //int upper_threshold = 240;

    //int lower_threshold = 50;
    //int upper_threshold = 205;

    //int lower_threshold = 100;
    //int upper_threshold = 170;

    for (int i = width + 70; i < width * 2 + 70; i++)
    {
        for (int j = 10; j < height + 10; j++)
        {
            color = GetPixel(hdc, i, j);
            r = GetRValue(color);
            g = GetGValue(color);
            b = GetBValue(color);

            if (r < lower_threshold) //условие с тем самым порогом
            {
                r = 0;
            }
            else if (r > upper_threshold) //условие с тем самым порогом
            {
                r = 255;
            }
            else 
            {
                r = r * (upper_threshold - lower_threshold) / 256;
            }

            if (g < lower_threshold) //условие с тем самым порогом
            {
                g = 0;
            }
            else if (g > upper_threshold) //условие с тем самым порогом
            {
                g = 255;
            }
            else 
            {
                g = g * (upper_threshold - lower_threshold) / 256;
            }

            if (b < lower_threshold) //условие с тем самым порогом
            {
                b = 0;
            }
            else if (b > upper_threshold) //условие с тем самым порогом
            {
                b = 255;
            }
            else 
            {
                b = b * (upper_threshold - lower_threshold) / 256;
            }

            SetPixel(hdc, i, j, RGB(r, g, b));

        }
    }

    //система координат для первого результирующего изображения:
    MoveToEx(hdc, width + 70, height + 20, NULL);
    LineTo(hdc, width + 70, height * 2 + 20);
    LineTo(hdc, width * 2 + 70, height * 2 + 20);

    int aver_sum = 0, aver_per_pix = 0, aver_color = 0;

    for (int i = width + 70; i < width * 2 + 70; i++)
    {
        aver_sum = 0;
        MoveToEx(hdc, i, 270, NULL);
        for (int j = 0; j < height; j++)
        {
            color = GetPixel(hdc, i, j);
            aver_per_pix = (GetRValue(color) + GetGValue(color) + GetBValue(color)) / 3;
            aver_sum += aver_per_pix;
        }
        aver_color = aver_sum / height;
        LineTo(hdc, i, (aver_sum / 100) + height);
    }
}

//int lower_threshold = 100;
//int upper_threshold = 155;

//int lower_threshold = 15;
//int upper_threshold = 240;

//int lower_threshold = 1;
//int upper_threshold = 254;

//for (int i = width + 70; i < width * 2 + 70; i++)
//{
//    for (int j = 10; j < height + 10; j++)
//    {
//        color = GetPixel(hdc, i, j);
//        r = GetRValue(color);
//        g = GetGValue(color);
//        b = GetBValue(color);
//
//        averege = (r + g + b) / 3;
//        SetPixel(hdc, i, j, RGB(r, g, b));
//
//        if (averege < lower_threshold) //условие с тем самым порогом
//        {
//            SetPixel(hdc, i, j, RGB(0, 0, 0));
//        }
//        if (averege > upper_threshold) //условие с тем самым порогом
//        {
//            SetPixel(hdc, i, j, RGB(255, 255, 255));
//        }
//        else if ((averege >= lower_threshold) && (averege <= upper_threshold))
//        {
//            contrast = (255 * (averege - lower_threshold) / (upper_threshold - lower_threshold));
//            SetPixel(hdc, i, j, RGB(contrast, contrast, contrast));
//        }
//    }
//}

//if (r < lower_threshold) //условие с тем самым порогом
//{
//    SetPixel(hdc, i, j, RGB(0, 0, 0));
//}
//else if (r > upper_threshold) //условие с тем самым порогом
//{
//    SetPixel(hdc, i, j, RGB(255, 255, 255));
//}
//else if ((r >= lower_threshold) && (r <= upper_threshold))
//{
//    contrast = (255 * (r - lower_threshold) / (upper_threshold - lower_threshold));
//    SetPixel(hdc, i, j, RGB(contrast, 0, 0));
//}
//
////SetPixel(hdc, i, j, RGB(0, g, 0));
//
//if (g < lower_threshold) //условие с тем самым порогом
//{
//    SetPixel(hdc, i, j, RGB(0, 0, 0));
//}
//else if (g > upper_threshold) //условие с тем самым порогом
//{
//    SetPixel(hdc, i, j, RGB(255, 255, 255));
//}
//
//else if ((g >= lower_threshold) && (g <= upper_threshold))
//{
//    contrast = (255 * (g - lower_threshold) / (upper_threshold - lower_threshold));
//    SetPixel(hdc, i, j, RGB(0, contrast, 0));
//}
//
////SetPixel(hdc, i, j, RGB(0, 0, b));
//
//if (b < lower_threshold) //условие с тем самым порогом
//{
//    SetPixel(hdc, i, j, RGB(0, 0, 0));
//}
//else if (b > upper_threshold) //условие с тем самым порогом
//{
//    SetPixel(hdc, i, j, RGB(255, 255, 255));
//}
//
//else if ((b >= lower_threshold) && (b <= upper_threshold))
//{
//    contrast = (255 * (b - lower_threshold) / (upper_threshold - lower_threshold));
//    SetPixel(hdc, i, j, RGB(0, 0, contrast));
//}