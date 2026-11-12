import numpy as np
import math

def newton_divided_difference(x,y):
    n=len(x)
    table=np.zeros((n,n))
    table[:,0]=y
    for j in range(1,n):
        for i in range(n-j):
            table[i,j]=(table[i+1,j-1]-table[i,j-1])/(x[i+j]-x[i])
    return table

def newton_divided_interpolation(x_test,x_data,table):
    n=len(x_data)
    result=table[0,0]
    for j in range(1,n):
        term = table[0,j]
        for i in  range(j):
            term*=(x_test-x_data[i])
        result+=term
    return result

x=np.array([0.0,0.3,0.9,2.0,2.4,3.1,3.8,4.2,4.7,4.8])
y=np.sin(x)
n=len(x)

table=newton_divided_difference(x,y)

x_test=1.8

result=newton_divided_interpolation(x_test,x,table)
abs_error=abs(np.sin(x_test)-result)

prod_term=np.prod([x_test-xi for xi in x])
max_deriv=1
for i in range(1,n+2):
    max_deriv/=i
error_bound=max_deriv*prod_term

print("\nNEWTON'S DIVIDED DIFFERENCE INTERPOLATION:\n")
print(f"\nEstimated value f({x_test}) = {result}\n")
print(f"Actual Value f({x_test}) = {np.sin(x_test)}\n")
print(f"Absolute Error = {abs_error}\n")
print(f"Error Bound = {error_bound}\n")



