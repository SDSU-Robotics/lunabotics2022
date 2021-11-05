#include <windows.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include "Class-Navi.cpp"
#include "Class-Excv.cpp"
#include "Class-Return.cpp"
using namespace std;


int main()
{
    bool exit = false;
    int task= 0;
    float Atime, Btime, Ctime;
    while(exit == false)
    {
        if (GetAsyncKeyState(VK_END)) // End(back)
        {
            exit = true;
        }

        if (GetAsyncKeyState(VK_NEXT)) //man (up)
        {
            task = 1;
        }
        if (GetAsyncKeyState(VK_PRIOR)) //auto (down)
        {
            task = 2;
        }

        if (task == 1)
        {
           if (GetAsyncKeyState(VK_LEFT))
            cout << "Left" << endl;
           else if (GetAsyncKeyState(VK_RIGHT))
            cout << "Right" << endl;
           else if (GetAsyncKeyState(VK_UP))
            cout << "Forward" << endl;
           else if (GetAsyncKeyState(VK_DOWN))
            cout << "Backward" << endl;
           else
            cout << "Scanning manual" << endl;

        }
        if (task == 2)
        {
            Atime = clock();
            for (;;)
            {
                Navigation();
                if (GetAsyncKeyState(VK_END)) // End(back)
                    break;
                if (GetAsyncKeyState(VK_NEXT)) //man (up)
                    {
                        task = 1;
                        break;
                    }
                if ((clock() - Atime) / CLOCKS_PER_SEC >= 2) // time in seconds
                    break;

            }

            Btime = clock();
            for (;;)
            {
                Excavation();
                if (GetAsyncKeyState(VK_END)) // End(back)
                    break;
                if (GetAsyncKeyState(VK_NEXT)) //man (up)
                    {
                        task = 1;
                        break;
                    }
                if ((clock() - Btime) / CLOCKS_PER_SEC >= 4) // time in seconds
                    break;

            }

            Ctime = clock();
            for (;;)
            {
                Return();

                if (GetAsyncKeyState(VK_END)) // End(back)
                    break;
                if (GetAsyncKeyState(VK_NEXT)) //man (up)
                    {
                        task = 1;
                        break;
                    }
                if ((clock() - Ctime) / CLOCKS_PER_SEC >= 2) // time in seconds
                    break;

            }
        }

    }
    return 0;
}
