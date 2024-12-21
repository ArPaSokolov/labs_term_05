import sympy as sp

# Функция
def func(x):
    return 2 * sp.exp(-x) - x / 2

# Определение переменной
x = sp.symbols('x')

# Определение функции
f = func(x)

# Первая и вторая производные
f_prime = sp.diff(f, x)
f_double_prime = sp.diff(f_prime, x)

# Ввод пользователя
x_value = float(input("Введите значение x: "))

# Вычисление производных в точке
first_derivative = f_prime.subs(x, x_value)
second_derivative = f_double_prime.subs(x, x_value)

# Вывод результатов
print(f"x = {x_value}: значение функции = {func(x_value):.7f}, первая производная = {first_derivative:.7f}, вторая производная = {second_derivative:.7f}")
