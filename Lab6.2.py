import numpy as np
import math

def backward_difference_table(y):
    n=len(y)
    table=np.zeros((n,n))
    table[:,0]=y
    for j in range(1,n):
        for i in range(j,n):
            table[i,j]=table[i,j-1]-table[i-1,j-1]
    return table

def newton_interpolation(x,x_data,h,table):
    n=len(x_data)
    u=(x-x_data[-1])/h
    u_term=1
    result=table[n-1,0]
    for i in range(1,n):
        u_term=u_term*(u+(i-1))/i
        result+=u_term*table[n-1,i]
    return result

x_data=np.array([0,0.2,0.4,0.6,0.8,1.0,1.2,1.4,1.6,1.8,2.0])
y_data=np.array([8.0000,6.4800,4.7203,2.7301,0.6142,-1.0000,0.4398,12.9810,57.8395,184.0393,494.0000])

x_test=1.7
n=len(x_data)
xn=x_data[n-1]
h=x_data[1]-x_data[0]

table=backward_difference_table(y_data)
print("\nBackward Difference Table:")
print(table)

result1=newton_interpolation(x_test,x_data,h,table)
table2=backward_difference_table(y_data[-5:])
result2=newton_interpolation(x_test,x_data[-5:],h,table2)

print(f"The estimated value f(1.7)= {result1}")
print(f"The estimated value using only first 5 datapoints f(1.7)= {result2}")



