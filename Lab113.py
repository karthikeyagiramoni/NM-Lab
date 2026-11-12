
import numpy as np

a = 0
b = 2
ya = 1
yb = 2

n = 10
h = (b - a) / n

x = np.linspace(a, b, n + 1)
m = n - 1

lower = np.full(m - 1, -1.0)
diag = np.full(m, 2 + h**2 / 2)
upper = np.full(m - 1, -1.0)

d = np.zeros(m)

for i in range(m):
    d[i] = -(h**2 / 2) * x[i + 1]

d[0] += ya
d[-1] += yb


c = np.zeros(m - 1)
r = np.zeros(m)

c[0] = upper[0] / diag[0]
r[0] = d[0] / diag[0]

for i in range(1, m):
    denominator = diag[i] - lower[i-1] * c[i-1]

    if i < m - 1:
        c[i] = upper[i] / denominator

    r[i] = (d[i] - lower[i-1] * r[i-1]) / denominator


y_interior = np.zeros(m)

y_interior[-1] = r[-1]

for i in range(m - 2, -1, -1):
    y_interior[i] = r[i] - c[i] * y_interior[i+1]


y = np.concatenate(([ya], y_interior, [yb]))


print("\nFinite Difference Method using Thomas Algorithm\n")
print("x\t\t y")

for i in range(n + 1):
    print(f"{x[i]:.2f}\t\t {y[i]:.6f}")
