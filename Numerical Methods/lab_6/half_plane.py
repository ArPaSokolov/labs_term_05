import numpy as np
import matplotlib.pyplot as plt


def f(x):  # f(x, t)
    return x


def U_x(x):
    return x ** 2 - 5 * x + 5


def scheme_1(I, J, dt, U, f, x, t):
    for i in range(1, I + 1):
        for j in range(0, J):
            U[i][j + 1] = U[i - 1][j] + dt * f(x[i])
    return U


def scheme_2(I, J, dt, U, f, x, t):
    for i in range(I - 1, -1, -1):
        for j in range(0, J):
            U[i][j + 1] = U[i + 1][j] - dt * f(x[i])
    return U


# Задаем сетку
def init_grid(I, J, dx, dt, a, U_x):
    I1 = I + J
    U = np.zeros((I1 + 1, J + 1))
    x = np.zeros(I1 + 1)
    t = np.zeros(J + 1)
    if a > 0:
        for i in range(J + I + 1):
            x[i] = dx * (i - J)
            U[i][0] = U_x(x[i])
    elif a < 0:
        for i in range(I + J + 1):
            x[i] = i * dx
            U[i][0] = U_x(x[i])
        for i in range(J + 1):
            t[i] = i * dt
    return x, t, U

# Функция для построения 3D графика
def plot_3d(graph, title):
    graph[0], graph[1] = np.meshgrid(graph[0], graph[1])
    graph[0], graph[1] = graph[0].T, graph[1].T
    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')
    ax.set_title(title)
    ax.set_xlabel("x")
    ax.set_ylabel("t")
    ax.set_zlabel("U")
    ax.set_rasterization_zorder(1)
    ax.plot_surface(graph[0], graph[1], graph[2], cmap='viridis')
    plt.show()


# Параметры задачи
x_start, x_end = 0, 1
t_start, t_end = 0, 10
dx = 0.1
a1 = 2
a2 = -2

# Условие устойчивости
dt = dx / max([abs(a1), abs(a2)])

# Размерности сетки
I = int((x_end - x_start) / dx)
J = int((t_end - t_start) / dt)


# Построение графиков
x, t, U = init_grid(I, J, dx, dt, a1, U_x)
U = scheme_1(I + J, J, dt, U, f, x, t)
x, t = np.linspace(x_start, x_end, I + 1), np.linspace(t_start, t_end, J + 1)
U = U[J:J + I + 1, :]
plot_3d([x, t, U], "Схема 1 (a > 0)")

x, t, U = init_grid(I, J, dx, dt, a2, U_x)
U = scheme_2(I + J, J, dt, U, f, x, t)
x, t = np.linspace(x_start, x_end, I + 1), np.linspace(t_start, t_end, J + 1)
U = U[0:I + 1, :]
plot_3d([x, t, U], "Схема 2 (a < 0)")

