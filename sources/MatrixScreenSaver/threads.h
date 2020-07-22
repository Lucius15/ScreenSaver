#ifndef SCREENSAVER_MATRIXSCREENSAVER_THREADS_H
#define SCREENSAVER_MATRIXSCREENSAVER_THREADS_H

#include "graphics\\graphics.h"
#include "sound\\sound.h"

namespace thread
{
    void GraphicsEventThread(LPVOID);
    void SoundThread();

} // namespace thread

#endif // SCREENSAVER_MATRIXSCREENSAVER_THREADS_H