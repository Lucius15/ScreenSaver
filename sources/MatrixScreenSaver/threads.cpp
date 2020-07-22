#include <time.h>
#include "threads.h"

namespace thread
{
    void GraphicsEventThread(LPVOID RawInput)
    {
        graphics::GraphicsThreadParam *Input = reinterpret_cast<graphics::GraphicsThreadParam*>(RawInput);

        Sleep(2000);

        graphics::StartMessageEvent(Input->hdc, Input->Horzres, Input->Vertres);

        graphics::GreenTextEvent(Input->hdc, Input->Horzres, Input->Vertres, Input->Parameters[5]);
        
        while(true)
        {
            srand(time(NULL));
            int chance = rand() % Input->Parameters[4];
            
            switch(chance)
            {
                case 1:
                {
                    graphics::NeoEvent(Input->hdc, Input->Horzres, Input->Vertres, Input->Parameters[7]);

                    graphics::GreenTextEvent(Input->hdc, Input->Horzres, Input->Vertres, Input->Parameters[5]);
                    break;
                }
                case 2:
                {
                    graphics::RandomLettersEvent(Input->hdc, Input->Horzres, Input->Vertres, Input->Parameters[6], Input->Parameters[7]);

                    graphics::GreenTextEvent(Input->hdc, Input->Horzres, Input->Vertres, Input->Parameters[5]);
                    break;
                }
                default:
                {
                    graphics::GreenTextEvent(Input->hdc, Input->Horzres, Input->Vertres, Input->Parameters[5]);
                    
                    break;
                }
            }	
        }
    }
} // namespace thread
