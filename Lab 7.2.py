import numpy as np
import math

def newton_divided_differnce(x,y):
    n=len(x)
    table=np.zeros((n,n))
    table[:,0]=y
    for j in range(1,n):
        for i in range(n-j):
            table[i,j]=(table[i+1,j-1]-table[i,j-1])/(x[i+j]-x[i])
    return table

def newton_divided_differnce_interpolation(x_test,x,table):
    n=len(x)
    result=table[0,0]

    for j in range(1,n):
        term=table[0,j]
        for i in range(j):
            term*=(x_test-x[i])
        result+=term
    return result

x_data=np.array([-1.0,-0.85,-0.7,-0.55,-0.4,-0.25,-0.1,0.05,0.2,0.35,0.5,0.65,0.8,1.0])
y_data=1/(1+25*x_data**2)
table=newton_divided_differnce(x_data,y_data)

x_test=np.array([-0.9,-0.6,-0.3,0.0,0.3,0.6,0.9])
n=len(x_test)
y_test=1/(1+25*x_test**2)
test_result=np.array([newton_divided_differnce_interpolation(xi,x_data,table) for xi in x_test])

abs_error=np.abs(y_test-test_result)
rel_error=abs_error/np.abs(y_test)*100
for i in range(n):
    print(f"\nEstimated value f({x_test[i]}) = {test_result[i]}")
    print(f"Actual value f({x_test[i]}) = {y_test[i]}")
    print(f"Absolute Error = {abs_error[i]}")
    print(f"Relative Error = {rel_error[i]}%\n")
    