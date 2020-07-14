#ifndef NUMBERSSCRENSAVER_GRAPHICS_H
#define NUMBERSSCRENSAVER_GRAPHICS_H

#include <stdio.h>
#include <windows.h>

namespace graphics
{
	void InitPaint(HWND*, HDC*, PAINTSTRUCT*);

	void GreenTextEvent(HDC*, int*, int*);

	void NeoEvent(HDC*, int*, int*);
	void RandomLettersEvent(HDC*, int*, int*);

} // namespace greaphics


#endif // NUMBERSSCRENSAVER_GRAPHICS_H
