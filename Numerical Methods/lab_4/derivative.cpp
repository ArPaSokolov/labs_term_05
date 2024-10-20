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

        // Вычисление производных
        double leftFirstDerivative = (f(x) - f(x - h)) / h;
        double rightFirstDerivative = (f(x + h) - f(x)) / h;
        double centralFirstDerivative = (f(x + h) - f(x - h)) / (2 * h);
        double secondDerivative = (f(x - h) - 2 * f(x) + f(x + h)) / (h * h);

        // Вывод значений
        std::cout << x << std::fixed << std::setprecision(4) << std::showpoint << "   " << f(x) << "      " << leftFirstDerivative << "        " << rightFirstDerivative << "          " << centralFirstDerivative << "      " << secondDerivative << "       " << exactFirstDerivative << "        " << exactSecondDerivative << std::setprecision(1) << std::endl;
    }

    // Таблица погрешностей
    std::cout << std::endl;
    std::cout << "x     Error (left)  Error (right)  Error (central)   Error (second)" << std::endl;;
    for (int i = 0; i < numNodes; ++i) {
        double x = start + i * h;
        double exactFirstDerivative = firstDerivative(x);
        double exactSecondDerivative = secondDerivative(x);

        // Вычисление производных
        double leftFirstDerivative = (f(x) - f(x - h)) / h;
        double rightFirstDerivative = (f(x + h) - f(x)) / h;
        double centralFirstDerivative = (f(x + h) - f(x - h)) / (2 * h);
        double secondDerivative = (f(x - h) - 2 * f(x) + f(x + h)) / (h * h);

        // Вычисление погрешностей
        double errorLeft = std::abs(exactFirstDerivative - leftFirstDerivative);
        double errorRight = std::abs(exactFirstDerivative - rightFirstDerivative);
        double errorCentral = std::abs(exactFirstDerivative - centralFirstDerivative);
        double errorSecond = std::abs(exactSecondDerivative - secondDerivative);

        // Вывод погрешностей
        std::cout << x << std::setprecision(5) << "     " << errorLeft << "        " << errorRight << "        " << errorCentral << "           " << errorSecond << std::setprecision(1) << std::endl;
    }

    return 0;
}