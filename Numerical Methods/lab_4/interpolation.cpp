#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

// Погрешность формулы Лагранжа
double errorEstimate = 0;

// Функция для вычисления значения lg(x)
double lg(double x) {
    return log10(x);
}

// Структура для хранения пар x и y = lg(x)
struct Point {
    double x;
    double y;
};

// Функция для вычисления и вывода интерполяционного многочлена Лагранжа
double lagrangeInterpolation(const std::vector<Point>& points, double x) {
    std::cout << std::resetiosflags(std::ios_base::fmtflags(std::ios_base::fixed | std::ios_base::showpoint));
    std::cout << "Интерполяционный многочлен Лагранжа:" << std::endl;
    
    double result = 0;

    for (size_t i = 0; i < points.size(); ++i) {
        if (i != 0) {
            std::cout << " + ";
        }
        double term = points[i].y;
        std::cout << "(" << points[i].y << ")";
        for (size_t j = 0; j < points.size(); ++j) {
            if (j != i) {
                term *= (x - points[j].x) / (points[i].x - points[j].x);
                std::cout << " * (x - " << points[j].x << ") / (" << points[i].x << " - " << points[j].x << ")";
            }
        }
        
        errorEstimate += std::abs(x - points[i].x);
        result += term;
    }
    std::cout << std::endl;

    return result;
}

int main() {
    // Заданные значения xk
    std::vector<double> xk = {8.0, 8.5, 9.0, 9.5};
    
    // Заполнение таблицы значениями yk = lg(xk)
    std::vector<Point> table;
    for (double x : xk) {
        table.push_back({x, lg(x)});
    }

    // Вывод таблицы
    std::cout << "Таблица значений y = lg(x):" << std::endl;
    for (const auto& point : table) {
        std::cout << std::fixed << std::setprecision(5) << std::showpoint;
        std::cout << "x = " << point.x << ", y = " << point.y << std::endl;
    }

    // Вычисление значения в заданной точке
    double x = 8.4;
    double analyticalValue = lg(x);
    double interpolatedValue = lagrangeInterpolation(table, x);

    // Вывод результатов
    std::cout << std::fixed << std::setprecision(4) << std::showpoint;
    std::cout << "Значение lg(" << x << "), вычисленное с помощью многочлена Лагранжа: " << interpolatedValue << std::endl;
    std::cout << "Аналитическое значение lg(" << x << ") = " << analyticalValue << std::endl;

    std::cout << "Оценка погрешности формулы Лагранжа: " << (1/x) * errorEstimate/(2*3*4) << std::endl; // максимальное значение имеет (lnx(x))' = 1/x
    std::cout << std::fixed << std::setprecision(8) << std::showpoint;
    std::cout << "Абсолютная погрешность вычислений: " << std::abs(interpolatedValue - analyticalValue) << std::endl;

    return 0;
}