import numpy as np
import math

def lagrange_interolation(x,xd,yd):
    n=len(xd)
    result=0.0
    for i in range(n):
        Li=1.0
        for j in range(n):
            if i!=j :
                Li=Li*(x-xd[j])/(xd[i]-xd[j])
        result+=Li*yd[i]
    return result


x_all=np.array([0,0.35,0.55,0.65,0.88,1,1.37,1.5,1.91,2])
y_all=1/(1+x_all)

indices=[3,4,5,6]

x_data=x_all[indices]
y_data=y_all[indices]

x_test=1.25
y_interp=lagrange_interolation(x_test,x_data,y_data)
y_exact=1/(1+x_test)
abs_error=abs(y_exact-y_interp)

n_order=4
prod_term=np.prod([x_test-xi for xi in x_data])
max_deriv=120/(1+min(x_data))**6
error_bound=max_deriv/math.factorial(5)*abs(prod_term)

print(f"Points used for P4: {x_data}")
print(f"(a) P4(1.25)= {y_interp}")
print(f"(b) Exact f(1.25)= {y_exact}")
print(f"(c) Absolute Error= {abs_error}")
print(f"(d) Error Bound= {error_bound}")