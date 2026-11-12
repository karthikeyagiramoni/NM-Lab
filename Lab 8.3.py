import numpy as np

x=np.array([0.0,0.2,0.4,0.6,.8,1.0,1.2,1.4,1.6])
f=np.array([1.0,1.040811,1.168731,1.411993,1.810656,2.718282,4.060156,6.550203,11.023176])

def central_first(f_plus,f_minus,h):
    return (f_plus-f_minus)/(2*h)

def central_second(f_plus,f0,f_minus,h):
    return (f_plus-2*f0+f_minus)/(h*h)

fp_h04=central_first(f[7],f[3],0.4)
fpp_h04=central_second(f[7],f[5],f[3],0.4)
print(f"\nh=0.4: f'(1.0)={fp_h04:.6f},f''(1.0)={fpp_h04:.6f}")

fp_h02=central_first(f[6],f[4],0.2)
fpp_h02=central_second(f[6],f[5],f[4],0.2)
print(f"\nh=0.2: f'(1.0)={fp_h02:.6f},f''(1.0)={fpp_h02:.6f}")

r=0.5
p=2
D_h1 = fp_h04
D_h2 = fp_h02
d_rich = D_h2+(D_h2-D_h1)/((1/r)**p-1)
print(f"\nRichardson improved f'(1.0) = {d_rich:.6f}")

import math

true_fp=math.e
print(f"\ntrue if e^x: {true_fp},error h0.4={abs(true_fp-fp_h04)},h0.2={abs(true_fp-fp_h02)}, rich={abs(true_fp-d_rich)}")

