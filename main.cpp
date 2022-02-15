#include"systemInteraction.h"
#include <in6addr.h>
using namespace std;

int main()
{
    vector<string>arr;
    int interval = 1000;
    int i = 0;
    while (1 && i != 10)
    {
        storeData obj;
        obj.fetchData();
        arr.push_back(obj.stringify());
        i++;
        Sleep(interval);
    }
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << endl;
    }
    return 0;
}