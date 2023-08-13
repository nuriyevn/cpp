#include <iostream>
#include <thread>
#include <cmath>
using namespace std;

void task1(std::string msg)
{
    std::cout << "\ntask1 says: I started an external thread " << msg;

    int result = 0;
    for (int i = 0; i < 2000000000; i++)
    {
        result += i * 50 + i*i+log(i);
        if (i % 100000000 == 0)
           cout << "Result from another thread: " << result << endl;
    }

    cout << "\nI am an another thread, and I am done" << endl;

    return;
}

int main()
{
    cout << "Main program started\n";
    std::thread t1(task1, "Hello");

    int n;
    cin >> n; 
    int result = 0;
    for (int i = 0; i < 2000000000; i++)
    {
        result += i * 50 + i*i+log(i);
        if (i % 100000000 == 0)
            cout << "Result from main: " << result << endl;
    }

    t1.join();

    return 0;
}