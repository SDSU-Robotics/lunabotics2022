#include <iostream>
using namespace std;

class Return
{
public:
    Return()
    {
        func();
    };

    void func()
    {
   cout<< "Returning" << endl;
    }
};
