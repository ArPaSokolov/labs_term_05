#include <iostream>
#include <iomanip>
#include <cmath>

// Функция f(x) = e^(x/2)
double f(double x) {
    return exp(x / 2);
}

// Первая производная функции f(x)
double firstDerivative(double x) {
    return 0.5 * exp(x / 2);
}

// Вторая производная функции f(x)
double secondDerivative(double x) {
    return 0.25 * exp(x / 2);
}

int main() {
    const int numNodes = 5;
    const double start = 0.5;
    const double end = 1.5;
    const double h = (end - start) / (numNodes - 1);

    // Вывод таблицы значений функции и производных;
    std::cout << "x      f(x)    f'(x) (left)  f'(x) (right)  f'(x) (central)  f''(x)   f'(x) (exact)  f''(x) (exact)" << std::endl;
    for (int i = 0; i < numNodes; ++i) {
        double x = start + i * h;
        double exactFirstDerivative = firstDerivative(x);
        double exactSecondDerivative = secondDerivative(x);

        std::cout << x << std::fixed << std::setprecision(4) << std::showpoint << "   " << f(x) << "      ";

        // Вычисление производных
        if (x - h < start) {
            std::cout << "Не сущ        ";
        } else {
            double leftFirstDerivative = (f(x) - f(x - h)) / h;
            std::cout << leftFirstDerivative << "        ";
        }

        if (x + h > end) {
            std::cout << "Не сущ          ";
        } else {
            double rightFirstDerivative = (f(x + h) - f(x)) / h;
            std::cout <<  rightFirstDerivative << "          ";
        }

        if (x - h < start || x + h > end) {
            std::cout << "Не сущ      ";
        } else {
            double centralFirstDerivative = (f(x + h) - f(x - h)) / (2 * h);
            std::cout << centralFirstDerivative << "      ";
        }

        if (x - h < start || x + h > end) {
            std::cout << "Не сущ       ";
        } else {
            double secondDerivative = (f(x - h) - 2 * f(x) + f(x + h)) / (h * h);
            std::cout << secondDerivative << "       ";
        }

        // Вывод значений
        std::cout << exactFirstDerivative << "        " << exactSecondDerivative << std::setprecision(1) << std::endl;
    }

    // Таблица погрешностей
    std::cout << std::endl;
    std::cout << "x     Error (left)  Error (right)  Error (central)   Error (second)" << std::endl;;
    for (int i = 0; i < numNodes; ++i) {
        double x = start + i * h;
        double exactFirstDerivative = firstDerivative(x);
        double exactSecondDerivative = secondDerivative(x);

        std::cout << x << std::setprecision(5) << "     ";

        // Вычисление производных
        if (x - h < start) {
            std::cout << " Не сущ        ";
        }
        else {
            double leftFirstDerivative = (f(x) - f(x - h)) / h;
            std::cout << std::abs(exactFirstDerivative - leftFirstDerivative) << "        ";
        }

        if (x + h > end) {
            std::cout << " Не сущ          ";
        }
        else {
            double rightFirstDerivative = (f(x + h) - f(x)) / h;
            std::cout << std::abs(exactFirstDerivative - rightFirstDerivative) << "          ";
        }

        if (x - h < start || x + h > end) {
            std::cout << " Не сущ      ";
        }
        else {
            double centralFirstDerivative = (f(x + h) - f(x - h)) / (2 * h);
            std::cout << std::abs(exactFirstDerivative - centralFirstDerivative) << "      ";
        }

        if (x - h < start || x + h > end) {
            std::cout << " Не сущ       ";
        }
        else {
            double secondDerivative = (f(x - h) - 2 * f(x) + f(x + h)) / (h * h);
            std::cout << std::abs(exactSecondDerivative - secondDerivative) << "       ";
        }

        // Вывод погрешностей
        std::cout << std::setprecision(1) << std::endl;
    }

    return 0;
}