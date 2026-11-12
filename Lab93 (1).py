import numpy as np
x=[0,0.5,1.0,1.5,2.0,2.5,3.0]
y=[1.0,1.6487,2.7183,4.4817,7.3891,12.1825,20.0855]

a=0
b=3

def func(k):
    value=x.index(k)
    return y[value]

def trapezoidal(a, b, n):
    h = (b - a) / n
    integral = 0.5 * (func(a) + func(b))
    
    for i in range(1, n):
        integral += func(a + i * h)
    
    integral *= h
    return integral

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
exact_value = 19.085536923188
n=len(x)
trapezoidal_result = trapezoidal(a, b, n-1)
simpson_one_third_result = simpson_one_third(a, b, n-1)
simpson_three_eighth_result = simpson_three_eighth(a, b, n-1)
print(f"Trapezoidal Rule Result: {trapezoidal_result} Error: {abs(trapezoidal_result - exact_value)}")
print(f"Simpson's 1/3 Rule Result: {simpson_one_third_result} Error: {abs(simpson_one_third_result - exact_value)}")
print(f"Simpson's 3/8 Rule Result: {simpson_three_eighth_result} Error: {abs(simpson_three_eighth_result - exact_value)}")
