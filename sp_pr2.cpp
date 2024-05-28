#include <Windows.h>
#include <tchar.h>

//��������
LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);

// ��� ������ ����
LPCTSTR g_lpszClassName = TEXT("sp_pr2_class"); 
// ��������� ����
LPCTSTR g_lpszAplicationTitle = TEXT("������� ���� ����������. ���������� <����� �.>");
// ��������� � ��������� � �������� ����
LPCTSTR g_lpszDestroyMessage = TEXT("��������� ��������� WM_DESTROY, �� ����������� ��������\
	� �������� ������ �����. ��������� ��������� � ����� � ���������� ����� ����������");

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wc;
	MSG msg;
	HWND hWnd;
	HBRUSH hbr = CreateSolidBrush(RGB(0, 255, 0));

	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = g_lpszClassName;
	wc.lpfnWndProc = Pr2_WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = hbr;
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, TEXT("������ ����������� ����"), 
			TEXT("������!"), MB_OK | MB_ICONERROR);
		return false;
	}

	hWnd = CreateWindowEx(NULL, g_lpszClassName,
		g_lpszAplicationTitle,
		WS_OVERLAPPEDWINDOW,
		200, // X ��������� (X)
		200, // Y ��������� (Y)
		450, // ������ (nWidth)
		450, // ������ (nHeight)
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL, TEXT("���� �� �������!"),
			TEXT("������ ��� �������� ����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);
	}
	return msg.wParam;

}

LRESULT CALLBACK Pr2_WndProc(HWND hWnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {

	switch (msg) {
		case WM_DESTROY:
			MessageBox(NULL, g_lpszDestroyMessage, TEXT("���� �������"), MB_OK);
			PostQuitMessage(5);
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return false;

}
