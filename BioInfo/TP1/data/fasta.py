import numpy as np
from collections import defaultdict
import sys

def find_kmers(sequence, k):
    """Crée une table d'index des k-mers d'une séquence."""
    kmers = defaultdict(list)
    for i in range(len(sequence) - k + 1):
        kmers[sequence[i:i + k]].append(i)
    return kmers

def find_seeds(seq1, seq2, k, threshold=5):
    """Trouve les mots identiques de taille k entre deux séquences et regroupe ceux proches sur une diagonale."""
    kmers1 = find_kmers(seq1, k)
    kmers2 = find_kmers(seq2, k)
    diagonals = defaultdict(list)
    
    for kmer in kmers1:
        if kmer in kmers2:
            for pos1 in kmers1[kmer]:
                for pos2 in kmers2[kmer]:
                    diag = pos1 - pos2
                    if diagonals[diag] and abs(pos1 - diagonals[diag][-1]) > threshold:
                        continue
                    diagonals[diag].append((pos1, pos2))
    return diagonals

def compute_initial_scores(diagonals, seq1, seq2, k):
    """Calcule les scores initiaux pour chaque région de similarité."""
    scores = []
    for diag, positions in diagonals.items():
        score = 0
        for pos1, pos2 in positions:
            for i in range(k):
                if seq1[pos1 + i] == seq2[pos2 + i]:
                    score += 2
                else:
                    score -= 1
        scores.append((score, positions))
    scores.sort(reverse=True, key=lambda x: x[0])
    return scores[:10]  # Garder les 10 meilleures régions

def merge_regions(scores, gap_penalty=-1):
    """Fusionne les régions proches si leur score combiné reste élevé."""
    init1 = scores[0][0] if scores else 0
    merged_scores = []
    
    for i in range(len(scores)):
        score, positions = scores[i]
        if i > 0 and (score - gap_penalty * len(positions)) > init1:
            merged_scores.append((score - gap_penalty * len(positions), positions))
    
    return merged_scores if merged_scores else scores

def smith_waterman(seq1, seq2, match=2, mismatch=-1, gap=-1):
    """Applique l'algorithme de Smith-Waterman pour un alignement local optimal."""
    m, n = len(seq1), len(seq2)
    score_matrix = np.zeros((m + 1, n + 1))
    max_score, max_pos = 0, (0, 0)
    
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            match_mismatch = match if seq1[i-1] == seq2[j-1] else mismatch
            score_matrix[i, j] = max(
                0,
                score_matrix[i-1, j-1] + match_mismatch,
                score_matrix[i-1, j] + gap,
                score_matrix[i, j-1] + gap
            )
            if score_matrix[i, j] > max_score:
                max_score, max_pos = score_matrix[i, j], (i, j)
    
    return max_score

def fasta_alignment(seq1, seq2, k=3):
    diagonals = find_seeds(seq1, seq2, k)
    initial_scores = compute_initial_scores(diagonals, seq1, seq2, k)
    merged_scores = merge_regions(initial_scores)
    best_region = max(merged_scores, key=lambda x: x[0])[1] if merged_scores else []
    
    if best_region:
        pos1, pos2 = best_region[0]
        aligned_seq1 = seq1[pos1:pos1 + k]
        aligned_seq2 = seq2[pos2:pos2 + k]
        return smith_waterman(aligned_seq1, aligned_seq2)
    
    return 0

# Exemple d'utilisation
seq1 = "ACGTGCACTG"
seq2 = "TGCACTGACG"
score = fasta_alignment(seq1, seq2)
print("Meilleur score d'alignement local:", score)