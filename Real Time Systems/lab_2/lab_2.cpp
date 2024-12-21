#include <thread>
#include <mutex>
#include <string>
#include <iostream>
#include <cmath>
#include <chrono>


void Func(std::string name)
{
    long double i = 0;
    auto start = std::chrono::high_resolution_clock::now();

    while (std::chrono::high_resolution_clock::now() - start < std::chrono::seconds(1)) {
        i += pow(10, -9);
    }

    std::cout << name << ": " << i << std::endl;

}

int main()
{
    std::cout << std::endl;
    std::thread thread1(Func, "t1");
    std::thread thread2(Func, "t2");
    std::thread thread3(Func, "t3");
    thread1.join();
    thread2.join();
    thread3.join();

    system("pause");

    return 0;
}
