#ifndef SCREENSAVER_MATRIXSCREENSAVER_GRAPHICS_H
#define SCREENSAVER_MATRIXSCREENSAVER_GRAPHICS_H

#include <stdio.h>
#include <windows.h>

namespace graphics
{
	void InitPaint(HWND*, HDC*, PAINTSTRUCT*);

	void GreenTextEvent(HDC*, int *Horzres, int *Vertres, int *WaitTimeGreenText);

	void NeoEvent(HDC*, int *Horzres, int *Vertres, int* WaitTimeRandomLettersOnError);
	void RandomLettersEvent(HDC*, int *Horzres, int *Vertres, int* WaitTimeRandomLettersEverywhere, int* WaitTimeRandomLettersOnError);

} // namespace graphics


#endif // SCREENSAVER_MATRIXSCREENSAVER_GRAPHICS_H
