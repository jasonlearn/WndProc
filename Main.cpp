/*------------------------------------------------------------
HELLOWIN.C -- Displays "Hello, Windows 98!" in client area
(c) Charles Petzold, 1998
------------------------------------------------------------*/

#include <windows.h>
#include "Main.h"
#include "WndProc1.h"
#include "WndProc2.h"

LRESULT CALLBACK HelloWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
	//iCmdShow - how you want to show it, size of the console
	
{
	static TCHAR szAppName[] = TEXT("HelloWin"); //name of the app
	static TCHAR szAppName2[] = TEXT("HelloWin2"); //name of the app

	//window class 1
	HWND         hwnd; //holds handle to the main window, better than pointer because memory changes. (pointers only points to references)
	MSG          msg; //holds any message retrieved from the msg queue
	WNDCLASS     wndclass; //wnd class for registration

	//window class 2
	HWND         hwnd2;
	MSG          msg2;
	WNDCLASS     wndclass2;

	tagWNDPROC1* wnd1;
	tagWNDPROC2* wnd2;

	int xsize = 400;
	int ysize = 200;

						   //defn wndclass attributes for this application
	wndclass.style = CS_HREDRAW | CS_VREDRAW; //redraw on refresh
	wndclass.lpfnWndProc = WndProc1; //lpf(long pointer function) wnd proc to handle window

										 //extra bytes you can put in
	wndclass.cbClsExtra = sizeof(*wnd1); //class space for expansion/info
	wndclass.cbWndExtra = sizeof(*wnd1); //wnd apce for info carrying

	wndclass.hInstance = hInstance; //application instance handle
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //set icon
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); //set current cursor
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //set background
	wndclass.lpszMenuName = NULL; //set menu
	wndclass.lpszClassName = szAppName; //set application name

	//wndclass2
										//defn wndclass attributes for this application
	wndclass2.style = CS_HREDRAW | CS_VREDRAW; //redraw on refresh
	wndclass2.lpfnWndProc = WndProc2; //lpf(long pointer function) wnd proc to handle window

									 //extra bytes you can put in
	wndclass2.cbClsExtra = sizeof(*wnd2); //class space for expansion/info
	wndclass2.cbWndExtra = sizeof(*wnd2); //wnd apce for info carrying

	wndclass2.hInstance = hInstance; //application instance handle
	wndclass2.hIcon = LoadIcon(NULL, IDI_APPLICATION); //set icon
	wndclass2.hCursor = LoadCursor(NULL, IDC_ARROW); //set current cursor
	wndclass2.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //set background
	wndclass2.lpszMenuName = NULL; //set menu
	wndclass2.lpszClassName = szAppName2; //set application name

										//register wndclass to O/S so approp. wnd msg are set to application
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR); //if unable to be retreived
		return 0;
	}

	if (!RegisterClass(&wndclass2))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName2, MB_ICONERROR); //if unable to be retreived
		return 0;
	}

	//class 1 window 1

	wnd1 = (tagWNDPROC1*)malloc(sizeof(struct tagWNDPROC1));
	wnd1 -> msg = TEXT("Hello!");
	wnd1->colour = RGB(255, 0, 0);

	wnd2 = (tagWNDPROC2*)malloc(sizeof(struct tagWNDPROC2));
	wnd2->count = 0;
	wnd2->colour = RGB(0, 0, 255);

	//create the main window and get it's handle for future reference
	hwnd = CreateWindow(szAppName,                  // window class name
		TEXT("Hello World for Windows"), // window caption
		WS_OVERLAPPEDWINDOW,        // window style

									//window position
		0,              // initial x position
		0,              // initial y position
		xsize,              // initial x size
		ysize,              // initial y size
									//if owned by another window
		NULL,                       // parent window handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		wnd2);                     // creation parameters

	SetWindowLongPtr(hwnd, 0, (long)wnd1);

	ShowWindow(hwnd, iCmdShow); //set window to be shown
	UpdateWindow(hwnd); //force an update so window is drawn

	//class 1 window 2
	wnd1 = (tagWNDPROC1*)malloc(sizeof(struct tagWNDPROC1));
	wnd1->msg = TEXT("GoodBye!");
	wnd1->colour = RGB(0, 0, 255);

	hwnd = CreateWindow(szAppName,                  // window class name
		TEXT("Hello World for Windows"), // window caption
		WS_OVERLAPPEDWINDOW,        // window style

									//window position
		400,              // initial x position
		0,              // initial y position
		xsize,              // initial x size
		ysize,              // initial y size
									//if owned by another window
		NULL,                       // parent window handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		NULL);                     // creation parameters

	SetWindowLongPtr(hwnd, 0, (long)wnd1);

	ShowWindow(hwnd, iCmdShow); //set window to be shown
	UpdateWindow(hwnd); //force an update so window is drawn

	//class 2 window 1
	wnd1 = (tagWNDPROC1*)malloc(sizeof(struct tagWNDPROC1));
	
	wnd1->msg = TEXT("Hello Windows!");
	wnd1->colour = RGB(0, 0, 0);

	wnd2 = (tagWNDPROC2*)malloc(sizeof(struct tagWNDPROC2));
	wnd2->count = 0;
	wnd2->colour = RGB(255, 0, 255);

	hwnd2 = CreateWindow(szAppName2,                  // window class name
		TEXT("Hello World for Windows"), // window caption
		WS_OVERLAPPEDWINDOW,        // window style

									//window position
		0,              // initial x position
		200,              // initial y position
		xsize,              // initial x size
		ysize,              // initial y size
							//if owned by another window
		NULL,                       // parent window handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		wnd2);                     // creation parameters

	SetWindowLongPtr(hwnd2, 0, (long)wnd1);

	ShowWindow(hwnd2, iCmdShow); //set window to be shown
	UpdateWindow(hwnd2); //force an update so window is drawn

	//class 2 window 2
	wnd1 = (tagWNDPROC1*)malloc(sizeof(struct tagWNDPROC1));
	wnd1->msg = TEXT("Hello Windows!");
	wnd1->colour = RGB(0, 0, 0);

	hwnd2 = CreateWindow(szAppName2,                  // window class name
		TEXT("Hello World for Windows"), // window caption
		WS_OVERLAPPEDWINDOW,        // window style

									//window position
		400,              // initial x position
		200,              // initial y position
		xsize,              // initial x size
		ysize,              // initial y size
							//if owned by another window
		NULL,                       // parent window handle
		NULL,                       // window menu handle
		hInstance,                  // program instance handle
		NULL);                     // creation parameters

	SetWindowLongPtr(hwnd2, 0, (long)wnd1);

	ShowWindow(hwnd2, iCmdShow); //set window to be shown
	UpdateWindow(hwnd2); //force an update so window is drawn

						//message loop
	while (GetMessage(&msg, NULL, 0, 0)) //get message for queue
	{
		TranslateMessage(&msg); //for keystroke tanslation
		DispatchMessage(&msg); //pass msg back to windows for program
							   //note that this is to put windows o/s in control, rather
	}
	return msg.wParam; //returns an integer as required

	while (GetMessage(&msg2, NULL, 0, 0)) //get message for queue
	{
		TranslateMessage(&msg2); //for keystroke tanslation
		DispatchMessage(&msg2); //pass msg back to windows for program
							   //note that this is to put windows o/s in control, rather
	}
	return msg2.wParam; //returns an integer as required
}