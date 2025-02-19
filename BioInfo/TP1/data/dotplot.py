def lire_fasta(filename):
    with open(filename, "r") as file:
        return [line.strip() for line in file.readlines()[1:]]

def dot_plot(filename, diagonale):

    sequence = lire_fasta(filename)

    sequence1 = sequence[0]
    sequence2 = sequence[1]

    m = len(sequence1)
    n = len(sequence2)
    matrix = [['.'] * m for _ in range(n)]

    if (diagonale > 0):
        for i in range(n):
            for j in range(m):
                if (sequence1[i] == sequence2[j]):
                    valid = True

                    for l in range(diagonale):
                        if (i + l >= n or j + l >= m or sequence1[i+l] != sequence2[j+l]):
                            valid = False
                            break

                    if (valid):
                        for l in range(diagonale):
                            matrix[i+l][j+l] = '□'

    else:
        for i in range(n):
            for j in range(m):
                if (sequence1[i] == sequence2[j]):
                    matrix[i][j] = '□'


    print(f"\nSéquence 1 : {sequence1}\nSéquence 2 : {sequence2}\n")

    print(f"Dot plot avec fenêtre de taille {diagonale} :")
    print("   ", "    ".join(sequence2))
    for i in range(n):
        print(sequence1[i], matrix[i])

dot_plot('data/test.fasta', 3)