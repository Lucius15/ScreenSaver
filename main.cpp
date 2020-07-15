
#define _WIN32_WINNT 0x0501

#include <windows.h>
#include <time.h>

#include "sources\\ScreenSaverShell\Shell.h"
#include "sources\\MatrixScreenSaver\\graphics\\graphics.h"
//#include "sources\\MatrixScreenSaver\\sound\\sound.h"

HWND				   hWnd;
HDC						hdc;
HINSTANCE 		  hInstance; 
PAINTSTRUCT 	paintstruct;
int 	   Horzres, Vertres;
int 			*Parameters;


void MainEventThread() // События программы
{
	Sleep(2000);

	graphics::GreenTextEvent(&hdc, &Horzres, &Vertres, &Parameters[3]);
	
	while(true)
	{
		srand(time(NULL));
		int chance = rand() % 5;
		
		switch(chance)
		{
			case 1:
			{
				graphics::NeoEvent(&hdc, &Horzres, &Vertres, &Parameters[5]);

				break;
			}
			case 2:
			{
				graphics::RandomLettersEvent(&hdc, &Horzres, &Vertres, &Parameters[4], &Parameters[5]);

				break;
			}
			default:
			{
				graphics::GreenTextEvent(&hdc, &Horzres, &Vertres, &Parameters[3]);
				
				break;
			}
		}	
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // Ф-я обработки сообщений от ОС             
{
	SetCursorPos(Horzres-15, Vertres-25);
	
	switch(message)
	{
		case  WM_CREATE:
		{
			Parameters = shell::LoadConfig();
			int Error = shell::CheckConfigValues(Parameters);

			if(Error)
			{
				char buf, error_message[100] = {"There's an error in the "};
				itoa((Error+1), &buf, 10);
				strcat(error_message, &buf);
				strcat(error_message, " config.txt line. Please correct it.");
				MessageBox(hWnd, error_message, 0, 0);
				PostQuitMessage(0);
			}

			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainEventThread, 0, 0, 0);
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
				
			break;
		}
		
		case WM_PAINT:
		{
			graphics::InitPaint(&hWnd, &hdc, &paintstruct);
			
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
	
	hWnd = CreateWindow("ScreenSaver", "Calculating...", WS_OVERLAPPEDWINDOW | WS_MAXIMIZE, 0, 0, Horzres, Vertres, NULL, NULL, hInstance, NULL); // Создание окна
	                   
	if(!hWnd) return 0;
	
	SetWindowLong(hWnd,GWL_STYLE,WS_POPUP);
    SetWindowLong(hWnd,GWL_EXSTYLE,WS_EX_TOPMOST);

    SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	SetLayeredWindowAttributes(hWnd, 0, Parameters[2], LWA_ALPHA);

	ShowWindow(hWnd, SW_SHOWMAXIMIZED);
	UpdateWindow(hWnd);

	hdc = GetDC(hWnd);
	Horzres = GetDeviceCaps(hdc, HORZRES);
	Vertres = GetDeviceCaps(hdc, VERTRES);								  									   								   

	while(GetMessage(&msg,0,0,0)) // Цикл обработки сообщений
	{	
		  TranslateMessage(&msg);
		  DispatchMessage (&msg);
	} 

	return msg.wParam;
}
