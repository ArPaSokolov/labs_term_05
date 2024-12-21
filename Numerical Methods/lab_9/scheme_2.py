import numpy as np
import matplotlib.pyplot as plt

# Параметры задачи
x_start, x_end = 0, 1  # Границы по x
t_start, t_end = 0, 10  # Границы по t
a = 1  # Коэффициент теплопроводности
h = 0.1  # Шаг по пространству
tau = 0.005  # Шаг по времени
lambda_ = a * tau / h**2  # Числовой параметр лямбда

# Проверка на устойчивость
if lambda_ >= 1/2:
    raise ValueError(f"Не выполняется условие устойчивости: lambda = {lambda_} >= 1/2")

# Число узлов по x и t
N = int((x_end - x_start) / h)
M = int((t_end - t_start) / tau)

# Инициализация сетки
u = np.zeros((M + 1, N + 1))

# Начальные условия
x = np.linspace(x_start, x_end, N + 1)
u[0, :] = x**3

# Применение неявной схемы методом прогонки
for j in range(M):
    # Вектор правой части
    b = u[j, 1:-1].copy()

    # Прогоночные коэффициенты
    alpha = np.zeros(N - 1)  # Прогоночный коэффициент alpha
    beta = np.zeros(N - 1)  # Прогоночный коэффициент beta

    # Прогоночные коэффициенты на первом шаге
    alpha[0] = lambda_ / (1 + 2 * lambda_)
    beta[0] = b[0] / (1 + 2 * lambda_)

    # Прямой ход метода прогонки
    for i in range(1, N - 1):
        denom = 1 + 2 * lambda_ - lambda_ * alpha[i - 1]
        alpha[i] = lambda_ / denom
        beta[i] = (b[i] + lambda_ * beta[i - 1]) / denom

    # Обратная подстановка
    u[j + 1, -2] = beta[-1]
    for i in range(N - 3, -1, -1):
        u[j + 1, i + 1] = alpha[i] * u[j + 1, i + 2] + beta[i]

    # Граничные условия (явные)
    u[j + 1, 0] = 0
    u[j + 1, N] = 1

# Визуализация результатов в 3D
T = np.linspace(t_start, t_end, M + 1)
X, T = np.meshgrid(x, T)

fig = plt.figure(figsize=(10, 6))
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(X, T, u, cmap='viridis')

ax.set_xlabel('x')
ax.set_ylabel('t')
ax.set_zlabel('U(x, t)')
ax.set_title('Схема 2 (неявная)')

plt.show()

# Визуализация результатов в 2D
plt.figure(figsize=(10, 6))
for t in range(0, M + 1, M // 10):
    plt.plot(x, u[t, :], label=f't={t * tau:.2f}')
plt.xlabel('x')
plt.ylabel('U(x,t)')
plt.legend()
plt.title('Схема 2 (неявная)')
plt.grid(True)
plt.show()