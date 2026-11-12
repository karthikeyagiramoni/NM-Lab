import numpy as np
import math

def forward_difference_table(y):
    n=len(y)
    table=np.zeros((n,n))
    table[:,0]=y
    for j in range(1,n):
        for i in range(0,n-j):
            table[i,j]=table[i+1,j-1]-table[i,j-1]
    return table

def newton_interpolation(x,x0,h,table):
    u=(x-x0)/h
    n=len(table)
    u_term=1
    result=table[0,0]
    for j in range(1,n):
        u_term=u_term*(u-(j-1))/j
        result+=u_term*table[0,j]
    return result

n=30
x_data=np.linspace(0,3,n)
y_data=np.exp(x_data)

table=forward_difference_table(y_data)
x_test=1.2
x0=x_data[0]
h=x_data[1]-x_data[0]

y_interp=newton_interpolation(x_test,x0,h,table)
y_exact=math.exp(x_test)

abs_error=abs(y_interp-y_exact)
rel_error=abs_error/abs(y_exact)
print(f"Interpolated y(1.2)= {y_interp}")
print(f"Actual y(1.2)= {y_exact}")
print(f"Absolute Error= {abs_error}")
print(f"Relative Error= {rel_error}")