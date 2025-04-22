import numpy as np
from collections import defaultdict

def find_kmers(sequence, k):
    """Crée une table d'index des k-mers d'une séquence."""
    kmers = defaultdict(list)
    for i in range(len(sequence) - k + 1):
        kmer = sequence[i:i + k]
        kmers[kmer].append(i)
    return kmers

def find_seeds(seq1, seq2, k, threshold=5):
    """Trouve les k-mers communs entre deux séquences et regroupe ceux proches sur la même diagonale."""
    kmers1 = find_kmers(seq1, k)
    kmers2 = find_kmers(seq2, k)
    diagonals = defaultdict(list)

    for kmer in kmers1:
        if kmer in kmers2:
            for pos1 in kmers1[kmer]:
                for pos2 in kmers2[kmer]:
                    diag = pos1 - pos2
                    if diagonals[diag] and abs(pos1 - diagonals[diag][-1][0]) > threshold:
                        continue
                    diagonals[diag].append((pos1, pos2))
    return diagonals

def compute_initial_scores(diagonals, seq1, seq2, k):
    """Calcule les scores initiaux pour chaque région de similarité basée sur les diagonales."""
    scores = []
    for diag, positions in diagonals.items():
        score = 0
        for pos1, pos2 in positions:
            for i in range(k):
                if (pos1 + i < len(seq1)) and (pos2 + i < len(seq2)):
                    if seq1[pos1 + i] == seq2[pos2 + i]:
                        score += 2
                    else:
                        score -= 1
        scores.append((score, positions))
    scores.sort(reverse=True, key=lambda x: x[0])
    return scores[:10]  # Top 10 régions

def merge_regions(scores, gap_penalty=-1):
    """Fusionne les régions proches si leur score reste élevé après pénalité."""
    if not scores:
        return []

    merged_scores = [scores[0]]  # Commencer avec la meilleure région

    for i in range(1, len(scores)):
        score, positions = scores[i]
        combined_positions = merged_scores[0][1] + positions
        penalized_score = score - gap_penalty * len(positions)
        if penalized_score > merged_scores[0][0]:
            merged_scores[0] = (penalized_score, combined_positions)

    return merged_scores

def smith_waterman(seq1, seq2, match=2, mismatch=-1, gap=-1):
    """Algorithme Smith-Waterman pour alignement local optimal."""
    m, n = len(seq1), len(seq2)
    score_matrix = np.zeros((m + 1, n + 1))
    max_score = 0

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            match_mismatch = match if seq1[i - 1] == seq2[j - 1] else mismatch
            score_matrix[i, j] = max(
                0,
                score_matrix[i - 1, j - 1] + match_mismatch,
                score_matrix[i - 1, j] + gap,
                score_matrix[i, j - 1] + gap
            )
            if score_matrix[i, j] > max_score:
                max_score = score_matrix[i, j]

    return int(max_score)

def fasta_alignment(seq1, seq2, k=3):
    """Trouve les meilleures régions similaires entre deux séquences et évalue leur alignement local."""
    diagonals = find_seeds(seq1, seq2, k)
    initial_scores = compute_initial_scores(diagonals, seq1, seq2, k)
    merged_scores = merge_regions(initial_scores)
    
    if not merged_scores:
        return 0

    best_score, best_region = max(merged_scores, key=lambda x: x[0])

    # Extraire un alignement local autour de la première position
    pos1, pos2 = best_region[0]
    window = max(20, k)  # fenêtre raisonnable pour l'alignement
    sub_seq1 = seq1[pos1:pos1 + window]
    sub_seq2 = seq2[pos2:pos2 + window]
    
    return smith_waterman(sub_seq1, sub_seq2)

# Exemple d'utilisation
if __name__ == "__main__":
    seq1 = "ACGTGCACTG"
    seq2 = "TGCACTGACG"
    score = fasta_alignment(seq1, seq2)
    print("Meilleur score d'alignement local:", score)
