#ifndef SCREENSAVER_MATRIXSCREENSAVER_GRAPHICS_H
#define SCREENSAVER_MATRIXSCREENSAVER_GRAPHICS_H


#include <windows.h>

namespace graphics
{
	struct GraphicsThreadParam
	{
		HDC hdc;
		int Horzres;
		int Vertres;
		int *Parameters;
	};

} //namespace graphics

namespace graphics
{
	void InitPaint(HWND&, HDC&, PAINTSTRUCT*);

	void StartMessageEvent(HDC&, int &Horzres, int &Vertres);

	void GreenTextEvent(HDC&, int &Horzres, int &Vertres, int &WaitTimeGreenText);

	void NeoEvent(HDC&, int &Horzres, int &Vertres, int& WaitTimeRandomLettersOnError);
	void RandomLettersEvent(HDC&, int &Horzres, int &Vertres, int& WaitTimeRandomLettersEverywhere, int& WaitTimeRandomLettersOnError);

} // namespace graphics


#endif // SCREENSAVER_MATRIXSCREENSAVER_GRAPHICS_H
