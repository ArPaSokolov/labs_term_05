#include <iostream>
#include <thread>
#include <mutex>
#include <string>


void Fact(std::string name) { // вычисление N!

    int f = 1;
    for (int j = 0; j < 10; j++){
        for (int i = 1; i <= 1000000000; i++) {
            f *= i;
        }
    }
}

int main()
{
    clock_t parallel_start = clock(); // время до выполнения кода

    std::thread thread1(Fact, "t1");
    std::thread thread2(Fact, "t2");
    thread1.join();
    thread2.join();

    clock_t parallel_end = clock(); // время после выполнения кода
    double parallel_seconds = (double)(parallel_end - parallel_start) / CLOCKS_PER_SEC; // время выполнения кода в секундах

    std::cout << "In parallel: " << parallel_seconds << std::endl;


    clock_t progress_start = clock(); // время до выполнения кода

    Fact("t3");
    Fact("t4");

    clock_t progress_end = clock(); // время после выполнения кода
    double progress_seconds = (double)(progress_end - progress_start) / CLOCKS_PER_SEC; // время выполнения кода в секундах

    std::cout << "In progress: " << progress_seconds << std::endl;
}
