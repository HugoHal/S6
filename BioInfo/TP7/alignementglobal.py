def s(a, b, gap_penalty):
    """Fonction de score de substitution : 0 si match, sinon pénalité."""
    return 0 if a == b else gap_penalty

def make_beautiful(seq):
    """Ajoute un '_' au début pour simuler un index à 1 (optionnel)."""
    return ['_'] + list(seq)

def calc_diff(A, B, gap_penalty):
    """Remplit la matrice d'alignement globale."""
    A = make_beautiful(A)
    B = make_beautiful(B)
    M = [[0 for _ in range(len(B))] for _ in range(len(A))]

    for i in range(len(A)):
        for j in range(len(B)):
            if i == 0 and j == 0:
                M[i][j] = 0
            elif i == 0:
                M[i][j] = j * gap_penalty
            elif j == 0:
                M[i][j] = i * gap_penalty
            else:
                match = M[i-1][j-1] + s(A[i], B[j], gap_penalty)
                delete = M[i-1][j] + gap_penalty
                insert = M[i][j-1] + gap_penalty
                M[i][j] = min(match, delete, insert)
    return M

def align_sequences(A, B, gap_penalty):
    """Fait le traceback pour obtenir l'alignement optimal."""
    M = calc_diff(A, B, gap_penalty)
    i, j = len(M) - 1, len(M[0]) - 1
    alignment = [(i, j)]
    values = [M[i][j]]

    while (i, j) != (0, 0):
        current = M[i][j]
        options = []

        if i > 0 and j > 0:
            options.append((M[i-1][j-1] + s(A[i], B[j], gap_penalty), (i-1, j-1)))
        if i > 0:
            options.append((M[i-1][j] + gap_penalty, (i-1, j)))
        if j > 0:
            options.append((M[i][j-1] + gap_penalty, (i, j-1)))

        best_score, best_move = min(options, key=lambda x: x[0])
        alignment.append(best_move)
        values.append(M[best_move[0]][best_move[1]])
        i, j = best_move

    return alignment[::-1], values[::-1]

# === Exemple d'utilisation ===
seq1 = "ACTG"
seq2 = "ACG"
gap_penalty = 3

alignment, scores = align_sequences(seq1, seq2, gap_penalty)

print("Alignement (coordonnées):", alignment)
print("Valeurs (scores):", scores)
