#include <iostream>
#include <iomanip>
#include <cmath>

// Определение правой части уравнения y' = sin(2x + y) - 0.3y
double f(double x, double y) {
    return sin(2 * x + y) - 0.3 * y;
}

// Метод Эйлера-Коши 2-го порядка точности
void EulerCauchy(double a, double b, double h, double y0) {
    double x = a;
    double y = y0;

    std::cout << std::fixed << std::setprecision(4) << std::showpoint << "Метод Эйлера-Коши 2-го порядка:" << std::endl;
    std::cout << "x = 0       y = 0" << std::endl;
    while (x < b) {
        x += h;
        double y_temp = y + h * f(x, y);
        y = y + (h * (f(x, y) + f(x + h, y_temp))/ 2);
        std::cout << "x = " << x << "  y = " << y << std::endl;
    }
}

// Метод Рунге-Кутта 4-го порядка точности
void RungeKutta(double a, double b, double h, double y0) {
    double x = a;
    double y = y0;

    std::cout << "Метод Рунге-Кутта 4-го порядка:" << std::endl;
    std::cout << "x = 0       y = 0" << std::endl;

    while (x < b) {
        x += h;
        double k1 = h * f(x, y);
        double k2 = h * f(x + h / 2, y + k1 / 2);
        double k3 = h * f(x + h / 2, y + k2 / 2);
        double k4 = h * f(x + h, y + k3);

        y = y + (k1 + 2*k2 + 2*k3 + k4) / 6;
        std::cout << "x = " << x << "  y = " << y << std::endl;
    }
}

int main() {
    double a = 0;
    double b = 0.5;
    double h = (b - a) / 8; // Шаг интегрирования
    double y0 = 0; // Начальное условие y(0) = 0

    EulerCauchy(a, b, h, y0);
    std::cout << std::endl;
    RungeKutta(a, b, h, y0);
    std::cout << std::endl;

    return 0;
}