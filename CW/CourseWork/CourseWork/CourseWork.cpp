// CourseWork.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "CourseWork.h"

#include "math.h"
#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "windows.h"

#define _CRT_SECURE_NO_WARNINGS

#define M_PI 3.14159265358979323846 

#define MAX_LOADSTRING 100

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
    LoadStringW(hInstance, IDC_COURSEWORK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COURSEWORK));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COURSEWORK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_COURSEWORK);
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

const char name_file[] = "model3D.obj";
char str[20];
FILE* file;

int quantity_vertexes = 0;
int quantity_edges = 0;

float** mass_vertexes;
float** mass_edges;

float** new_vertexes;

float angleA = 330.0;
float angleB = 180.0;

float R = 1024.0;
float d = 512.0;

float screen_width = 750;
float screen_height = 400;

int ratio_scale = 4;

void quantity_vert_edg()
{
    file = fopen(name_file, "r");
    while ((fscanf(file, "%s", str) != EOF)) 
    {
        if (!file)
        {
            break;
        }
        if (str[0] == 'v') 
        {
            quantity_vertexes++;
        }
        if (str[0] == 'l') 
        {
            quantity_edges++;
        }
    }
    fclose(file);
};

float** set_vertexes(int size)
{
    float** arr_vertexes;
    arr_vertexes = (float**)malloc(size * sizeof(float*));
    for (int i = 0; i < size; i++)
    {
        arr_vertexes[i] = (float*)malloc(4 * sizeof(float));
        for (int j = 0; j < 4; j++)
        {
            arr_vertexes[i][j] = 1;
        }

    }
    return arr_vertexes;
};

float** set_edges(int size)
{
    float** arr_edges;
    arr_edges = (float**)malloc(size * sizeof(float*));
    for (int i = 0; i < size; i++)
    {
        arr_edges[i] = (float*)malloc(4 * sizeof(float));
    }
    return arr_edges;
};

void read_vertexes_from_file()
{
    int i = 0;
    file = fopen(name_file, "r");
    while ((fscanf(file, "%s", str) != EOF)) 
    {
        if (!file)
        {
            break;
        }
        if (str[0] == 'v') 
        {
            for (i; i < quantity_vertexes; i++)
            {
                for (int j = 0; j < 3; j++) 
                {
                    fscanf(file, "%f", &mass_vertexes[i][j]);
                }
                break;
            }
            i++;
        }
    }
    fclose(file);
}

void read_edges_from_file()
{
    int i = 0;
    file = fopen(name_file, "r");
    while ((fscanf(file, "%s", str) != EOF)) 
    {
        if (!file)
        {
            break;
        }
        if (str[0] == 'l') 
        {
            for (i; i < quantity_edges; i++)
            {
                for (int j = 0; j < 2; j++) 
                {
                    fscanf(file, "%f", &mass_edges[i][j]);
                }
                break;
            }
            i++;
        }
    }
    fclose(file);
}

void view_transformation() // Видовое преобразование
{
    float fi = angleA * M_PI / 180;
    float TETA = angleB * M_PI / 180;

    float matrix_vid[4][4]
    {
    {-sin(TETA) , -cos(fi) * cos(TETA) , -sin(fi) * cos(TETA) , 0},
    { cos(TETA) , -cos(fi) * sin(TETA) , -sin(fi) * sin(TETA) , 0},
    {	     0  ,		       sin(fi) ,	         -cos(fi) , 0},
    {        0  ,                   0  ,                   R  , 1}
    };

    for (int i = 0; i < quantity_vertexes; i++)
    {
        for (int j = 0; j < 4; j++) 
        {
            new_vertexes[i][j] = 0;
            for (int k = 0; k < 4; k++) 
            {
                new_vertexes[i][j] = new_vertexes[i][j] + mass_vertexes[i][k] * matrix_vid[k][j];
            }
            new_vertexes[i][3] = mass_vertexes[i][3];
        }
    }
}

void perspective_transformation() // Перспективное преобразование 
{
    for (int i = 0; i < quantity_vertexes; i++)
    {
        new_vertexes[i][0] = (d * new_vertexes[i][0] / new_vertexes[i][2]);
        new_vertexes[i][1] = (d * new_vertexes[i][1] / new_vertexes[i][2]);
    }
}

void screen_transformation() // Экранное преобразование
{
    for (int i = 0; i < quantity_vertexes; i++)
    {
        new_vertexes[i][0] = new_vertexes[i][0] + screen_height;
        new_vertexes[i][1] = new_vertexes[i][1] + screen_width;
    }
}

void change_scale() // Уменьшение коэффициента
{
    for (int i = 0; i < quantity_vertexes; i++)
    {
        for (int j = 0; j < 3; j++) 
        {
            mass_vertexes[i][j] = mass_vertexes[i][j] * ratio_scale;
        }
    }
}

void drawing(HDC hdc) //Отрисовка модели
{
    int vertex;
    for (int i = 0; i < quantity_edges; i++)
    {
        for (int j = 0; j < 2; j++) 
        {
            vertex = mass_edges[i][j];
            if (vertex > 0) 
            {
                if (j == 0) 
                {
                    MoveToEx(hdc, new_vertexes[vertex][1], new_vertexes[vertex][0], NULL);
                }
                else 
                {
                    LineTo(hdc, new_vertexes[vertex][1], new_vertexes[vertex][0]);
                }
            }
        }
    }
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

    case WM_KEYDOWN:
    {
        switch (LOWORD(wParam))
        {
        case VK_RIGHT:
        {
            angleA = angleA + 10.0;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        case VK_LEFT:
        {
            angleA = angleA - 10.0;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        case VK_UP:
        {
            angleB = angleB + 10.0;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        case VK_DOWN:
        {
            angleB = angleB - 10.0;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }

        case VK_F1:
        {
            ratio_scale = ratio_scale + 1.0;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        case VK_F2:
        {
            ratio_scale = ratio_scale - 1.0;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }

        case VK_F3:
        {
            d = d + 100.0;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        case VK_F4:
        {
            d = d - 100.0;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }

        case VK_F5:
        {
            R = R + 50.0;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        case VK_F6:
        {
            R = R - 50.0;
            InvalidateRect(hWnd, NULL, TRUE);
            break;
        }
        }
    }
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...

            quantity_vert_edg();

            mass_vertexes = set_vertexes(quantity_vertexes);
            mass_edges = set_edges(quantity_edges);

            new_vertexes = set_vertexes(quantity_vertexes);
            read_vertexes_from_file();
            change_scale();
            read_edges_from_file();
            view_transformation();
            perspective_transformation();
            screen_transformation();
            drawing(hdc);

            EndPaint(hWnd, &ps);

            free(mass_vertexes);
            free(mass_edges);
            free(new_vertexes);
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
