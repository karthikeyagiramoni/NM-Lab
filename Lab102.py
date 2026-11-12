import math

def f(x,y):
    return x*math.sqrt(y)

def exact(x):
    return ((x*x+3)/4)**2

def euler(x0,y0,h,n):
    x=x0
    y=y0

    values=[(x,y)]
    for i in range(n):
        y=y+h*f(x,y)
        x=x+h

        values.append((x,y))
    return values

def modifiedEuler(x0,y0,h,n):
    x=x0
    y=y0

    values=[(x,y)]
    for i in range(n):
        k1=f(x,y)
        y_p=y+h*k1
        k2=f(x+h,y_p)
        y_c=y+h*(k1+k2)/2
        y=y_c
        x=x+h
        values.append((x,y))
    return values

x0=1
y0=1
h=1
n=3

euler_values=euler(x0,y0,h,n)
modified_euler_values=modifiedEuler(x0,y0,h,n)

print("\nQUESTION 2:\n")
print("(a,b,c)")

print("{:<8} {:<15} {:<15} {:<15} {:<15}".format(
    "x", "Euler", "Modified Euler", "Exact", "Euler Error"
))

euler_max=[0,0]
modified_max=[0,0]

for i in range(n + 1):

    x = euler_values[i][0]
    ye = euler_values[i][1]
    ym = modified_euler_values[i][1]
    yt = exact(x)

    error_e = abs(yt - ye)
    error_m = abs(yt - ym)

    if euler_max[1]<error_e:
        euler_max[1]=error_e
        euler_max[0]=x
    if modified_max[1]<error_m:
            modified_max[1]=error_m
            modified_max[0]=x

    print("\n{:<8} {:<15.6f} {:<15.6f} {:<15.6f} {:<15.6f}".format(
        x, ye, ym, yt, error_e
    ))

    print("         Modified Euler Error = {:.6f}".format(error_m))


print("\n(d)Euler Method:")
print("Maximum error at x=",euler_max[0]," Error=",euler_max[1])
print("\nModified Euler Method:")
print("Maximum error at x=",modified_max[0]," Error=",modified_max[1])


