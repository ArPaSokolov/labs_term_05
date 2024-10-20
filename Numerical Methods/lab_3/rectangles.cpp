#include <iostream>
#include <iomanip>
#include <cmath>

// Функция для интегрирования
double f(double x) {
    return 1 / (1 + std::sin(x));
}

// Метод левых прямоугольников
void leftRectangle(double a, double b, double epsilon) {
    int n = 1;
    double prevSum = 1;
    double currentSum = 0;

    while (std::abs(currentSum - prevSum) > epsilon){
        prevSum = currentSum;
        currentSum = 0;
        n *= 2;
        double h = (b - a) / n;
        for (int i = 0; i < n; ++i) {
            currentSum += f(a + i * h);
        }
        currentSum *= h;
    }

    std::cout << "Полученное значение: " << currentSum << std::endl;
    std::cout << "Количество разбиений: " << n << std::endl;
    std::cout << "Предпоследнее значение: " << prevSum << std::endl;
    std::cout << "Относительная погрешность: " << std::abs(1 - currentSum) * 100 << "%" << std::endl << std::endl;
}

// Метод правых прямоугольников
void rightRectangle(double a, double b, double epsilon) {
    int n = 1;
    double prevSum = 1;
    double currentSum = 0;

    while (std::abs(currentSum - prevSum) > epsilon){
        prevSum = currentSum;
        currentSum = 0;
        n *= 2;
        double h = (b - a) / n;
        for (int i = 1; i <= n; ++i) {
            currentSum += f(a + i * h);
        }
        currentSum *= h;
    }

    std::cout << "Полученное значение: " << currentSum << std::endl;
    std::cout << "Количество разбиений: " << n << std::endl;
    std::cout << "Предпоследнее значение: " << prevSum << std::endl;
    std::cout << "Относительная погрешность: " << std::abs(1 - currentSum) * 100 << "%" << std::endl << std::endl;
}

// Метод центральных прямоугольников
void centerRectangle(double a, double b, double epsilon) {
    int n = 1;
    double prevSum = 1;
    double currentSum = 0;

    while (std::abs(currentSum - prevSum) > epsilon){
        prevSum = currentSum;
        currentSum = 0;
        n *= 2;
        double h = (b - a) / n;
        for (int i = 0; i < n; ++i) {
            currentSum += f(a + (i + 0.5) * h);
        }
        currentSum *= h;
    }

    std::cout << "Полученное значение: " << currentSum << std::endl;
    std::cout << "Количество разбиений: " << n << std::endl;
    std::cout << "Предпоследнее значение: " << prevSum << std::endl;
    std::cout << "Относительная погрешность: " << std::abs(1 - currentSum) * 100 << "%" << std::endl << std::endl;
}

int main() {
    double a = 0; // Начало интервала
    double b = M_PI / 2; // Конец интервала
    double epsilon = 0.0001; // Заданная точность

    std::cout << std::fixed << std::setprecision(5) << std::showpoint;
    std::cout << "МЕТОД ЛЕВЫХ ПРЯМОУГОЛЬНИКОВ: " << std::endl ;
    leftRectangle(a, b, epsilon);

    std::cout << "МЕТОД ПРАВЫХ ПРЯМОУГОЛЬНИКОВ: " << std::endl;
    rightRectangle(a, b, epsilon);

    std::cout << "МЕТОД ЦЕНТРАЛЬНЫХ ПРЯМОУГОЛЬНИКОВ: " << std::endl;
    centerRectangle(a, b, epsilon);

    return 0;
}