import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Параметры задачи
a, b = 0, 1
c, d = 0, 10
D = 1  # Уточните значение D, если оно задано
N = 100  # Число узлов по x
M = 1000  # Число узлов по t
h = (b - a) / N
tau = (d - c) / M
lambda_ = (D * tau / h) ** 2

# Инициализация сетки
u = np.zeros((M + 1, N + 1))

# Начальные условия
for i in range(N + 1):
    x_i = i * h
    u[0, i] = x_i ** 2

for i in range(N + 1):
    x_i = i * h
    u[1, i] = x_i ** 2 - tau

# Прогонка
for j in range(1, M):
    alpha = np.zeros(N + 1)
    beta = np.zeros(N + 1)

    # Прямой ход
    for i in range(1, N):
        alpha[i] = lambda_ / (1 + 2 * lambda_ - lambda_ * alpha[i - 1])
        beta[i] = (2 * u[j, i] - u[j - 1, i] + lambda_ * beta[i - 1]) / (1 + 2 * lambda_ - lambda_ * alpha[i - 1])

    # Граничное условие на правой границе
    u[j + 1, N] = 1

    # Обратный ход
    for i in range(N - 1, 0, -1):
        u[j + 1, i] = alpha[i] * u[j + 1, i + 1] + beta[i]

    # Граничное условие на левой границе
    u[j + 1, 0] = 0

# Визуализация результатов

x = np.linspace(a, b, N + 1)
t = np.linspace(c, d, M + 1)
X, T = np.meshgrid(x, t)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, T, u, cmap='viridis')

ax.set_xlabel('x')
ax.set_ylabel('t')
ax.set_zlabel('U(x, t)')
ax.set_title('Схема 2 (неявная)')

plt.show()
