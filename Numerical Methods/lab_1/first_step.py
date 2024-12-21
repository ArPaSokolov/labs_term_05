import numpy as np
import matplotlib.pyplot as plt


# Функция
def func(x):
    return 2 * np.exp(-x) - x / 2


# Дано
y_values = list()
x_values = list()
a, b = -1, 5  # границы отрезка
n = 25  # количество точек
h = (b - a) / n  # шаг между точками на оси Х

# Вычисление и вывод результатов
x = a - h
for _ in range(0, n + 1):
    x += h
    x_values.append(x)
    y_values.append(func(x))
    print(f"f({x_values[-1]:.7f}) = {y_values[-1]:.7f}")

# Построение графика
plt.plot(x_values, y_values, marker='o',  label='f(x)')
plt.axhline(0, color='black', linewidth=0.8)
plt.axvline(0, color='black', linewidth=0.8)
plt.title("График функции f(x) = 2e^(-x) - x/2")
plt.xlabel("x")
plt.ylabel("f(x)")
plt.grid(True)
plt.show()
