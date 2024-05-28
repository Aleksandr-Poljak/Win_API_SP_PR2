#include <Windows.h>
#include <tchar.h>

//Прототип
LRESULT CALLBACK Pr2_WndProc(HWND, UINT, WPARAM, LPARAM);

// Имя класса окна
LPCTSTR g_lpszClassName = TEXT("sp_pr2_class"); 
// Заголовок окна
LPCTSTR g_lpszAplicationTitle = TEXT("Главное окно приложения. Програмист <Поляк А.>");
// Выводится в сообщении о закрытии окна
LPCTSTR g_lpszDestroyMessage = TEXT("Поступило сообщение WM_DESTROY, из обработчика которого\
	и выполнен данный вывод. Сообщение поступило в связи с разрушение мокна приложения");

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
		MessageBox(NULL, TEXT("Ошибка регистрации окна"), 
			TEXT("Ошибка!"), MB_OK | MB_ICONERROR);
		return false;
	}

	hWnd = CreateWindowEx(NULL, g_lpszClassName,
		g_lpszAplicationTitle,
		WS_OVERLAPPEDWINDOW,
		200, // X положение (X)
		200, // Y положение (Y)
		450, // Ширина (nWidth)
		450, // Высота (nHeight)
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL, TEXT("Окно не создано!"),
			TEXT("Ошибка при создании окна"), MB_OK | MB_ICONERROR);
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

	HDC hdc; // Дескриптор контекста устройства.

	LPCTSTR lpszMessage = TEXT("Обработка сообщения WM_LBUTTONDOWN,\n которое посылается \
				в окно при щелчке левой кнопки мыши");
	TCHAR messageFormat[200];
	wsprintf(messageFormat, lpszMessage);

	int xPos = LOWORD(lParam); // Получаем x-координату
	int yPos = HIWORD(lParam); // Получаем y-координату
	RECT rt{ xPos, yPos, xPos + 200, yPos + 50 }; // Создаем прямоугольник для текста;

	switch (msg) {
		case WM_DESTROY:
			//MessageBox(NULL, g_lpszDestroyMessage, TEXT("Окно закрыто"), MB_OK);
			PostQuitMessage(5);
			break;
		// Вывод сообщения при  клике левой кнопкой мыши по координатам мыши
		case WM_LBUTTONDOWN:	
			hdc = GetDC(hWnd);
			DrawText(hdc, messageFormat, lstrlen(messageFormat), &rt, DT_LEFT | DT_TOP | DT_WORDBREAK);
			ReleaseDC(hWnd, hdc);
			break;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return false;
}
