#include <windows.h>
#include <wininet.h>
#if defined __MINGW_H
#define _WIN32_IE 0x0400
#endif
#include <commctrl.h>
#include <direct.h>
#include <stdio.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
char *szClassName = TEXT("WindowsApp");
HWND window = NULL;
HWND pButton = NULL, nButton = NULL, title = NULL;
HBITMAP background = NULL;
HWND status = NULL;

BOOL MessageLoop(BOOL blocking) {
    MSG messages;

    if (!(blocking ? 
        GetMessage(&messages, NULL, 0, 0) :
        PeekMessage(&messages, NULL, 0, 0, PM_REMOVE)
    ))
        return FALSE;

    TranslateMessage(&messages);
    DispatchMessage(&messages);

    return TRUE;
}

#define MAX_PAGES 4
int curpage = 0;

LPCSTR TitleForPage(int page) {
	switch (page) {
		case 0: {
			return TEXT("Welcome");
		} case 1: {
			return TEXT("Enter DFU Mode");
		} case 2: {
			return TEXT("Jailbreaking...");
		} case 3: {
			return TEXT("Complete");
		} default: {
			return TEXT("Unknown Page");
		}
	}
}

UINT dfutimer = 0;
int dfuphase = 0;
int dfucountdown = 0;
HWND reset = NULL, counter = NULL, progress = NULL;
LPCSTR dfutext[] = {
	"Get ready to enter DFU.",
	"Hold the power button.",
	"Hold the power and home buttons.",
	"Hold the home button."
};

#define DFU_PHASE_READY 0
#define DFU_PHASE_POWER 1
#define DFU_PHASE_BOTH 2
#define DFU_PHASE_HOME 3
#define TIMER_ID 1337

BOOL DeviceInDFU() 
{
	return FALSE;
}

void UpdateDFUStatusText()
{
	char text[0x400];
	strcpy(text, "\r\n");
	
	for (int i = 0; i < (sizeof(dfutext) / sizeof(LPCSTR)); i++) {
		if (i == dfuphase) strcat(text, ">> ");
		strcat(text, dfutext[i]);
		if (i == dfuphase) strcat(text, " <<");
		strcat(text, "\r\n\r\n");
	}
	
	SendMessage(status, WM_SETTEXT, 0, (LPARAM)text);
	
	strcpy(text, "");
	sprintf(text, "%ds", dfucountdown);
	
	SendMessage(counter, WM_SETTEXT, 0, (LPARAM)text);
}

void DestroyPage()
{
	MoveWindow(status, 350/2, 105, 350, 195, TRUE);
	EnableWindow(nButton, TRUE);
	
	if (reset) {
		DestroyWindow(reset); 
		reset = NULL; 
	}
	
	if (counter) {
		DestroyWindow(counter);
		counter = NULL;
	}
	
	if (progress) {
		DestroyWindow(progress);
		progress = NULL;
	}
	
	if (dfutimer) {
		KillTimer(window, dfutimer);
		dfutimer = 0;
		dfuphase = 0;
		dfucountdown = 0;
	}
}

void DisplayCurrentPage() 
{
	ShowWindow(pButton, curpage == 0 ? SW_HIDE : SW_SHOW);
	if (curpage == MAX_PAGES - 1) SendMessage(nButton, WM_SETTEXT, 0, (LPARAM)TEXT("Finish"));
	else SendMessage(nButton, WM_SETTEXT, 0, (LPARAM)TEXT("Continue"));
	
	SendMessage(title, WM_SETTEXT, 0, (LPARAM)TitleForPage(curpage));
	SendMessage(status, WM_SETTEXT, 0, (LPARAM)TEXT(""));
	
	switch (curpage) {
		case 0: {
			// Status label
			LPCSTR text = 
				"In development for almost a\r\n"
				"year, greenpois0n is the most\r\n"
				"advanced jailbreak tool yet.\r\n\r\n\r\n"
				"Please power down your device, then\r\n"
				"click continue below to begin.\r\n\r\n\r\n"
				"Jailbreak by posixninja, pod2g,\r\n"
				"Jaywalker, chronic, AriX, ius, nikias,\r\n"
				"and the rest of the chronic-dev team.\r\n"
				"GUI is by chpwn."; 
			SendMessage(status, WM_SETTEXT, 0, (LPARAM)text);
			
			break;
		} case 1: {
			dfucountdown = 5;
			dfuphase = DFU_PHASE_READY;
			dfutimer = SetTimer(window, TIMER_ID, /* one second: */ 1000, NULL);
			reset = CreateWindowEx(0, TEXT("BUTTON"), TEXT("Try Again"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD, 305, 300, 85, 25, window, (HMENU) 3, NULL, NULL);
		    SendMessage(reset, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), FALSE);    
		
			counter = CreateWindowEx(0, TEXT("STATIC"), TEXT(""), WS_VISIBLE | WS_CHILD | SS_CENTER, 350/2, 103, 350, 45, window, NULL, NULL, NULL);
		    SendMessage(counter, WM_SETFONT, (WPARAM) CreateFont(40, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Tahoma")), TRUE);
			
			MoveWindow(status, 350/2, 150, 350, 150, TRUE);
			//EnableWindow(nButton, FALSE);
			UpdateDFUStatusText();
						
			break;
		} case 2: {
			EnableWindow(nButton, FALSE);
			EnableWindow(pButton, FALSE);
			
			MoveWindow(status, 400/2, 150, 300, 25, TRUE);
			
			progress = CreateWindowEx(0, PROGRESS_CLASS, (LPTSTR) NULL, PBS_SMOOTH | WS_CHILD | WS_VISIBLE, 400/2, 175, 300, 25, window, NULL, NULL, NULL);
			InvalidateRect(window, NULL, FALSE);
			UpdateWindow(window);
			SendMessage(progress, PBM_SETBKCOLOR, 0, 0x00000000);
			SendMessage(progress, PBM_SETBARCOLOR, 0, 0x0000ff00);
			SendMessage(progress, PBM_SETRANGE, 0, MAKELPARAM(0, 5));
			SendMessage(progress, PBM_SETPOS, 0, 0);
			
			SendMessage(status, WM_SETTEXT, 0, (LPARAM) TEXT("Preparing jailbreak..."));
			SendMessage(progress, PBM_SETPOS, 1, 0);
			Sleep(1000);
			
			SendMessage(status, WM_SETTEXT, 0, (LPARAM) TEXT("Sending exploit..."));
			SendMessage(progress, PBM_SETPOS, 2, 0);
			Sleep(3000);
			
			SendMessage(status, WM_SETTEXT, 0, (LPARAM) TEXT("Uploading ramdisk..."));
			SendMessage(progress, PBM_SETPOS, 3, 0);
			Sleep(6000);
			
			SendMessage(status, WM_SETTEXT, 0, (LPARAM) TEXT("Jailbreaking..."));
			SendMessage(progress, PBM_SETPOS, 4, 0);
			Sleep(4000);
			
			SendMessage(status, WM_SETTEXT, 0, (LPARAM) TEXT("Completing jailbreak..."));
			SendMessage(progress, PBM_SETPOS, 5, 0);
			Sleep(1000);
			
			SendMessage(status, WM_SETTEXT, 0, (LPARAM) TEXT("Jailbreak complete!"));
			
			EnableWindow(nButton, TRUE);
			EnableWindow(pButton, FALSE);
			
			break;
		} case 3: {
			EnableWindow(nButton, TRUE);
			EnableWindow(pButton, FALSE);
			
			// Status label
			LPCSTR text = 
				"Your device will reboot jailbroken.\r\n"
				"Open the pois0n application that appears\r\n"
				"to get started.\r\n\r\n\r\n"
				"We hope you enjoyed this jailbreak,\r\n"
				"and look forward to helping you free\r\n"
				"your device again in the future.\r\n\r\n\r\n"
				">> chronic dev team <<\r\n"
				"Website: http://chronic-dev.org/\r\n"
				"Donations: http://chronic-dev.org/donate\r\n"; 
			SendMessage(status, WM_SETTEXT, 0, (LPARAM) text);
			
			break;
		} default: {
			
			break;
		}
	}
}

void NextPage() {
	if (curpage < MAX_PAGES - 1) curpage += 1;
	else PostQuitMessage(0);
	DestroyPage();
	DisplayCurrentPage();
}

void PreviousPage() {
	if (curpage > 0) curpage -= 1;
	DestroyPage();
	DisplayCurrentPage();
}

void ReloadPage() {
	DestroyPage();
	DisplayCurrentPage();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{   
    // Register window class
    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WindowProcedure;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(GetModuleHandle(NULL), TEXT("ID"));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_BTNFACE + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;
    wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), TEXT("ID"), IMAGE_ICON, 16, 16, 0);
    if(!RegisterClassEx(&wc)) return 0;

	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC  = ICC_PROGRESS_CLASS;
	InitCommonControlsEx(&icex);

	// Load background image
	background = (HBITMAP)LoadImage(GetModuleHandle(NULL), TEXT("back"), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

    // Create the window
    window = CreateWindowEx(0, szClassName, TEXT("greenpois0n"), WS_OVERLAPPED | WS_SYSMENU | SS_OWNERDRAW, CW_USEDEFAULT, CW_USEDEFAULT, 652 + GetSystemMetrics(SM_CXFIXEDFRAME), 397 + GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION), HWND_DESKTOP, NULL, hInstance, NULL);

	// Next button
	nButton = CreateWindowEx(0, TEXT("BUTTON"), TEXT("Continue"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD, 420, 300, 85, 25, window, (HMENU) 1, NULL, NULL);
	SendMessage(nButton, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), FALSE);    

	// Previous button
	pButton = CreateWindowEx(0, TEXT("BUTTON"), TEXT("Back"), BS_PUSHBUTTON | WS_VISIBLE | WS_CHILD, 190, 300, 85, 25, window, (HMENU) 2, NULL, NULL);
	SendMessage(pButton, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), FALSE);       

	// Title
	title = CreateWindowEx(0, TEXT("STATIC"), TEXT(""), WS_VISIBLE | WS_CHILD | SS_CENTER, 350/2, 65, 350, 25, window, NULL, NULL, NULL);
    SendMessage(title, WM_SETFONT, (WPARAM) CreateFont(25, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Tahoma")), TRUE);

	// Status label
	status = CreateWindowEx(0, TEXT("STATIC"), TEXT(""), WS_VISIBLE | WS_CHILD | SS_CENTER, 350/2, 105, 350, 195, window, NULL, NULL, NULL);
	SendMessage(status, WM_SETFONT, (WPARAM) CreateFont(14, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Tahoma")), TRUE);

	ReloadPage();

    // Show the window
    ShowWindow(window, nFunsterStil);
    
    // Run the main runloop.
    while(MessageLoop(TRUE));

    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND: {	
	    if (LOWORD(wParam) == 1) {
			NextPage();
	    } else if (LOWORD(wParam) == 2) {
			PreviousPage();
	    } else if (LOWORD(wParam) == 3) {
			ReloadPage();
		}
        
        break;
    } case WM_DESTROY: {
        PostQuitMessage(0);
            
        break;
	} case WM_PAINT: {
		BITMAP bm;
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(hwnd, &ps);

		HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP hbmOld = SelectObject(hdcMem, background);

		GetObject(background, sizeof(bm), &bm);

		BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, hbmOld);
		DeleteDC(hdcMem);

		EndPaint(hwnd, &ps);
		
		break;
	} case WM_CTLCOLORSTATIC: {
		HDC hdcStatic = (HDC) wParam;

		SetTextColor(hdcStatic, RGB(255, 255, 255));
		SetBkColor(hdcStatic, RGB(0, 0, 0));
		return (INT_PTR)CreateSolidBrush(RGB(0, 0, 0));
		
		break;
	} case WM_TIMER: {
		if (wParam == TIMER_ID) {
			dfucountdown -= 1;
			
			if (DeviceInDFU()) {
				EnableWindow(nButton, TRUE);
				SendMessage(counter, WM_SETTEXT, 0, (LPARAM)TEXT("Ready to jailbreak."));
				break;
			}
			
			if (dfucountdown <= 0) {
				if (dfuphase == DFU_PHASE_HOME) {
					SendMessage(counter, WM_SETTEXT, 0, (LPARAM)TEXT("Please try again."));
					break;
				} else {
					dfuphase += 1;
					if (dfuphase == DFU_PHASE_POWER) {
						dfucountdown = 2;
					} else if (dfuphase == DFU_PHASE_BOTH) {
						dfucountdown = 10;
					} else if (dfuphase == DFU_PHASE_HOME) {
						dfucountdown = 30;
					}
				}
			}
			
			UpdateDFUStatusText();
			
			return 0;
		}
	} default: 
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
