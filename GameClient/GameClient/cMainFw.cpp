#include "cMainFw.h"
cMainFw* fw;


LRESULT CALLBACK cMainFw::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000/30, NULL);
		break;
	case WM_PAINT:
		if (fw->getNowScene() != NULL)
		{
			RECT r = { 0,0,fw->getX(), fw->getY() };
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			HDC hmemdc = CreateCompatibleDC(hdc);
			HBITMAP hbmp = CreateCompatibleBitmap(hdc, r.right, r.bottom);
			SelectObject(hmemdc, hbmp);
			FillRect(hmemdc, &r, (HBRUSH)GetStockObject(BLACK_BRUSH));

			fw->getNowScene()->Render(hmemdc);

			BitBlt(hdc, 0, 0, r.right, r.bottom, hmemdc, 0, 0, SRCCOPY);
			EndPaint(hWnd, &ps);
			DeleteObject(hbmp);
			DeleteDC(hmemdc);
			DeleteDC(hdc);
		}
		break;
	case WM_KEYUP:
	case WM_KEYDOWN:
		if (fw->getNowScene() != NULL)
			fw->getNowScene()->KeyBoard(message, wParam, lParam);
		break;
	case WM_CHAR:
		if (fw->getNowScene() != NULL)
			fw->getNowScene()->KeyBoard(message, wParam, lParam);
		break;
	case WM_TIMER:
			if (fw->getNowScene() != NULL)
				fw->getNowScene()->Update();
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_MBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
	case WM_MOUSEWHEEL:
	case WM_MOUSEMOVE:
		if (fw->getNowScene() != NULL)
			fw->getNowScene()->Mouse(message, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (int)wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hWnd, message, wParam, lParam));
}

void cMainFw::CreateWindowns(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	WNDCLASS WndClass;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = name;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);
	RECT	r = { 0,0,x,y };
	AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, false);
	hWnd = CreateWindow(WndClass.lpszClassName, WndClass.lpszClassName, WS_OVERLAPPED,
		CW_USEDEFAULT, CW_USEDEFAULT, r.right - r.left, r.bottom - r.top,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	this->hWnd = hWnd;
	this->hInst = hInstance;
	fw = this;
}
int cMainFw::StartLoop()
{
	MSG Message;
	while (GetMessage(&Message, 0, 0, 0)) {

		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
