#include <iostream>
#include <iomanip>
// #include <cmath>

const int row = 4, column = 4;

void printMatrix(double A[row][column]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            std::cout << std::setprecision(2) << A[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Gauss(double A[row][column], double b[column], double x[column]){
    int k = 0, index = 0;
    double max;
    while (k < column){
        // Поиск строки с максимальным A[i][k]
        max = std::abs(A[k][k]);
        index = k;
        for (int i = k + 1; i < row; i++){
            if (std::abs(A[i][k]) > max){
                max = std::abs(A[i][k]);
                index = i;
            }
        }

        // Перестановка строк
        for (int j = 0; j < column; j++) {
            std::swap(A[k][j], A[index][j]);
        }
        std::swap(b[k], b[index]);

        // Нормализация уравнений
        for (int i = k; i < row; i++){
            double temp = A[i][k];
            if (temp == 0){ // нулевой коэффициент
                continue;  
            } 
            for (int j = k; j < column; j++){
                A[i][j] /= temp;
            }  
            b[i] /= temp;
            if (i == k){ // само же уравнение
                continue;  
            } 
            for (int j = 0; j < column; j++){
                A[i][j] -= A[k][j];
            }
            b[i] -= b[k];
        }
        k++;
    }
    
    std::cout << "Треугольная матрица A: " << std::endl;
    printMatrix(A);

    // обратная подстановка
    for (k = column - 1; k >= 0; k--) {
        x[k] = b[k];
        for (int i = 0; i < k; i++){
            b[i] -= A[i][k] * x[k];
        }
    }

    // вывод
    std::cout << "Ответ:" << std::endl;
    for (int i = 0; i < column; i++){
        std::cout << "x[" << i << "]=" << x[i] << std::endl;
    }
}

void transposeMatrix(double A[row][column], double AT[column][row]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            AT[j][i] = A[i][j];
        }
    }
}

void Seidel(double A[row][column], double b[column], double x[column]) {
    double AT[column][row];
    double C[column][column];
    double d[column];
    transposeMatrix(A, AT); // транспонируем матрицу A

    // C = AT * A
    for (int i = 0; i < column; i++) {
        for (int j = 0; j < column; j++) {
            C[i][j] = 0;
            for (int k = 0; k < row; k++) {
                C[i][j] += AT[i][k] * A[k][j];
            }
        }
    }

    // d = AT * b
    for (int i = 0; i < column; i++) {
        d[i] = 0;
        for (int j = 0; j < row; j++) {
            d[i] += AT[i][j] * b[j];
        }
    }

    // Итерации
    double epsilon = 0.001; // точность
    int maxIterations = 100; // максимальное количество итераций
    int iterations = 0; // счетчик итераций
    double error, maxError; // погрешность

    for (int iter = 0; iter < maxIterations; iter++) {
        double x_new[column];
        for (int i = 0; i < column; i++) {
            x_new[i] = d[i];
            for (int j = 0; j < column; j++) {
                if (j != i) {
                    x_new[i] -= C[i][j] * x_new[j];
                }
            }
            x_new[i] /= C[i][i];
        }

        // Проверка на сходимость
        error, maxError = 0;
        for (int i = 0; i < column; i++) {
            error = std::abs(x[i] - x_new[i]);
            maxError = std::max(error, maxError);
        }

        if (maxError < epsilon) {
            break;
        }

        // Обновляем значения вектора x
        for (int i = 0; i < column; i++) {
            x[i] = x_new[i];
        }

        iterations++;
    }
    std::cout << "Количество итераций: " << iterations << std::endl;

    std::cout << "Преобразованная матрица C:" << std::endl;
    printMatrix(C);

    std::cout << "Решение системы:" << std::endl;
    for (int i = 0; i < column; i++) {
        std::cout << "x[" << i << "] = " << x[i] << std::endl;
    }
    std::cout << std::endl << "Максимальный модуль разности последней и предпоследней итерации:" << maxError << std::endl;
}
    

int main() {
    std::cout << std::endl;

    double A[row][column] = {
        {6.1, -2.2, -1.2, -3.3},
        {7.2, 0.9, 1.8, -4.1},
        {2.8, 3.3, 1.1, 2.5},
        {-1.5, 1.0, 6.3, 0.8}
    };
    double b[column] = {-0.50, -2.15, 14.30, -14.00};
    double x[column];

    std::cout << "Исходная матрица A: " << std::endl;
    printMatrix(A);

    // std::cout << "МЕТОД ГАУССА: " << std::endl;
    // Gauss(A, b, x);

    std::cout << "МЕТОД ЗЕЙДЕЛЯ:" << std::endl;
    Seidel(A, b, x);

    return 0;
}