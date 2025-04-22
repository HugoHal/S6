import csv

fasta_file = "sequencesTP7.fasta"
output_csv = "composition.csv"

def calcule_compo(sequence):
    length = len(sequence)
    taux_a = sequence.count('A') / length
    taux_t = sequence.count('T') / length
    taux_c = sequence.count('C') / length
    taux_g = sequence.count('G') / length
    return {'A': taux_a, 'T': taux_t, 'C': taux_c, 'G': taux_g, 'Length': length}

# Lecture du fichier FASTA et traitement
sequences = {}
with open(fasta_file, "r") as f:
    identifiant = None
    sequence = ""
    for line in f:
        line = line.strip()
        if line.startswith(">"):
            if identifiant is not None:
                sequences[identifiant] = sequence
            identifiant = line[4:]  # Enlève le '>'
            identifiant = identifiant.split(" ")[0]
            sequence = ""
        else:
            sequence += line.upper()  # On concatène les lignes de séquence
    if identifiant is not None:
        sequences[identifiant] = sequence  # Pour la dernière séquence

# Écriture dans le fichier CSV
with open(output_csv, "w", newline='') as csvfile:
    writer = csv.writer(csvfile, delimiter=';')
    writer.writerow(['Identifiant', 'Longueur', 'Taux de A', 'Taux de C', 'Taux de G', 'Taux de T'])
    
    for identifiant, sequence in sequences.items():
        compo = calcule_compo(sequence)
        writer.writerow([
            identifiant,
            compo['Length'],
            round(compo['A'], 3),
            round(compo['C'], 3),
            round(compo['G'], 3),
            round(compo['T'], 3)
        ])

