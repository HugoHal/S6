import math
import random

def P(alph, t):
    """Construit la matrice de transition selon le modèle de Jukes-Cantor."""
    e = math.exp(-4 * alph * t)
    base_prob = 1 / 4
    diff_prob = (1 / 4) - (1 / 4) * e
    same_prob = (1 / 4) + (3 / 4) * e
    matrix = {
        "A": {"A": same_prob, "T": diff_prob, "C": diff_prob, "G": diff_prob},
        "T": {"A": diff_prob, "T": same_prob, "C": diff_prob, "G": diff_prob},
        "C": {"A": diff_prob, "T": diff_prob, "C": same_prob, "G": diff_prob},
        "G": {"A": diff_prob, "T": diff_prob, "C": diff_prob, "G": same_prob}
    }
    return matrix

def muter_sequence(matrix, seq):
    """Fait muter chaque nucléotide de la séquence selon la matrice de transition."""
    nouvelle_seq = []
    for base in seq:
        probas = list(matrix[base].values())
        bases = list(matrix[base].keys())
        nouvelle_base = random.choices(bases, weights=probas, k=1)[0]
        nouvelle_seq.append(nouvelle_base)
    return nouvelle_seq

def ajuster_taille(seq, taille):
    """Ajuste la séquence à la taille demandée en répétant le début si nécessaire."""
    if len(seq) >= taille:
        return seq[:taille]
    repetition = (taille // len(seq)) + 1
    return (seq * repetition)[:taille]

def generation_finale(alph, t, n, taille, fichier):
    """Lit les séquences d'un fichier fasta, les mute n fois et écrit le résultat."""
    sequences = {}
    name = ""
    sequence = ""
    matrix = P(alph, t)

    with open(fichier, "r") as f:
        for ligne in f:
            ligne = ligne.strip()
            if not ligne:
                continue
            if ligne.startswith(">"):
                if name:
                    sequences[name] = list(sequence.upper())
                name = ligne
                sequence = ""
            else:
                sequence += ligne
        if name:  # dernière séquence
            sequences[name] = list(sequence.upper())

    with open("JC.fasta", "w") as f:
        for nom, seq in sequences.items():
            base_seq = ajuster_taille(seq, taille)
            for i in range(n):
                mutated_seq = muter_sequence(matrix, base_seq)
                f.write(f"{nom}_mutation{i+1}\n")
                f.write("".join(mutated_seq) + "\n")

# Exemple d'appel
generation_finale(0.01, 5, 3, 100, "sequencesTP7.fasta")

