import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Параметры задачи
a, b = 0, 1
c, d = 0, 10
a_squared = 1  # Уточните значение a^2, если оно задано
N = 50  # Число узлов по x
M = 500  # Число узлов по t
h = (b - a) / N
tau = (d - c) / M
lambda_ = (a_squared * tau ** 2) / h ** 2

# Инициализация сетки
u = np.zeros((M + 1, N + 1))

# Начальные условия
x = np.linspace(a, b, N + 1)
u[0, :] = x ** 2
u[1, :] = x ** 2 - tau

# Применение явной схемы "крест"
for j in range(1, M):
    for i in range(1, N):
        u[j+1, i] = 2 * (1 - lambda_) * u[j, i] + lambda_ * (u[j, i+1] + u[j, i-1]) - u[j-1, i]

    # Граничные условия
    u[j+1, 0] = 0
    u[j+1, N] = 1

# Визуализация результатов
t = np.linspace(c, d, M + 1)
X, T = np.meshgrid(x, t)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, T, u, cmap='viridis')

ax.set_xlabel('x')
ax.set_ylabel('t')
ax.set_zlabel('U(x, t)')
ax.set_title('Схема крест (явная)')

plt.show()
