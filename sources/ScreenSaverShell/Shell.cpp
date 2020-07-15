#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

namespace
{
    int Parameters[20];

} // namespace


namespace shell
{

    int* LoadConfig()
    {
        std::ifstream configin;
        configin.open("config.txt");

        if(configin.is_open())
        {
            std::string line;
            for(int i = 0; getline(configin, line); i++)
            {
                if(i == 0)
                    continue;

                for(int j = 0; j <= line.size(); j++)
                {
                    if(line[j] == ':')
                    {
                        char value[10] =  {};

                        for(int s = 0, k = j+1; k <= line.size(); k++, s++)
                            value[s] = line[k];

                        Parameters[i] = atoi(value);
                    }
                }
            }
        }
        return Parameters;
    }


    int CheckConfigValues(int *checking)
    {

        if(checking[1] != 0)
        {
            return 1;
            /*char _filepath[] = {"..\\..\\resources\\videos\\"};

            char _video_number[10] = {};
            sprintf(_video_number, "%d", checking[1]);

            strcat(_filepath, _video_number);
            strcat(_filepath, ".avi");

            std::ifstream _check_video(_filepath);
            if(!_check_video.is_open())
                return 1;*/
        }

        for(int i = 2; i <= 4; i++)
            if(checking[i] < 0)
                return i;
        
        return 0;
    }

} // namespace shell
