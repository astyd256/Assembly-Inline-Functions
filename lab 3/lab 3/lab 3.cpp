
#pragma comment(lib, "d2d1")
#include <windows.h>
#include <math.h>
#include <d2d1.h>


#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;}
#define NUM    1000
#define TWOPI  (2 * 3.14159)

int curFunc = 1;
int curScale = 1;

POINT points[NUM];

ID2D1Factory* g_pD2DFactory = NULL;
ID2D1HwndRenderTarget* g_pRendertarget = NULL;
ID2D1SolidColorBrush* g_pRedBrush = NULL;
ID2D1SolidColorBrush* g_pBlackBrush = NULL;

void CreateD2DResource(HWND hwnd)
{
    if (!g_pRendertarget)
    {
        HRESULT hr;

        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
        if (FAILED(hr))
        {
            MessageBox(hwnd, L"Create D2D factory failed!", L"Error", 0);
            return;
        }

        //Size of the drawing area
        RECT rc;
        GetClientRect(hwnd, &rc);

        //Create render target
        hr = g_pD2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(
                hwnd,
                D2D1::SizeU(rc.right, rc.bottom)
            ),
            &g_pRendertarget
        );

        if (FAILED(hr))
        {
            MessageBox(hwnd, L"Create render target failed!", L"Error", 0);
            return;
        }

        //Create brushes
        hr = g_pRendertarget->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::Red),
            &g_pRedBrush
        );
        if (FAILED(hr))
        {
            MessageBox(hwnd, L"Create red brush failed!", L"Error", 0);
            return;
        }

        hr = g_pRendertarget->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::Black),
            &g_pBlackBrush
        );
        if (FAILED(hr))
        {
            MessageBox(hwnd, L"Create black brush failed!", L"Error", 0);
            return;
        }
    }
}

void ResizeRenderTarget(HWND hwnd)
{
    if (g_pRendertarget != NULL)
    {
        RECT rc;
        GetClientRect(hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        g_pRendertarget->Resize(size);
        InvalidateRect(hwnd, NULL, FALSE);
    }
}

void DrawLines(HWND hwnd, int windowX, int windowY)
{
    CreateD2DResource(hwnd);

    g_pRendertarget->BeginDraw();

    //Clear backgorund
    g_pRendertarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

    //Draw
    for (int i = 1; i < NUM; i++)
    {
        g_pRendertarget->DrawLine(
            D2D1::Point2(points[i - 1].x, points[i - 1].y),
            D2D1::Point2(points[i].x, points[i].y),
            g_pRedBrush
        );
    }

    //Horizontal
    g_pRendertarget->DrawLine(
        D2D1::Point2(0, windowY / 2),
        D2D1::Point2(windowX, windowY / 2),
        g_pBlackBrush
    );
    //Vertical
    g_pRendertarget->DrawLine(
        D2D1::Point2(windowX / 2, 0),
        D2D1::Point2(windowX / 2, windowY),
        g_pBlackBrush
    );


    //End draw
    HRESULT hr = g_pRendertarget->EndDraw();
    if (FAILED(hr))
    {
        MessageBox(hwnd, L"Draw failed!", L"Error", 0);
        return;
    }
}

VOID Cleanup()
{
    SAFE_RELEASE(g_pRendertarget);
    SAFE_RELEASE(g_pRedBrush);
    SAFE_RELEASE(g_pBlackBrush);
    SAFE_RELEASE(g_pD2DFactory);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND hwnd);

HMENU hMenu;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR szCmdLine, int iCmdShow)
{
    HWND         hwnd;
    MSG          msg;
    WNDCLASS     wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = L"FunctionWindow";

    RegisterClass(&wndclass);

    hwnd = CreateWindow(L"FunctionWindow", TEXT("Functions Using Polyline"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int  cxClient, cyClient;
    HDC         hdc;
    int         i;
    PAINTSTRUCT ps;


    switch (message)
    {
    case WM_COMMAND:
        //Register up menu click

        switch (wParam)
        {
        case 1:
            curFunc = 1;
            break;
        case 2:
            curFunc = 2;
            break;
        case 3:
            curFunc = 3;
            break;
        case 4:
            curFunc = 4;
            break;
        case 5:
            curFunc = 5;
            break;
        case 6:
            curFunc = 6;
            break;
        case 7:
            curScale = 1;
            break;
        case 8:
            curScale = 2;
            break;
        case 9:
            curScale = 4;
            break;
        case 10:
            curScale = 8;
            break;
        }

        RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
        return 0;
    case WM_CREATE:
        //Create up menus

        AddMenus(hwnd);

        return 0;
    case WM_SIZE:
        cxClient = LOWORD(lParam);
        cyClient = HIWORD(lParam);
        ResizeRenderTarget(hwnd);
        return 0;

    case WM_PAINT:

        for (i = 0; i < NUM; i++)
        {
            points[i].x = (i * cxClient / NUM);

            switch (curFunc)
            {
            case 1:
                points[i].y = ((int)(cyClient / 2 * (1 - sin(TWOPI * (i - NUM / 2) / NUM * curScale) / curScale)));
                break;
            case 2:
                points[i].y = (int)(cyClient / 2 * (1 - cos(TWOPI * (i - NUM / 2) / NUM * curScale) / curScale));
                break;
            case 3:
                points[i].y = (int)(cyClient / 2 * (1 - tan(TWOPI * (i - NUM / 2) / NUM * curScale) / curScale));
                break;
            case 4:
                points[i].y = (int)(cyClient / 2 * (1 - atan(TWOPI * (i - NUM / 2) / NUM * curScale) / curScale));
                break;
            case 5:
                points[i].y = (int)(cyClient / 2 * (1 - acos(TWOPI * (i - NUM / 2) / NUM * curScale) / curScale));
                break;
            case 6:
                points[i].y = (int)(cyClient / 2 * (1 - asin(TWOPI * (i - NUM / 2) / NUM * curScale) / curScale));
                break;
            }
        }

        DrawLines(hwnd, cxClient, cyClient);

        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

void AddMenus(HWND hwnd)
{
    //Up menu space
    hMenu = CreateMenu();

    //Sub menus
    HMENU hFunctionMenu = CreateMenu();

    AppendMenu(hFunctionMenu, MF_STRING, 1, L"Sin");
    AppendMenu(hFunctionMenu, MF_STRING, 2, L"Cos");
    AppendMenu(hFunctionMenu, MF_STRING, 3, L"Tan");
    AppendMenu(hFunctionMenu, MF_STRING, 4, L"Atan");
    AppendMenu(hFunctionMenu, MF_STRING, 5, L"Acos");
    AppendMenu(hFunctionMenu, MF_STRING, 6, L"Asin");

    HMENU hScaleMenu = CreateMenu();

    AppendMenu(hScaleMenu, MF_STRING, 7, L"1x");
    AppendMenu(hScaleMenu, MF_STRING, 8, L"2x");
    AppendMenu(hScaleMenu, MF_STRING, 9, L"4x");
    AppendMenu(hScaleMenu, MF_STRING, 10, L"8x");


    //Main menus
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFunctionMenu, L"Functions");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hScaleMenu, L"Scale");

    SetMenu(hwnd, hMenu);
}
