#include <time.h>

#include "graphics.h"

namespace
{

	HPEN Main_pen, Error_pen, Black_pen;
	HBRUSH Main_brush, Error_brush;

	namespace color
	{
		int Black = RGB(0, 0, 0);
		int Green = RGB(0, 255, 0);
	}
}

namespace
{
	void InitHpen()
	{
		Main_pen = CreatePen(PS_SOLID, 1, color::Green);
		Error_pen = CreatePen(PS_SOLID, 1, color::Green);
		Black_pen = CreatePen(PS_SOLID, 1, color::Black);
	}


	void InitHbrush()
	{
		Main_brush = CreateSolidBrush(color::Black);
		Error_brush = CreateSolidBrush(color::Black);
	}
	
	
	void WriteNeoMessage(HDC hdc, int Horzres, int Vertres) //Сообщений для Нео
	{
		SetTextColor(hdc, RGB(0, 255, 0));
		SetBkColor(hdc, RGB(0, 0, 0));
		SelectObject(hdc,   Main_pen);	
		SelectObject(hdc, Main_brush);
		
		int _rand_x, _rand_y;
		_rand_x = (rand() % (Horzres - 400));
		_rand_y = (rand() % (Vertres - 350));
		
		Rectangle(hdc, _rand_x, _rand_y, _rand_x + 400, _rand_y + 100);
		
		char MessageToNeo[60] = {"Wake up Neo...The Matrix has youFollow the white rabbit..."};
		for(int i = 0; i < 14; i++)
		{
			TextOut(hdc, _rand_x + 25 + i*14, _rand_y + 20, &MessageToNeo[i], 1);
			Sleep(100);
		}
		
		TextOut(hdc, _rand_x + 200, _rand_y + 25, " ", 1);
		
		Sleep(500);
		
		for(int i = 0; i < 18; i++)
		{
			TextOut(hdc, _rand_x + 25 + i*13, _rand_y + 40, &MessageToNeo[i+14], 1);
			Sleep(100);
		}
		
		TextOut(hdc, _rand_x + 200, _rand_y + 25, " ", 1);
		
		Sleep(500);
		
		for(int i = 0; i < 26; i++)
		{
			TextOut(hdc, _rand_x + 25 + i*13, _rand_y + 60, &MessageToNeo[i+32], 1);
			Sleep(100);
		}
		TextOut(hdc, _rand_x + 200, _rand_y + 25, " ", 1);
	}
	
	
	/*void WriteColorizedText() // Цветной текст
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
	
		
	void WriteRandomColorizedText(HDC hdc, int Horzres, int Vertres)
	{
		for(int i = 0; i < 5*(Horzres + Vertres); i++)
		{
			
			int _rand_x = rand() % Horzres, _rand_y = rand() % Vertres;
			
			int Text_color_R = rand() % 255, Text_color_G = rand() % 255, Text_color_B = rand() % 255;
			SetTextColor(hdc, RGB(Text_color_R, Text_color_G, Text_color_B));
					
			char symb;
			symb = (rand() % 255);
			TextOut(hdc, _rand_x, _rand_y, &symb, 1);
			
			Sleep(1);
		}
	}
	
	
	void RandomLetters(HDC hdc, int Horzres, int Vertres)
	{
		SetBkColor(hdc, color::Black);
		
		for(int i = 0; i < 100; i++)
		{
			int Text_color_R = rand() % 255, Text_color_G = rand() % 255, Text_color_B = rand() % 255;
			SetTextColor(hdc, RGB(Text_color_R, Text_color_G, Text_color_B));
			
			int _rand_x = (rand() % 300) + Horzres/2 - 150, _rand_y = (rand() % 100) + Vertres/2 - 50;
			
			char symb;
			symb = (rand() % 255);
			TextOut(hdc, _rand_x, _rand_y, &symb, 1);
			
			Sleep(150);
		}
	}
	
	
	void Restart(HDC hdc, int Horzres, int Vertres) //Перезапуск системы (красное окно + стирание экрана)
	{
		Sleep(3000);
		
		SetTextColor(hdc, RGB(0, 0, 0));
		SetBkColor(hdc, RGB(0, 255, 0));
		SelectObject(hdc,   Error_pen);	
		SelectObject(hdc, Error_brush);
		
		Rectangle(hdc, Horzres/2 - 150, Vertres/2 - 50, Horzres/2 + 150, Vertres/2 + 50);
		TextOut(hdc, Horzres/2 - 100, Vertres/2 - 20, "CRITICAL FAILURE IN SYSTEM", 26);
		TextOut(hdc, Horzres/2 - 125, Vertres/2, " ", 1);
		TextOut(hdc, Horzres/2 - 75, Vertres/2, "INITIATING RESTART", 18);
		TextOut(hdc, Horzres/2 - 125, Vertres/2, " ", 1);
		
		//PlaySound("Error.wav", NULL, SND_FILENAME | SND_NOSTOP);
		
		Sleep(2000);
		
		RandomLetters(hdc, Horzres, Vertres);
		
		Sleep(1000);
		
		SelectObject(hdc,   Black_pen);	
		SelectObject(hdc, Main_brush);
		
		Rectangle(hdc, 0, 0, Horzres, Vertres);
		
		Sleep(1000);
	}

}

namespace graphics
{

	void InitPaint(HWND hWnd, HDC hdc, PAINTSTRUCT paintstruct)
	{
		hdc = BeginPaint(hWnd, &paintstruct);

		InitHpen();
		InitHbrush();

		SetTextColor(hdc, color::Green);
		SetBkColor(hdc, color::Black);
	}


	void GreenTextEvent(HDC hdc, int Horzres, int Vertres)
	{
		SetTextColor(hdc, color::Green);
		SetBkColor(hdc,   color::Black);
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
			Sleep(5);
		}
	}


	void NeoEvent(HDC hdc, int Horzres, int Vertres)
	{
		WriteNeoMessage(hdc, Horzres, Vertres);
		Restart(hdc, Horzres, Vertres);
	}


	void RandomLettersEvent(HDC hdc, int Horzres, int Vertres)
	{
		RandomLetters(hdc, Horzres, Vertres);
		Restart(hdc, Horzres, Vertres);
	}
		
}

	

