#ifndef NUMBERSSCRENSAVER_GRAPHICS_H
#define NUMBERSSCRENSAVER_GRAPHICS_H

#include <stdio.h>
#include <windows.h>

namespace graphics
{
	void InitPaint(HWND hWnd, HDC hdc, PAINTSTRUCT paintstruct);

	void GreenTextEvent(HDC hdc, int Horzres, int Vertres);

	void NeoEvent(HDC hdc, int Horzres, int Vertres);
	void RandomLettersEvent(HDC hdc, int Horzres, int Vertres);

}


#endif // NUMBERSSCRENSAVER_GRAPHICS_H
