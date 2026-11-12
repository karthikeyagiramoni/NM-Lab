import numpy as np

def func(x):
    return np.exp(-x**2)/(1+x**2)

n=[12,24,48,96]

def trapezoidal(a, b, n):
    h = (b - a) / n
    integral = 0.5 * (func(a) + func(b))
    
    for i in range(1, n):
        integral += func(a + i * h)
    
    integral *= h
    return integral

def romberg(a, b, panel_count):
    base_panels = panel_count
    levels = 1
    while base_panels % 2 == 0:
        base_panels //= 2
        levels += 1

    R = np.zeros((levels, levels))
    for i in range(levels):
        R[i, 0] = trapezoidal(a, b, base_panels * 2**i)
    
    for j in range(1, levels):
        for i in range(levels - j):
            R[i, j] = (4**j * R[i + 1, j - 1] - R[i, j - 1]) / (4**j - 1)
    
    return R

analytical_value = 0.61882196330814

print("Trapezoidal Rule Approximations:")
for num in n:
    approx = trapezoidal(0, 1, num)
    error = abs(approx - analytical_value)
    print(f"n={num}: Approximation={approx}, Error={error}")
print("\nRomberg Integration Approximations:")
for num in n:
    R = romberg(0, 1, num)
    approx = R[0, -1]
    error = abs(approx - analytical_value)
    print(f"n={num}: Approximation={approx}, Error={error}")