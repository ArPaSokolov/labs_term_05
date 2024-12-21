#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>

// Определение правой части уравнения y' = sin(2x + y) - 0.3y
double f(double x, double y) {
    return sin(2 * x + y) - 0.3 * y;
}

// Метод Эйлера-Коши 2-го порядка точности
std::map<double, double> EulerCauchy(double a, double b, int n, double y0) {
    double h = (b - a) / n; // Шаг интегрирования
    double x = a;
    double y = y0;
    std::map<double, double> EC;

    while (x < b) {
        x += h;
        double y_temp = y + h * f(x, y);
        y = y + (h * (f(x, y) + f(x + h, y_temp))/ 2);
        EC[x] = y;
    }

    return EC;
}

// Метод Рунге-Кутта 4-го порядка точности
std::map<double, double> RungeKutta(double a, double b, int n, double y0) {
    double h = (b - a) / n; // Шаг интегрирования
    double x = a;
    double y = y0;
    std::map<double, double> RK;

    while (x < b) {
        x += h;
        double k1 = h * f(x, y);
        double k2 = h * f(x + h / 2, y + k1 / 2);
        double k3 = h * f(x + h / 2, y + k2 / 2);
        double k4 = h * f(x + h, y + k3);

        y = y + (k1 + 2*k2 + 2*k3 + k4) / 6;
        RK[x] = y;
    }

    return RK;
}

bool checkAccuracy(std::map<double, double>& y1, std::map<double, double>& y2, double eps) {
    for (const auto& [x, y] : y1) {
        if (y2.find(x) != y2.end()) {
            if (fabs(y - y2[x]) >= eps) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    double a = 0;
    double b = 0.5;
    int n = 2; 
    double y0 = 0; // Начальное условие y(0) = 0
    double eps = 0.001; // Точность

    std::map<double, double> notChecked;
    std::map<double, double> checked;

    std::cout << std::fixed << std::setprecision(5) << std::showpoint;

    // std::cout << "Метод Эйлера-Коши 2-го порядка:" << std::endl; 
    // notChecked = EulerCauchy(a, b, n, y0);

    // do {
    //     checked = notChecked;
    //     n *= 2;
    //     notChecked = EulerCauchy(a, b, n, y0);
    // } while (!checkAccuracy(checked, notChecked, eps));

    std::cout << "Метод Рунге-Кутта 4-го порядка:" << std::endl; 
    notChecked = RungeKutta(a, b, n, y0);

    do {
        checked = notChecked;
        n *= 2;
        notChecked = RungeKutta(a, b, n, y0);
    } while (!checkAccuracy(checked, notChecked, eps));

    int count = 0;
    for (const auto& [x, y] : notChecked) {
        if (count > n - 32) {
            std::cout << "x = " << x << "   y1 = " << y;
            if (checked[x]){
                std::cout << "   y2 = " << checked[x] << std::endl;
            }
            else {
                std::cout << std::endl;
            }
        }
        count++;
    }
    std::cout << "Для расчетов с заданной точностью потребовалось " << count << " узлов" << std::endl;
    std::cout << std::endl;


    return 0;
}