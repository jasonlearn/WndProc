#include <windows.h>
#include "WndProc1.h"
#include "WndProc2.h"

LRESULT CALLBACK WndProc1(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;
	tagWNDPROC1 *wnd1 = (tagWNDPROC1*)(GetWindowLongPtr(hwnd, 0));
	tagWNDPROC2 *cls = (tagWNDPROC2*)(GetClassLongPtr(hwnd, 0));

	switch (message)
	{
	case WM_CREATE://additional things to do when window is created
		PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (((LPCREATESTRUCT)lParam)->lpCreateParams != NULL) {
			SetClassLongPtr(hwnd, 0, (LONG)((LPCREATESTRUCT)lParam)->lpCreateParams);
		}
		cls = ((tagWNDPROC2 *)GetClassLongPtr(hwnd, 0));
		cls -> count++;
		return 0;

	case WM_PAINT: //what to do when a paint msg occurs.  This message is forced when the windows is "dirty" so it repaints
		hdc = BeginPaint(hwnd, &ps); //Validates your window if.  Get a handle to a device, can only be used in WM_PAINT

		GetClientRect(hwnd, &rect); //define drawing area for window
		
		TCHAR b[64];
		wsprintf(b, TEXT("number windows %d"), cls->count);
		SetTextColor(hdc, cls->colour);
		DrawText(hdc, b, -1, &rect,
			DT_SINGLELINE | DT_TOP | DT_LEFT);

		SetTextColor(hdc, wnd1->colour);
		DrawText(hdc, wnd1->msg, -1, &rect,		//-1 where to end the message
													//&rect draws in GetClientRect
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);	//DT_SINGLELING - displays message in one line
														//DT_CENTER & DE_VCENTER - centers vertically and horizontally
		
		EndPaint(hwnd, &ps); //release the device context
		return 0;

	case WM_DESTROY: //how to handle a destroy (close window)
		if (cls->count == 1) {
			PostQuitMessage(0);
		}
		cls->count--;
		return 0;
	}

	//return the message to windows for further processing
	return DefWindowProc(hwnd, message, wParam, lParam); //If you call this, windows will not redraw.
}