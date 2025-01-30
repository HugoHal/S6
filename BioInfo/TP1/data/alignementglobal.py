fastafile1 = 'BioInfo/TP1/data/actin_xenopus_ADN.fasta'
fastafile2 = 'BioInfo/TP1/data/actin_xenopus_mRNA.fasta'

file1 = open(fastafile1)
file2 = open(fastafile2)

g = 3
match = 0

def s(a,b,g):
    if a == b :
        return 0
    else :
        return g

def recupdata(file):
    file.readline()
    Lines = file.readlines()
    A = []
    for i in Lines:
        for j in range(len(i)):
            if len(A) < 10 :
                A.append(i[j])
    return A

B = recupdata(file1)
A = recupdata(file2)

def makebeautiful(A):
    A.reverse()
    A.append('_')
    A.reverse()
    return A

def CalcDif(A,B, g):
    A = makebeautiful(A)
    B = makebeautiful(B)
    M = [[0 for j in range(len(B))] for i in range(len(A))]
    for i in range(len(A)):
        for j in range(len(B)):
            if i == 0 and j == 0 :
                M[i][j] = 0
            elif j == 0 :
                M[i][j] = g*i
            elif i == 0 :
                M[i][j] = g*j
            else :
                M[i][j]=min((M[i-1][j-1]+s(A[i],B[j],g)), (M[i-1][j]+g),(M[i][j-1]+g))
    return M

M = CalcDif(A,B,g)
for i in M:
    print(i)

def alignementotpi(M,A,B,g):
    x = len(M)-1
    y = len(M[x])-1
    align = [(x,y)]
    valfi = [M[x][y]]
    while align[-1] != (0,0):
        i = align[-1][0]
        j = align[-1][1]
        a = M[i-1][j-1]+s(A[i],B[j],g)
        b = M[i-1][j]+g
        c = M[i][j-1]+g
        if a <= min(b,c):
            align.append((i-1,j-1))
            valfi.append(M[i-1][j-1])
        elif b < min(a,c):
            align.append((i-1,j))
            valfi.append(M[i-1][j])
        else :
            align.append((i,j-1))
            valfi.append(M[i][j-1])
    return align, valfi

align, valfi = alignementotpi(M,A,B,g)
print(align)
print(valfi)