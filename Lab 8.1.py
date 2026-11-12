import numpy as np

def divided_difference_table(x_data,y_data):
    n=len(x_data)
    table=np.zeros((n,n))
    table[:,0]=y_data
    for j in range(1,n):
        for i in range(n-j):
            table[i][j]=(table[i+1,j-1]-table[i,j-1])/(x_data[i+j]-x_data[i])
    return table

def newton_polynomial(x_data,coeff,x_eval):
    n=len(coeff)
    result=coeff[n-1]
    for i in range(n-2,-1,-1):
        result=result*(x_eval-x_data[i])+coeff[i]
    return result

x_data=np.array([0.00,0.08,0.19,0.33,0.50,0.72,0.99,1.31,1.68,2.10])
y_data=np.array([1.000,1.084,1.218,1.406,1.686,2.099,2.687,3.540,4.747,6.404])

dd_table=divided_difference_table(x_data,y_data)
coeff=dd_table[0,:]

def deriv_3pt(x_data,y_data,x_eval):
    n=len(x_data)
    idx=np.argmin(np.abs(x_data-x_eval))
    if idx==0:
        ids=[0,1,2]
    elif idx==n-1:
        ids=[n-3,n-2,n-1]
    else:
        ids=[idx-1,idx,idx+1]
    xs=x_data[ids]
    ys=y_data[ids]
    A=np.vander(xs,3)
    a,b,c=np.linalg.solve(A,ys)
    fp=2*a*x_eval+b
    fpp=2*a
    return ids,xs,fp,fpp

for x in [0.33,0.50,0.72]:
    ids,xs,fp,fpp=deriv_3pt(x_data,y_data,x)
    print(f"\nFor x={x}:")
    print(f"Selected points: {xs}")
    print(f"First derivative: {fp}")
    print(f"Second derivative: {fpp}")

def newton_to_power_coeffs(x_nodes,b_coeffs):
    n=len(b_coeffs)
    power_poly=np.array([b_coeffs[0]])
    term=np.array([1.0])
    for k in range(1,n):
        term=np.convolve(term,np.array([-x_nodes[k-1],1.0]))
        if len(term)>len(power_poly):
            power_poly=np.pad(power_poly,(0,len(term)-len(power_poly)))
        power_poly=power_poly+b_coeffs[k]*np.pad(term,(0,len(power_poly)-len(term)))
    return power_poly

c_inc=newton_to_power_coeffs(x_data,coeff)
c_dec=c_inc[::-1]
print("\nPolynomial Coefficients:")
print(c_dec)
c1_der=np.polyder(c_dec,1)
c2_der=np.polyder(c_dec,2)

roots=np.roots(c1_der)
real_roots=[r.real for r in roots if abs(r.imag)<1e-6 and x_data[0]<=r.real<=x_data[-1]]
print("\nCritical points: ",real_roots)

candidates = [x_data[0],x_data[-1]]+real_roots
vals=[(xi,np.polyval(c_dec,xi)) for xi in candidates]
max_val=max(vals,key=lambda t:t[1])
print(f"\nMax at x={max_val[0]} and y={max_val[1]}")
min_val=min(vals,key=lambda t:t[1])
print(f"Min at x={min_val[0]} and y={min_val[1]}")








