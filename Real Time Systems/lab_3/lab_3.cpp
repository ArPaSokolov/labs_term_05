#include <iostream>
#include <conio.h>
#include <stdio.h>

int main()
{
    clock_t start, end;
    char exitKey = 'q'; // клавиша выхода из программы
    char key;
    std::string message = "The program is still alive!";

    start = clock();
    std::cout << "Press anykey to start\n";
    char x = _getch();
    std::cout << "Started with key " << x << std::endl;

    while (true)
    {
        end = clock();
        if ((double)(end - start) / CLOCKS_PER_SEC >= 1) // секундомер
        {
            std::cout << message << std::endl;
            start = clock();
        }

        if (_kbhit()) // проверяем, нажата ли клавиша
        {
            key = _getch(); // считываем клавишу

            if (key == exitKey)
            {
                std::cout << "Entered exitKey!" << std::endl;
                break;
            }
            else
            {
                std::cout << "Entered key " << key << std::endl;
                message = "The program is still alive! And it has new key ";
                message += key;
            }
        }
    }
}
