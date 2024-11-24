#include "custom_mutex.h"

#include <thread>
#include <mutex>
#include <string>
#include <iostream>
#include <cmath>


CustomMutex m;
int Bob_coins = 0;
int Tom_coins = 0;
int coins = 1000;
int count = 0;


void coin_sharing(std::string name)
{   
    
    while (coins > 0) {
        m.lock();
        count++;

        if (name  == "Боб" && Bob_coins == Tom_coins && coins > 1) {
            Bob_coins++;
            coins--;
        } 
        else if (name  == "Том" && Bob_coins > Tom_coins) {
            Tom_coins++;
            coins--;
        }
        
        std::cout << std::endl;
        std::cout << "У " << name << "а " << (name == "Боб" ? Bob_coins : Tom_coins) << std::endl;
        std::cout << "Осталось монет: " << coins << std::endl;
                
        if (Bob_coins == Tom_coins && coins == 1) 
        {
            coins--;
            std::cout << std::endl;
            std::cout << "Отдадим покойнику" << std::endl;
        }
        m.unlock();        
    }
}

int main()
{   
    int start = coins;
    
    std::cout << std::endl;
    std::thread thread1(coin_sharing, "Боб");
    std::thread thread2(coin_sharing, "Том");
    thread2.join();
    thread1.join();

    std::cout << std::endl;
    std::cout << "Изначально монет было " << start << std::endl;
    std::cout << "Итераций было " << count << std::endl;
    std::cout << "Итого у Боба " << Bob_coins << std::endl;
    std::cout << "Итого у Тома " << Tom_coins << std::endl;
    std::cout << "Итого монет: " << coins << std::endl;

    return 0;
}
