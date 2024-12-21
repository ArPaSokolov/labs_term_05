import numpy as np
import matplotlib.pyplot as plt

# Параметры
a, b = 0, 10
c, d = 0, 10
epsilon = 0.01


# Правая часть
def f(x, y):
    return x * y ** 2


# Граничные условия
def boundary_conditions(U, x, y):
    U[:, 0] = x + c
    U[:, -1] = x + d
    U[0, :] = a + y
    U[-1, :] = b + y
    return U


# Метод простой итерации
def simple_iteration_method(N, M):
    h = (b - a) / N
    k = (d - c) / M

    x = np.linspace(a, b, N + 1)
    y = np.linspace(c, d, M + 1)

    U = np.zeros((N + 1, M + 1))
    U = boundary_conditions(U, x, y)
    U_new = np.copy(U)

    max_iterations = 10000
    for iteration in range(max_iterations):
        for i in range(1, N):
            for j in range(1, M):
                U_new[i, j] = 0.25 * (U[i + 1, j] + U[i - 1, j] + U[i, j + 1] + U[i, j - 1] - h ** 2 * f(x[i], y[j]))

        if np.linalg.norm(U_new - U, ord=np.inf) < epsilon:
            break

        U = np.copy(U_new)

    return x, y, U


# Решение для сеток
x5, y5, U5 = simple_iteration_method(5, 5)
x10, y10, U10 = simple_iteration_method(10, 10)

# Визуализация
X5, Y5 = np.meshgrid(x5, y5)
X10, Y10 = np.meshgrid(x10, y10)

fig = plt.figure(figsize=(12, 5))

ax1 = fig.add_subplot(121, projection='3d')
ax1.plot_surface(X5, Y5, U5.T, cmap='viridis')
ax1.set_title('Сетка 5x5 (Метод простой итерации)')
ax1.set_xlabel('x')
ax1.set_ylabel('y')
ax1.set_zlabel('U(x, y)')

ax2 = fig.add_subplot(122, projection='3d')
ax2.plot_surface(X10, Y10, U10.T, cmap='viridis')
ax2.set_title('Сетка 10x10 (Метод простой итерации)')
ax2.set_xlabel('x')
ax2.set_ylabel('y')
ax2.set_zlabel('U(x, y)')

plt.tight_layout()
plt.show()
