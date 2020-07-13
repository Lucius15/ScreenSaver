
// 1  -  ������� ��������� ��������� �� OS Windows. ��������� ����� ��������� �� ����, ������, ������� � �.�. � �����
//       �������������� �����. 
//
// 2  -  WinMain() - ��� ����� ����� � ���������, ��� � ������� int main() ��� MS-DOS (��� � ���������� ����������)
#include <stdio.h>
#include <windows.h>                       //  ���������� (������������ ���� ) ���� ������ � ���������� ������� WinAPI 
#include <time.h>

HWND             	  hWnd;      			     //  ����� ��������! ���� ������ ���������� ���������� � ����� ����� �����
HDC 				   hdc;  
HINSTANCE        hInstance; 			                          //  ��������� ���� ��������� ���� ��������� ��������
PAINTSTRUCT    paintstruct;
int Horzres, Vertres;

void WriteRandom()
{
	while(true)
	{
		Sleep(5);
		SetCursorPos(Horzres-25, Vertres-75);
		Sleep(5);
		SetCursorPos(Horzres-50, Vertres-75);
		srand(time(NULL));
		for(int i = 0; i < Vertres/10; i++)
		{
			for(int j = 0; j < Horzres/10; j++)
			{
				char symb;
				symb = (rand() % 255);
				TextOut(hdc, j*10, i*10, &symb, 1);
			}
		}	
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)                   // 1 - �������� ����.               
{			
	switch(message)
	{
		case  WM_CREATE:
		{
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)WriteRandom, NULL, NULL, NULL);
			break;                                //  ��������� ����������� ��������� ��� �������������
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
			hdc = BeginPaint(hWnd, &paintstruct);
			SetTextColor(hdc, RGB(0, 230, 0));
			SetBkColor(hdc, RGB(0, 0, 0));
			break;
		}

	    case WM_DESTROY:
		{
				EndPaint(hWnd, &paintstruct);
				PostQuitMessage(0);                //  ��������� ����������� ��������� ��� ��_�������������
				break;
		}
		 	 			   
		default:
		{    	   
			return DefWindowProc(hWnd, message, wParam, lParam);    // ��������� OS ��������� ���������
			break;
		}
	}
	return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmd, int nCmdShow)     // 2 - �������� ����. 
{
	
	MSG msg;                                // ������ ������� ��������� ��������� �� OS Windows ��� ������ ���������� 
	WNDCLASS WndClass;      // ������ ������� ������� ���������--- ������� ������������ ����� �������� ���� ���������� 	
			 WndClass.style         = 0;
			 WndClass.lpfnWndProc   = WndProc;                                             // ����� (���) ������� ����
			 WndClass.cbClsExtra    = 0;
			 WndClass.cbWndExtra    = 0;
			 WndClass.hInstance     = hInstance;                                            //   ���������� ����������
			 WndClass.hIcon		    = 0;//LoadIcon(hInstance, "MYICON");                         //   ��������� ������
			 WndClass.hCursor	    = LoadCursor(NULL, IDC_ARROW);                          //   ��������� ��� ������� 
			 WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);              //   ���� ������� ���� �������
			 WndClass.lpszMenuName  = 0;//"xMENU";                                             //   ��������� ��� ���� 
			 WndClass.lpszClassName = "ScreenSaver";                               //   ��������� ���� ��� ������ ����  

	if(!RegisterClass(&WndClass)) return 0;    // ���� ����� �� ���������������, �� ������� (��������� �� �����������)
	
	HDC hDCScreen = GetDC(NULL);
	Horzres = GetDeviceCaps(hDCScreen, HORZRES);
	Vertres = GetDeviceCaps(hDCScreen, VERTRES);
	ReleaseDC(NULL, hDCScreen);
	
	hWnd = CreateWindow("Screensaver",                  // ������� ���� ������ ScreenSaver (��� ������ ���� ���������)
						"Calculating...",                          // ��������� ���� (������� �� �������-����� ������)
						WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,                                                             // ����� ����
						0,                                                 // ���������� X ������ �������� ���� ���� 
						0,              						             // ���������� Y ������ �������� ���� ���� 
						Horzres,                        										   // ������� ���� (������)
					    Vertres,                        														 // ������
					    NULL,                        // ���������� ������������� ����  ( ��� �������� ���� ��������� :)
					    NULL,                                     // ����������  ���� ��� ������������� ��������� ����.
					    hInstance,                                                 // ���������� ���������� ����������
					    NULL);                      
	if(!hWnd) return 0;							        //  ���� ���� �� �������, �� ������� (��������� �� �����������)
	ShowWindow(hWnd, nCmdShow);						                                     //  ���������� ���� �� ������
	UpdateWindow(hWnd);								                                                 //  �������� ����       								  									   								   

	while(GetMessage(&msg,0,0,0))                                                         //  ���� ��������� ���������
	{	
		  TranslateMessage(&msg);                                   //  �������� � "�������������" ��������� � �������
		  DispatchMessage (&msg);
	} 

	return msg.wParam;
}
