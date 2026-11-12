import math

def f(x,y):
    return 1/(1+x*x)-2*y*y

def exact(x):
    return x/(1+x*x)

def rk4(x,y,h):
    k1=f(x,y)
    k2=f(x+h/2,y+h*k1/2)
    k3=f(x+h/2,y+h*k2/2)
    k4=f(x+h,y+h*k3)
    return y+h*(k1+2*k2+2*k3+k4)/6


h=0.1
x=[0,0.1,0.2,0.3,0.4,0.5]
y=[0]

for i in range(1,4):
    y.append(exact(x[i]))



for i in range(3,5):
    f0=f(x[i],y[i])
    f1=f(x[i-1],y[i-1])
    f2=f(x[i-2],y[i-2])
    f3=f(x[i-3],y[i-3])

    yp=y[i]+(h/24)*(55*f0-59*f1+37*f2-9*f3)
    fp=f(x[i]+h,yp)
    yc=y[i]+(h/24)*(9*fp+19*f0-5*f1+f2)
    err=abs(yp-yc)
    while err>0.0005:
        yp=yc
        fp=f(x[i]+h,yp)
        yc=y[i]+(h/24)*(9*fp+19*f0-5*f1+f2)
        err=abs(yp-yc)
    y.append(yc)

print("\nx\tNumerical(y)\tExact(y)\tAbs Error")

for i in range(6):
    ex=exact(x[i])
    error=abs(ex-y[i])
    print(f"{x[i]}\t{y[i]:.6f}\t{ex:.6f}\t{error}")