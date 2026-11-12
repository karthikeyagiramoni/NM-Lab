x=[1,2,3,4,5,6,7]
y=[3,11,None,69,131,223,351]

for M in range(-100,500):
    yt=[3,11,M,69,131,223,351]

    d1=[yt[i+1]-yt[i] for i in range(6)]
    d2=[d1[i+1]-d1[i] for i in range(5)]
    d3=[d2[i+1]-d2[i] for i in range(4)]
    if len(set(d3))==1:
        print(f"Missing value: y[3]={M}")
        break