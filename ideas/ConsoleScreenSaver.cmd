
// 1  -  Функция обработки сообщений от OS Windows. Сообщения будут поступать от мыши, кнопок, таймера и т.д. и здесь
//       обрабатываться Ваими. 
//
// 2  -  WinMain() - это точка входа в программу, как и функция int main() для MS-DOS (или в консольном приложении)
#include <stdio.h>
#include <windows.h>                       //  Подключаем (заголовочный файл ) типы данных и библиотеки функций WinAPI 
#include <time.h>

HWND             	  hWnd;      			     //  хендл ГЛАВНОГО! окна сделан глобальной переменной и будет виден везде
HDC 				   hdc;  
HINSTANCE        hInstance; 			                          //  Экземпляр этой программы тоже глобально объявлен
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)                   // 1 - смотрите ВЫШЕ.               
{			
	switch(message)
	{
		case  WM_CREATE:
		{
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)WriteRandom, NULL, NULL, NULL);
			break;                                //  Принимаем однократное сообщение для инициализации
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
				PostQuitMessage(0);                //  Принимаем однократное сообщение для ДЕ_инициализации
				break;
		}
		 	 			   
		default:
		{    	   
			return DefWindowProc(hWnd, message, wParam, lParam);    // обработка OS остальных сообщений
			break;
		}
	}
	return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmd, int nCmdShow)     // 2 - смотрите ВЫШЕ. 
{
	
	MSG msg;                                // Создаём элемент структуры сообщений от OS Windows для нашего приложения 
	WNDCLASS WndClass;      // Создаём элемент оконной структуры--- сначала регистрируем класс главного окна программы— 	
			 WndClass.style         = 0;
			 WndClass.lpfnWndProc   = WndProc;                                             // адрес (имя) функции окна
			 WndClass.cbClsExtra    = 0;
			 WndClass.cbWndExtra    = 0;
			 WndClass.hInstance     = hInstance;                                            //   Дескриптор приложения
			 WndClass.hIcon		    = 0;//LoadIcon(hInstance, "MYICON");                         //   Загружаем иконку
			 WndClass.hCursor	    = LoadCursor(NULL, IDC_ARROW);                          //   Загружаем тип курсора 
			 WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);              //   Цвет заливки окна выбрали
			 WndClass.lpszMenuName  = 0;//"xMENU";                                             //   Указываем имя меню 
			 WndClass.lpszClassName = "ScreenSaver";                               //   Придумали сами имя класса окна  

	if(!RegisterClass(&WndClass)) return 0;    // если класс не зарегистрирован, то выходим (программа не запустилась)
	
	HDC hDCScreen = GetDC(NULL);
	Horzres = GetDeviceCaps(hDCScreen, HORZRES);
	Vertres = GetDeviceCaps(hDCScreen, VERTRES);
	ReleaseDC(NULL, hDCScreen);
	
	hWnd = CreateWindow("Screensaver",                  // Создаем окно класса ScreenSaver (имя класса сами придумали)
						"Calculating...",                          // заголовок окна (надпись на верхней-синей полосе)
						WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,                                                             // стиль окна
						0,                                                 // координата X левого верхнего угла окна 
						0,              						             // координата Y левого верхнего угла окна 
						Horzres,                        										   // размеры окна (Ширина)
					    Vertres,                        														 // Высота
					    NULL,                        // Дескриптор родительского окна  ( нет главного окна программы :)
					    NULL,                                     // Дескриптор  меню или идентификатор дочернего окна.
					    hInstance,                                                 // Дескриптор экземпляра приложения
					    NULL);                      
	if(!hWnd) return 0;							        //  если окно не создано, то выходим (программа не запустилась)
	ShowWindow(hWnd, nCmdShow);						                                     //  отобразить окно на экране
	UpdateWindow(hWnd);								                                                 //  обновить окно       								  									   								   

	while(GetMessage(&msg,0,0,0))                                                         //  Цикл обработки сообщений
	{	
		  TranslateMessage(&msg);                                   //  Принятие и "проталкивание" сообщений в очереди
		  DispatchMessage (&msg);
	} 

	return msg.wParam;
}
