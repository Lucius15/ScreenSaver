
#define _WIN32_WINNT 0x0501

#include <windows.h>
#include <time.h>
#include <conio.h>

#include "sources\\ScreenSaverShell\shell.h"
#include "sources\\MatrixScreenSaver\\threads.h"


HWND				  			     hWnd;
HDC									  hdc;
HINSTANCE 		  			    hInstance; 
PAINTSTRUCT 				  paintstruct;
int 	   				 Horzres, Vertres;
int 	   		 			  *Parameters;
bool 		  isScreenSaverActive = false;
graphics::GraphicsThreadParam ThreadParam;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // Processing system messsges           
{
	SetCursorPos(Horzres-15, Vertres-25);
	
	switch(message)
	{
		case  WM_CREATE:
		{
			Parameters = shell::LoadConfig();
			int Error = shell::CheckConfigValues(Parameters);

			if(Error != 0)
			{
				if(Error == -1)
				{
					MessageBox(hWnd, "File config.txt is missing or corrupted!", "Critical error", 0);
				}
				else
				{
					char buf, error_message[100] = {"There's an error in the "};
					itoa((Error+1), &buf, 10);
					strcat(error_message, &buf); 
					strcat(error_message, " config.txt line. Please, correct it.");
					MessageBox(hWnd, error_message, "Config error", 0);
				}

				PostQuitMessage(0);
			}

			hdc = GetDC(hWnd);
			Horzres = GetDeviceCaps(hdc, HORZRES);
			Vertres = GetDeviceCaps(hdc, VERTRES);

			ThreadParam.hdc = hdc;
			ThreadParam.Horzres = Horzres;
			ThreadParam.Vertres = Vertres;
			ThreadParam.Parameters = Parameters;

			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)thread::GraphicsEventThread, reinterpret_cast<LPVOID>(&ThreadParam), 0, 0);
			//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainSoundThread, 0, 0, 0);
			break;                                
		}
		
		case WM_KEYDOWN:
		{
			if(wParam == VK_ESCAPE)
			{
				EndPaint(hWnd, &paintstruct);
				PostQuitMessage(0);
			}
			else if(wParam == VK_TAB)
			{
				EndPaint(hWnd, &paintstruct);
				system("start ScreenSaver.exe");
				PostQuitMessage(0);
			}
				
			break;
		}
		
		case WM_PAINT:
		{
			graphics::InitPaint(hWnd, hdc, &paintstruct);
			
			break;
		}

	    case WM_DESTROY:
		{
			EndPaint(hWnd, &paintstruct);
			PostQuitMessage(0);
			                
			break;
		}
		 	 			   
		default:
		{    	   
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
	}
	
	SetCursorPos(Horzres - 25, Vertres - 25);
	
	return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmd, int nCmdShow) 
{
	
	MSG msg;              
	WNDCLASS WndClass;      
			 WndClass.style         = 0;
			 WndClass.lpfnWndProc   = WndProc;
			 WndClass.cbClsExtra    = 0;
			 WndClass.cbWndExtra    = 0;
			 WndClass.hInstance     = hInstance;
			 WndClass.hIcon		    = 0;//LoadIcon(hInstance, "MYICON");
			 WndClass.hCursor	    = LoadCursor(NULL, IDC_ARROW);         
			 WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); 
			 WndClass.lpszMenuName  = 0;
			 WndClass.lpszClassName = "ScreenSaver";

	if(!RegisterClass(&WndClass)) return 0;

	shell::CheckForActivity();
	
	hWnd = CreateWindow("ScreenSaver", "Calculating...", WS_OVERLAPPEDWINDOW | WS_MAXIMIZE, 0, 0, Horzres, Vertres, NULL, NULL, hInstance, NULL); // Window creation
	                   
	if(!hWnd) return 0;

	SetWindowLong(hWnd, GWL_STYLE,        WS_POPUP);
    SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_TOPMOST);

    SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hWnd, 0, Parameters[3], LWA_ALPHA);

	ShowWindow(hWnd, SW_SHOWMAXIMIZED);

	UpdateWindow(hWnd);
	SetFocus(hWnd);							  									   								   

	while(GetMessage(&msg,0,0,0)) // Message processing cycle
	{	
		  TranslateMessage(&msg);
		  DispatchMessage (&msg);
	} 

	return msg.wParam;
}
