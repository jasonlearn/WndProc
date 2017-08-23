#include <tchar.h>

LRESULT CALLBACK WndProc1(HWND, UINT, WPARAM, LPARAM);

struct tagWNDPROC1
{
	int			count;
	TCHAR*		msg;
	COLORREF	colour;
}; 
tagWNDPROC1;
