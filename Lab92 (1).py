import numpy as np
def func(x):
    return x*(np.sin(x))*(np.exp(-x))

n=[4,8,16,32,64]

def simpson_one_third(a, b, n):
    h = (b - a) / n
    integral = func(a) + func(b)
    
    for i in range(1, n, 2):
        integral += 4 * func(a + i * h)
    
    for i in range(2, n-1, 2):
        integral += 2 * func(a + i * h)
    
    integral *= h / 3
    return integral

def simpson_three_eighth(a, b, n):
    h = (b - a) / n
    integral = func(a) + func(b)
    
    for i in range(1, n, 3):
        integral += 3 * func(a + i * h)
    
    for i in range(2, n, 3):
        integral += 3 * func(a + i * h)
    
    for i in range(3, n, 3):
        integral += 2 * func(a + i * h)
    
    integral *= 3 * h / 8
    return integral

def romberg(a, b, n):
    R1 = np.zeros((n, n))
    for i in range(n):
        R1[i, 0] = simpson_one_third(a, b, 2**(i + 1))
    
    for j in range(1, n):
        for i in range(n - j):
            factor = 16**j
            R1[i, j] = (factor * R1[i + 1, j - 1] - R1[i, j - 1]) / (factor - 1)
    R2 = np.zeros((n, n))
    for i in range(n):
            R2[i, 0] = simpson_three_eighth(a, b, 3 * 2**i)
        
    for j in range(1, n):
        for i in range(n - j):
            factor = 16**j
            R2[i, j] = (factor * R2[i + 1, j - 1] - R2[i, j - 1]) / (factor - 1)
    return (R1[0, n-1], R2[0, n-1])

exact_value = 0.58948722320
a=0
b=np.pi
print("Simpson's 1/3 Rule Approximations:")
for num in n:
    approx = simpson_one_third(a, b, num)
    error = abs(approx - exact_value)
    print(f"n={num}: Approximation={approx}, Error={error}")
print("\nSimpson's 3/8 Rule Approximations:")
for num in n:
    approx = simpson_three_eighth(a, b, num)
    error = abs(approx - exact_value)
    print(f"n={num}: Approximation={approx}, Error={error}")
print("\nRomberg Integration Approximations:")
for num in n:
    R1, R2 = romberg(a, b, int(np.log2(num)))
    error1 = abs(R1 - exact_value)
    error2 = abs(R2 - exact_value)
    print(f"n={num}: Simpson's 1/3 Approximation={R1}, Error={error1}")
    print(f"n={num}: Simpson's 3/8 Approximation={R2}, Error={error2}\n")