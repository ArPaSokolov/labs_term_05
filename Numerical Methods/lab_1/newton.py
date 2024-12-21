import sympy as sp


# Функция
def func(x):
    return 2 * sp.exp(-x) - x / 2


# Дано
a, b = 1, 2  # границы отрезка

k = 0
X = [0] * 6  # список с приближенными значениями корня
X[k] = float(a)  # идем от левой границы

# Вычисления
x = sp.symbols('x')  # определение переменной
f = func(x) # определение функции
f_prime = sp.diff(f, x) # первая производная

print("k      x(k)")
while abs(X[k] - X[k-1]) > 0.0000001:
    X[k+1] = X[k] - func(X[k]) / f_prime.subs(x, X[k])
    print(f"{k+1}   {X[k]:.8f}")
    k += 1
print(f"{k+1}   {X[k]:.8f}")
