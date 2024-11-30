import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Параметры задачи
a, b = 0, 1
c, d = 0, 10
A = 1
h = 0.1  # шаг по пространству
tau = 0.005  # шаг по времени
lambda_ = A * tau / h**2

# Проверка на устойчивость
if lambda_ >= 1/2:
    raise ValueError(f"Не выполняется условие устойчивости: lambda = {lambda_} >= 1/2")

# Число узлов по x и t
N = int((b - a) / h)
M = int((d - c) / tau)

# Инициализация сетки
u = np.zeros((M + 1, N + 1))

# Начальные условия
x = np.linspace(a, b, N + 1)
u[0, :] = x**3

# Применение явной схемы
for j in range(M):
    for i in range(1, N):
        u[j+1, i] = u[j, i] + lambda_ * (u[j, i+1] - 2*u[j, i] + u[j, i-1])
    # Граничные условия
    u[j+1, 0] = 0
    u[j+1, N] = 1

# Визуализация результатов в 3D
T = np.linspace(c, d, M + 1)
X, T = np.meshgrid(x, T)

fig = plt.figure(figsize=(10, 6))
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, T, u, cmap='viridis')

ax.set_xlabel('x')
ax.set_ylabel('t')
ax.set_zlabel('U(x, t)')
ax.set_title('Схема 1 (явная)')

plt.show()

# Визуализация результатов в 2D
T = np.linspace(c, d, M + 1)
X, T = np.meshgrid(x, T)

plt.figure(figsize=(10, 6))
for t in range(0, M+1, M//10):
    plt.plot(x, u[t, :], label=f't={t*tau:.2f}')
plt.xlabel('x')
plt.ylabel('U(x,t)')
plt.legend()
plt.title('Схема 1 (явная)')
plt.grid(True)
plt.show()
