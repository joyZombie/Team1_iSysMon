#include"systemInteraction.h"
#include <in6addr.h>
using namespace std;
int main()
{
    storeData obj;
    obj.intialiseThread();
    int i = 0;
    // Sleep(2000);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    while (i != 5)
    {
        string str = obj.fetchNewData();
        cout << str << endl;
        i++;
        // Sleep(2000);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

