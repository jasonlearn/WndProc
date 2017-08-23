#include <tchar.h>

LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

struct tagWNDPROC2
{
	int			count;
	TCHAR*		msg;
	COLORREF	colour;
};
tagWNDPROC2;