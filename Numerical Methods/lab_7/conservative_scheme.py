import numpy as np
import matplotlib.pyplot as plt

# Параметры
h = 0.1  # шаг по пространству
tau = 0.01  # шаг по времени
eps = 0.01  # точность

# Границы области
a = c = 0
b = d = 1

# Количество точек по пространству и времени
I = int((b - a) / h) + 1
J = int((d - c) / tau) + 1
u = np.zeros((J, I))

# Начальные условия
for i in range(I):
    if a + i * h >= 0.5:        # Если x больше или равен 0.5
        u[0][i] = 3  # Устанавливаем значение u в 3
    else:
        u[0][i] = 4  # Устанавливаем значение u в 4

# Вычисление значений u
for j in range(J - 1):
    for i in range(I - 1):
        if np.abs(u[j][i]) > h / tau:
            print("Условие устойчивости не выполнено")
            exit(1)  # Выход из программы

        u[j + 1][i] = u[j][i] + tau / (2 * h) * (u[j][i - 1] ** 2 - u[j][i] ** 2)

    # Периодические граничные условия
    u[j + 1][0] = u[j + 1][-2]
    u[j + 1][-1] = u[j + 1][1]

# Визуализация
x = np.arange(a, b + h, h)
t = np.arange(c, d + tau, tau)
x, t = np.meshgrid(x, t)
fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.set_xlabel("t")
ax.set_ylabel("x")
ax.set_zlabel("U")
ax.set_title('Решение уравнения переноса\nметодом консервативной схемы')
ax.plot_surface(t, x, u, cmap="viridis")

plt.show()
