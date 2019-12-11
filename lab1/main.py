import random

def GramSchmidt(*a):
    k = len(a[0])
    N = len(a)
    b = [[0] * k for i in range(N)]
    b[0] = a[0]
    for i in range(1,N):
        sum = a[i]
        for j in range(0,i):
            scolar_ab = 0
            scolar_bb = 0
            proj = [i for i in range(k)]
            for n in range(k):
                scolar_ab += b[j][n] * a[i][n]
                scolar_bb += b[j][n] * b[j][n]
            for n in range(k):
                proj[n] = (scolar_ab / scolar_bb) * b[j][n]
            for n in range(k):
                sum[n] -= proj[n]
        b[i] = sum
    return b

l1=[random.randrange(0,10) for i in range(3)]
l2=[random.randrange(0,10) for i in range(3)]
l3=[random.randrange(0,10) for i in range(3)]
print(l1,"\n",l2,"\n",l3)
print(GramSchmidt(l1,l2,l3))