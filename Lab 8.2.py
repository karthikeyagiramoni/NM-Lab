import numpy as np
t=np.array([0,100,200,300,400,500,600,700,800,900,1000,1100,1200])
s=np.array([0.0,4.6,18.9,43.7,80.8,132.4,199.7,284.9,389.6,515.8,665.1,839.7,1041.4])

h=100.0

def forward_diff_table(y,order=4):
    n=len(y)
    table=np.zeros((n,order+1))
    table[:,0]=y
    for j in range(1,order+1):
        for i in range(n-j):
            table[i,j]=table[i+1,j-1]-table[i,j-1]
    return table

fd=forward_diff_table(s,4)
print("\nForward Difference Table:")
print(fd)

def velocity_central(t_data,s_data,t0,h):
    idx=np.searchsorted(t_data,t0)

    if idx<4:idx=2
    if idx>len(t_data)-3:idx=len(t_data)-3

    xs=t_data[idx-2:idx+3]
    fs=s_data[idx-2:idx+3]
    coeff=np.polyfit(xs,fs,4)
    dcoeff=np.polyder(coeff)
    return np.polyval(dcoeff,t0)

for tt in [430,670,860,910]:
    v=velocity_central(t,s,tt,h)
    print(f"Velocity at t={tt}s : {v:.6f} km/s ")

def accel_central(t_data,s_data,t0,h):
    idx=np.searchsorted(t_data,t0)
    
    if idx<4:idx=2
    if idx>len(t_data)-3:idx=len(t_data)-3
    
    xs=t_data[idx-2:idx+3]
    fs=s_data[idx-2:idx+3]
    coeff=np.polyfit(xs,fs,4)
    d2coeff=np.polyder(coeff,2)
    return np.polyval(d2coeff,t0)

for tt in [525,720]:
    a=accel_central(t,s,tt,h)
    print(f"Acceleration at t={tt}s : {a:.6f} km/s ")

acc_all=[accel_central(t,s,ti,h,) for ti in t[2:-2]]
print("Accel variation: " ,np.min(acc_all)," to ",np.max(acc_all),"km/s2")
if np.std(acc_all)<0.0005:
    print("Uniform Acceleration")
else:
    print("Non-uniform Acceleration")