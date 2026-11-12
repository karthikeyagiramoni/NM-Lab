import math

def  f(x,y):
    return (math.exp(-x*x-y*y))/(1+x+y)

def trapezoidal(h,k):
    xn=(int)(round(1/h))
    yn=(int)(round(1/k))
    ans=0
    for i in range(xn+1):
        wx=1
        if i==0 or i==xn:
            wx=0.5
        else:
            wx=1
        
        for j in range(yn+1):
            wy=1
            if j==0 or j==yn:
                wy=0.5
            else:
                wy=1
            ans+=wx*wy*f(i*h,j*k)
    return ans*h*k

def simpson(h,k):
    xn=(int)(round(1/h))
    yn=(int)(round(1/k))
    ans=0
    if xn%2!=0 or yn%2!=0:
        return ValueError("Number of subintervals must be even")
    for i in range(xn+1):
        wx=1
        if i==0 or i==xn:
            wx=1
        elif i%2==1:
            wx=4
        else:
            wx=2

        for j in range(yn+1):
            wy=1
            if j==0 or j==yn:
                wy=1
            elif j%2==1:
                wy=4
            else:
                wy=2
            ans+=wx*wy*f(i*h,j*k)
    return ans*(h*k/9)

def mixed(h,k):
    xn=(int)(round(1/h))
    yn=(int)(round(1/k))
    ans=0
    if  yn%2!=0:
            return ValueError("Number of subintervals must be even")
    for i in range(xn+1):
        wx=0
        if i==0 or i==xn:
            wx=0.5
        else:
            wx=1
        temp=0
        for j in range(yn+1):
            wy=0
            if j==0 or j==yn:
                wy=1
            elif j%2==0:
                wy=2
            else:
                wy=4
            temp+=wy*f(h*i,k*j)

        ans+=temp*wx/3
    return ans*h*k

exact=0.31614002
print("QUESTION 1:\n")
print("\n(a)Composite Trapezoidal Rule with h=0.25 k=0.25 :")
print("I = ",trapezoidal(0.25,0.25))
print("Error = ",abs(trapezoidal(0.25,0.25)-exact))

print("\n(b)Composite Simpson's 1/3 Rule with h=0.25 k=0.25 :")
print("I = ",simpson(0.25,0.25))
print("Error = ",abs(simpson(0.25,0.25)-exact))

print("\nComposite Simpson's 1/3 Rule with h=0.25 k=0.125 :")
print("I = ",simpson(0.25,0.125))
print("Error = ",abs(simpson(0.25,0.125)-exact))

print("\n(c)Simpson's Rule gives more accurate result than Trapezoidal Rule with same h and k values.")
print("Reducing the step size increases the number of mesh points and generally improves accuracy.")

print("\n(d)Mixed method with h=0.25 k=0.25 :")
print("I = ",mixed(0.25,0.25))
print("Error = ",abs(mixed(0.25,0.25)-exact))
