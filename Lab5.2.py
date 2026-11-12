import numpy as np
def thomas_param(alpha,beta):
    a=[0,-1,-1,-1]
    b=[2,alpha,beta,2]
    c=[-1,-1,-1,0]
    d=[1,2,2,1]

    b_mod=b[:]
    d_mod=d[:]

    try:
        for i in range(1,4):
            if abs(b_mod[i-1])<1e-12 :
                return False,i,None
            w=a[i]/b_mod[i-1]
            b_mod[i]-=w*c[i-1]
            d_mod[i]-=w*d_mod[i-1]
        if abs(b_mod[3])<1e-12 :
            return False,4,None
        x=[0]*4
        x[3]=d_mod[3]/b_mod[3]
        for i in range(2,-1,-1):
            x[i]=(d_mod[i]-c[i]*x[i+1])/b_mod[i]
        return True,-1,x
    except ZeroDivisionError:
        return False,i+1,None

params=[(1/2,1),(2,2),(1/5,1/3),(0,2),(3/2,1),(2,2/3),(1,1)]

print("\nSOLUTION TABLE:\n")
for al,be in params:
    ok,step,sol=thomas_param(al,be)
    if ok:
        print(chr(945),f"={al}  ",chr(946),f"={be}  SUCCESS-> sol={sol}\n")
    else:
        print(chr(945),f"={al}  ",chr(946),f"={be} FAILED at Elimination Step {step}\n")