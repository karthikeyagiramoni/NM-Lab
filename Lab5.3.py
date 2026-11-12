def forward_table(y):
    n=len(y)
    table=[[0]*n for _ in range(n)]
    for i in range(n):
        table[i][0]=y[i]

    for j in range(1,n) :
        for i in range(n-j):
            table[i][j]=table[i+1][j-1]-table[i][j-1]

    return table

x=[1.0,1.5,2.0,2.5,3.0,3.5]
y=[2.0,3.5,5.8,9.2,14.7,21.0]

table=forward_table(y)

print("Forward Difference Table:\n")
for i in range(len(y)):
    row=[f"{table[i][j]:.2f}" for j in range(len(y)-i)]
    print(row)