import math

def f(x,y):
    return (y**2-2*x)/(y**2+x)

def rk4(x,y,h):
    k1=f(x,y)
    k2=f(x+h/2,y+h*k1/2)
    k3=f(x+h/2,y+h*k2/2)
    k4=f(x+h,y+h*k3)
    return y+h*(k1+2*k2+2*k3+k4)/6

x0=0
y0=1
h=0.1
n=15
rk_values={}

x=x0
y=y0
for i in range(n):
    y=rk4(x,y,h)
    x=x+h
    if round(x,1) in [0.5,1.0,1.5]:
        rk_values[round(x,1)]=y


x=x0
y=y0
me_values={}

for i in range(n):
    k1=f(x,y)
    yp=y+h*k1
    k2=f(x+h,yp)
    y=y+(h/2)*(k1+k2)
    x=x+h

    if round(x,1) in [0.5,1.0,1.5]:
        me_values[round(x,1)]=y

print("\nComparision of RK4 and Modified Euler:\n")
print("x\tRK4(y)\t\tModified Euler(y)")
for x in [0.5,1.0,1.5]:
    print(f"{x:.1f}\t{rk_values[x]:.6f}\t{me_values[x]:.6f}")