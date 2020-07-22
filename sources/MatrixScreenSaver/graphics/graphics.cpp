#include <time.h>

#include "graphics.h"

namespace
{

	HPEN Main_pen, Error_pen, Black_pen;
	HBRUSH Main_brush, 		Error_brush;

	namespace color
	{
		int Black = RGB(0,   0, 0);
		int Green = RGB(0, 255, 0);
	}
} // namespace

namespace
{
	void InitHpen()
	{
		Main_pen  = CreatePen(PS_SOLID, 1, color::Green);
		Error_pen = CreatePen(PS_SOLID, 1, color::Green);
		Black_pen = CreatePen(PS_SOLID, 1, color::Black);
	}


	void InitHbrush()
	{
		Main_brush  = CreateSolidBrush(color::Black);
		Error_brush = CreateSolidBrush(color::Green);
	}
	
	
	void WriteNeoMessage(HDC hdc, int Horzres, int Vertres) // Message to Neo 
	{
		SetTextColor(hdc, color::Green);
		SetBkColor  (hdc, color::Black);
		SelectObject(hdc,     Main_pen);	
		SelectObject(hdc,   Main_brush);
		
		int _rand_x = rand() % (Horzres - 400),
			_rand_y = rand() % (Vertres - 350);
		
		Rectangle(hdc, _rand_x, _rand_y, _rand_x + 400, _rand_y + 100);
		
		char MessageToNeo1[16] = {"Wake up, Neo..."};
		char MessageToNeo2[22] = {"The Matrix has you..."};
		char MessageToNeo3[28] = {"Follow the white rabbit."};

		TextOut(hdc, _rand_x + 25, _rand_y + 20, &MessageToNeo1[0], 1);
		for(int i = 1; i < 16; i++)
		{
			TextOut(hdc, _rand_x + 30 + i*14, _rand_y + 20, &MessageToNeo1[i], 1);

			Sleep(100);
		}
		TextOut(hdc, _rand_x + 200, _rand_y + 25, " ", 1);
		
		Sleep(500);
		
		for(int i = 0; i < 22; i++)
		{
			TextOut(hdc, _rand_x + 25 + i*13, _rand_y + 40, &MessageToNeo2[i], 1);

			Sleep(100);
		}
		TextOut(hdc, _rand_x + 200, _rand_y + 25, " ", 1);
		
		Sleep(500);
		
		for(int i = 0; i < 28; i++)
		{
			TextOut(hdc, _rand_x + 25 + i*13, _rand_y + 60, &MessageToNeo3[i], 1);

			Sleep(100);
		}
		TextOut(hdc, _rand_x + 200, _rand_y + 25, " ", 1);
	}
	
	
	/*void WriteColorizedText() // Old colorized text
	{
		for(int i = 0; i < Horzres/10; i++)
		{
			for(int j = 0; j < Vertres/10; j++)
			{
				int Text_color_R = rand() % 255, Text_color_G = rand() % 255, Text_color_B = rand() % 255;
				SetTextColor(hdc, RGB(Text_color_R, Text_color_G, Text_color_B));
				
				char symb;
				symb = (rand() % 255);
				TextOut(hdc, i*10, j*10, &symb, 1);
				
				Sleep(1);
			}
		}
	}*/
	
		
	void WriteRandomLettersEverywhere(HDC hdc, int Horzres, int Vertres, int WaitTime) // Colorized text
	{
		
		for(int i = 0; i < 5*(Horzres + Vertres); i++)
		{
			
			int _rand_x = rand() % Horzres,
				_rand_y = rand() % Vertres;
			
			int Text_color_R = rand() % 255,
				Text_color_G = rand() % 255,
				Text_color_B = rand() % 255;
			SetTextColor(hdc, RGB(Text_color_R, Text_color_G, Text_color_B));
					
			char symb;
			symb = (rand() % 255);
			TextOut(hdc, _rand_x, _rand_y, &symb, 1);
			
			Sleep(WaitTime);
		}
	}
	
	
	void WriteRandomLettersOnError(HDC hdc, int Horzres, int Vertres, int WaitTime)
	{
		SetBkColor(hdc, color::Black);
		
		for(int i = 0; i < 100; i++)
		{
			int Text_color_R = rand() % 255,
				Text_color_G = rand() % 255,
				Text_color_B = rand() % 255;
			SetTextColor(hdc, RGB(Text_color_R, Text_color_G, Text_color_B));
			
			int _rand_x = (rand() % 300) + Horzres/2 - 150,
				_rand_y = (rand() % 100) + Vertres/2 -  50;
			
			char symb;
			symb = (rand() % 255);
			TextOut(hdc, _rand_x, _rand_y, &symb, 1);
			
			Sleep(WaitTime);
		}
	}
	
	
	void Restart(HDC hdc, int Horzres, int Vertres, int WaitTime) // System restart
	{
		Sleep(3000);
		
		SetTextColor(hdc, color::Black);
		SetBkColor	(hdc, color::Green);
		SelectObject(hdc,    Error_pen);	
		SelectObject(hdc,  Error_brush);
		
		Rectangle(hdc, Horzres/2 - 150, Vertres/2 - 50, Horzres/2 + 150, Vertres/2 + 50);

		TextOut(hdc, Horzres/2 - 100, Vertres/2 - 20, "CRITICAL FAILURE IN SYSTEM", 26);
		TextOut(hdc, Horzres/2 - 125, Vertres/2, 	  " ", 							 1);
		TextOut(hdc, Horzres/2 -  75, Vertres/2, 	  "INITIATING RESTART", 		18);
		TextOut(hdc, Horzres/2 - 125, Vertres/2, 	  " ", 							 1);
		
		Sleep(2000);
		
		WriteRandomLettersOnError(hdc, Horzres, Vertres, WaitTime);
		
		Sleep(1000);
		
		SelectObject(hdc,   Black_pen);	
		SelectObject(hdc,  Main_brush);
		
		Rectangle(hdc, 0, 0, Horzres, Vertres);
		
		Sleep(1000);
	}

} // namespace

namespace graphics
{

	void InitPaint(HWND &hWnd, HDC &hdc, PAINTSTRUCT *paintstruct)
	{
		hdc = BeginPaint(hWnd, paintstruct);

		InitHpen();
		InitHbrush();

		SetTextColor(hdc, color::Green);
		SetBkColor  (hdc, color::Black);
	}


	void StartMessageEvent(HDC &hdc, int &Horzres, int &Vertres)
	{
		SetTextColor(hdc, color::Green);
		SetBkColor(hdc, color::Black);

		char StartMessage2[] = {"start"};
		char StartMessage3[] = {" Calculating.exe"};

		TextOut(hdc, 0, 0, ">", 1);
		TextOut(hdc, Horzres, Vertres, " ", 1);
		Sleep(2000);

		TextOut(hdc, 8, 0, StartMessage2, sizeof(StartMessage2));
		Sleep(150);
		
		TextOut(hdc, 8 + sizeof(StartMessage2)*5, 0, StartMessage3, sizeof(StartMessage3));

		for(int i = 0; i < 5; i++)
		{
			TextOut(hdc, 10 + sizeof(StartMessage2)*5 + sizeof(StartMessage3)*6, 0, "_", 1);
			Sleep(500);
			TextOut(hdc, 10 + sizeof(StartMessage2)*5 + sizeof(StartMessage3)*6, 0, "  ", 2);
			Sleep(500);
		}
	}


	void GreenTextEvent(HDC &hdc, int &Horzres, int &Vertres, int &WaitTimeGreenText)
	{
		SetTextColor(hdc, color::Green);
		SetBkColor  (hdc, color::Black);
		SelectObject(hdc,     Main_pen);	
		SelectObject(hdc,   Main_brush);
		
		for(int i = 0; i < Vertres/10; i++)
		{
			for(int j = 0; j < Horzres/10; j++)
			{

				char symb;
				symb = (rand() % 255);
				TextOut(hdc, j*10, i*10, &symb, 1);
			}
			Sleep(WaitTimeGreenText);
		}
	}


	void NeoEvent(HDC &hdc, int &Horzres, int &Vertres, int& WaitTimeRandomLettersOnError)
	{
		WriteNeoMessage(hdc, Horzres, Vertres);
		Restart(hdc, Horzres, Vertres, WaitTimeRandomLettersOnError);
	}


	void RandomLettersEvent(HDC &hdc, int &Horzres, int &Vertres, int& WaitTimeRandomLettersEverywhere, int& WaitTimeRandomLettersOnError)
	{
		WriteRandomLettersEverywhere(hdc, Horzres, Vertres, WaitTimeRandomLettersEverywhere);
		Restart(hdc, Horzres, Vertres, WaitTimeRandomLettersOnError);
	}
		
} // namespace graphics

	

