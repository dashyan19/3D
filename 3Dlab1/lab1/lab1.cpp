// WindowsProject21.cpp : Определяет точку входа для приложения.
//

#include "math.h"
#include "framework.h"
#include "lab1.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна


int Zero[21][3] = { 330, 0, 0, 345, 30, 1, 345, 240, 1, 405, 240, 1, 345, 217.5, 1, 345, 90, 1,
495, 180, 1, 345, 165, 1, 330, 0, 0, 315, 30, 1, 315, 240, 1, 255, 240, 1, 315, 217.5, 1, 315, 90, 1,
165, 180, 1, 315, 165, 1, 330, 255, 0, 330, 210, 1, 255, 240, 0, 345, 240, 1, 330, 127, 0 };




float points2[21][3] = { 330, 0, 0, 345, 30, 1, 345, 240, 1, 405, 240, 1, 345, 217.5, 1, 345, 90, 1,
495, 180, 1, 345, 165, 1, 330, 0, 0, 315, 30, 1, 315, 240, 1, 255, 240, 1, 315, 217.5, 1, 315, 90, 1,
165, 180, 1, 315, 165, 1, 330, 255, 0, 330, 210, 1, 255, 240, 0, 345, 240, 1,  330, 127, 0 };


float maxheight = points2[0][1], maxlength = points2[0][0];
float minheight = points2[0][1], minlength = points2[0][0];

float averagelength = maxlength - minlength;
float averageheight = maxheight - minheight;








float move0[3][3] = { 1, 0, 0,
                   0, 1, 0,
                   -maxlength, -maxheight, 1 };

float movenow[3][3] = { 1, 0, 0,
                   0, 1, 0,
                   maxlength, maxheight, 1 };


float moveup[3][3] = { 1, 0, 0,
                   0, 1, 0,
                   0, -(averageheight), 1 };



float moveright[3][3] = { 1, 0, 0,
                   0, 1, 0,
                   averagelength, 0, 1 };


float moveleft[3][3] = { 1, 0, 0,
                   0, 1, 0,
                   -averagelength, 0, 1 };

float movedown[3][3] = { 1, 0, 0,
                   0, 1, 0,
                   0, averageheight, 1 };




float otr[3][3] = {
    1, 0,  0,
    0, -1, 0,
    0, 0,  1 };


float rad = 110 * 3.14159 / 180;
float rotate[3][3] = {
    {cos(rad), sin(rad), 0},
    {-sin(rad), cos(rad), 0},
    {-points2[20][0] * (cos(rad) - 1) + points2[20][1] * sin(rad),  -points2[20][1] * (cos(rad) - 1) - points2[20][0] * sin(rad), 1},
};



void raschet() {
    int tochka;
    tochka = sizeof(points2);

    for (int i = 0; i < (sizeof(points2) / 4 / 3) - 1; i++) {
        if (points2[i][1] > maxheight) { maxheight = points2[i][1]; }
        if (points2[i][1] < minheight) { minheight = points2[i][1]; }
    }

    for (int i = 0; i < (sizeof(points2) / 4 / 3) - 1; i++) {
        if (points2[i][0] > maxlength) { maxlength = points2[i][0]; }
        if (points2[i][0] < minlength) { minlength = points2[i][0]; }
    }


    averagelength = maxlength - minlength;
    averageheight = maxheight - minheight;

  

    

    int v = (sizeof(points2) / 4 / 3) - 1;


   
}

void rerun(float trans1[3][3], float trans2[3][3], float trans3[3][3], float trans4[3][3]) {

    trans1[2][1] = -averageheight;
    trans2[2][0] = averagelength;
    trans3[2][0] = -averagelength;
    trans4[2][1] = averageheight;

}


void rerun2(float trans1[3][3]) {

    trans1[2][0] = -points2[20][0] * (cos(rad) - 1) + points2[20][1] * sin(rad);
    trans1[2][1] = -points2[20][1] * (cos(rad) - 1) - points2[20][0] * sin(rad);

}




void DrawNow(HDC hdc) {

    for (int i = 0, j = 0; i < sizeof(points2) / 4 / 3; i++) {

        if (points2[i][2] == 1) { LineTo(hdc, points2[i][j], points2[i][j + 1]); }
        else { MoveToEx(hdc, points2[i][j], points2[i][j + 1], NULL); }

    }


}



float n, m = 0;
void transformation(float point[20][3], float trans[3][3]) {

    for (int i = 0; i < 21; i++) {
        n = point[i][0], m = point[i][1];
        point[i][0] = trans[0][0] * n + trans[1][0] * m + trans[2][0];
        point[i][1] = trans[0][1] * n + trans[1][1] * m + trans[2][1];
        if (point[i][2] != 0) {
            point[i][2] = trans[0][2] * n + trans[1][2] * m + trans[2][2];
        }
        
    }

};

void Re() {

    for (int i = 0; i < 21; i++) {
        for (int j = 0; j < 3; j++) {
            points2[i][j] = Zero[i][j];
        }
    }

};



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

    raschet();
    rerun(moveup, moveright, moveleft, movedown);
    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB1));

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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

    ShowWindow(hWnd, nCmdShow);
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
    case WM_CREATE:
    {   //Кнопка вернуть
        HWND button = CreateWindow(L"button", L"Вернуть самолет", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            420, 500, 140, 30, hWnd, reinterpret_cast<HMENU>(1), NULL, NULL);
        //Кнопка сдвинуть вверх
        HWND button1 = CreateWindow(L"button", L"Сдвинуть вверх", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            560, 500, 140, 30, hWnd, reinterpret_cast<HMENU>(22), NULL, NULL);
        //Кнопка сдвинуть вправо
        HWND button2 = CreateWindow(L"button", L"Cдвинуть вправо", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            690, 500, 140, 30, hWnd, reinterpret_cast<HMENU>(26), NULL, NULL);
        //Кнопка сдвинуть вниз
        HWND button3 = CreateWindow(L"button", L"Cдвинуть вниз", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            690, 530, 140, 30, hWnd, reinterpret_cast<HMENU>(28), NULL, NULL);
        //Кнопка сдвинуть вниз
        HWND button4 = CreateWindow(L"button", L"Cдвинуть влево", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            690, 560, 140, 30, hWnd, reinterpret_cast<HMENU>(29), NULL, NULL);
        //Кнопка повернуть на 300 градусов
        HWND button5 = CreateWindow(L"button", L"Повернуть на 110 градусов", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            420, 530, 280, 30, hWnd, reinterpret_cast<HMENU>(33), NULL, NULL);
        //Кнопка отразить по X
        HWND button6 = CreateWindow(L"button", L"Отразить", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            420, 560, 280, 30, hWnd, reinterpret_cast<HMENU>(44), NULL, NULL);

    }
    break;

    case WM_COMMAND:
    {

        switch (LOWORD(wParam)) {
            //Действие кнопки с id 1
        case 1:
            Re();
            raschet();
            rerun2(rotate);
            InvalidateRect(hWnd, NULL, 1);
            UpdateWindow(hWnd);
            break;
            //Действие кнопки с id 22
        case 22:
            transformation(points2, moveup);
            InvalidateRect(hWnd, NULL, 1);
            break;
            //Действие кнопки с id 26
        case 26:
            transformation(points2, moveright);
            InvalidateRect(hWnd, NULL, 1);
            break;
            //Действие кнопки с id 28
        case 28:
            transformation(points2, movedown);
            InvalidateRect(hWnd, NULL, 1);
            break;
            //Действие кнопки с id 29
        case 29:
            transformation(points2, moveleft);
            InvalidateRect(hWnd, NULL, 1);
            break;
            //Действие кнопки с id 33
        case 33:
            rerun2(rotate);
            transformation(points2, rotate);
            InvalidateRect(hWnd, NULL, 1);
            break;
            //Действие кнопки с id 44
        case 44:
            transformation(points2, otr);
            InvalidateRect(hWnd, NULL, 1);
            break;
        default:
            break;
        }

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
       
       
        DrawNow(hdc);
       
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
