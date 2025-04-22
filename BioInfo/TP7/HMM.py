import random

class HMM:
    sigma = [ 'A', 'C', 'G', 'T']
    
    def __init__(self, states = [1], depart = [1], emission = [[0.25, 0.25, 0.25, 0.25]], transition = [[1]]):
        self.S = states
        self.P = depart
        self.E = emission
        self.T = transition

    def print(self):
        print("États :")
        print(self.S)
        print("Probabilités de départ :")
        print(self.P)
        print("Probabilités d'émission :")
        print(self.E)
        print("Probabilités de transition :")
        print(self.T)
        
    def fromAlignement(self,a,L):
        # Les états
        states = []
        for i in range(len(L)):
            states.append(i+1)
        self.S = states
        # Initialisation du départ
        dep = [1.0]
        for i in range(1,len(self.S)):
            dep.append(0.0)
        self.P = dep
        # Récupération des fréquences d'émission ensembles de colonnes par ensembles de colonnes
        self.E = []
        for i in range(len(self.S)):
            freq = {'A':0,'C':0,'G':0,'T':0}
            somme = 0
            for k in range(L[i][0],L[i][1]+1):
                for j in range(len(a)):
                    if a[j][k] != '-':
                        freq[a[j][k]] += 1
                        somme += 1
            line = []
            try:
                for k in range(len(self.sigma)):
                    line.append(freq[self.sigma[k]]/somme)
                self.E.append(line)
            except:
                print("Un intervalle de colonnes ne comporte aucun caractère de l'alphabet !")            
        # Récupération des fréquences de transition
        self.T = []
        for i in range(len(self.S)-1):
            freq = []
            freqcum = []
            # Initialisation des fréquences à 0
            for k in range(len(a[0])):
                freq.append(0)
            for k in range(len(self.S)):
                freqcum.append(0)
            # Calcul des effectifs pour les états suivants
            for j in range(len(a)):
                for q in range(L[i][0],L[i][1]+1):
                    if (a[j][q] != '-'):
                        k = q+1
                        while ((k < len(a[0])) and (a[j][k] == '-')):
                            k += 1
                        if (k<len(a[0])):
                            freq[k] += 1
                        else:
                            freq[q] += 1
            # fusion des frequences dans les intervalles
            for q in range(len(self.S)):
                for j in range(L[q][0],L[q][1]+1):
                    freqcum[q] += freq[j]
            line = []      
            try: 
                for k in range(len(self.S)):
                    line.append(freqcum[k]/sum(freqcum))
            except:
                print("Aucune transition trouvée")
            self.T.append(line)
        line = []
        for j in range(len(self.S)-1):
            line.append(0.0)
        line.append(1.0)
        self.T.append(line)


    def __eq__(self,other):
        return ((self.S == other.S) and (self.P == other.P) and (self.E == other.E) and (self.T == other.T))

    def estValide(self):
        ok = True
        if sum(self.P) != 1:
            ok = False
        for i in range(len(self.S)):
            if sum(self.E[i]) != 1:
                ok = False
            if sum(self.T[i]) != 1:
                ok = False
        return ok

    def backward(self,w):
        k = len(w)
        n = len(self.S)
        beta = [[] for _ in range(k)]
        for j in range(n):
            beta[k-1].append(self.E[j][(self.sigma).index(w[k-1],0,len(self.sigma))])
        for i in range(k-2,-1,-1):
            for j in range(n):
                beta[i].append(0)
                for l in range(n):
                    beta[i][j] += self.E[j][(self.sigma).index(w[i],0,len(self.sigma))]*beta[i+1][l]*self.T[j][l]
        for j in range(n):
            beta[0][j] *= self.P[j]
        return beta
        
    def generer_sequence(self, longueur):
        seq = []
        etat = random.choices(self.S, self.P)[0]
        a = random.choices(self.sigma, self.E[etat])
        seq.append(a[0])
        for i in range (1,longueur):
            etat = random.choices(self.S, self.T[etat-1])[0]
            a = random.choices(self.sigma, self.E[etat-1])
            seq.append(a[0])
        return seq

def cma(A,j):
    for i in range(len(A)):
        if A[i][j] == '-':
            return True
    return False

def ima(A):
    L = []
    p = len(A[0])
    deb,fin = 0,0
    while deb < p:
        fin = deb
        while fin < p and cma(A,fin): 
            fin += 1
        if (fin > deb):
            L.append((deb,fin-1))
            deb = fin
        else:
            L.append((deb,deb))
            deb = deb + 1
    return L 
    
def charger_alignement(fichier):
    """
    Charge un alignement multiple depuis un fichier FASTA.
    Ignore les lignes d'identifiants (commençant par '>').
    Retourne une liste de listes de caractères (ex: [['A','T','G','-'], ...])
    """
    alignement = []
    sequence_en_cours = ""

    with open(fichier, "r") as f:
        for ligne in f:
            ligne = ligne.strip()
            if not ligne:
                continue  # ignore les lignes vides
            if ligne.startswith(">"):
                if sequence_en_cours:
                    alignement.append(list(sequence_en_cours.upper()))
                    sequence_en_cours = ""
            else:
                sequence_en_cours += ligne  # concatène les lignes de séquence
        if sequence_en_cours:
            alignement.append(list(sequence_en_cours.upper()))

    return alignement     



"""
h1 = HMM([1,2,3,4], [1,0,0,0], [[1,0,0,0],[0,0,0.5,0.5],[0.5,0,0.5,0],[0.2,0.1,0.4,0.3]], [[0.5,0,0.5,0],[0,0.1,0.8,0.1],[0,0.2,0.5,0.3],[0,0,0,1]])
h2 = HMM([1,2,3,4], [1,0,0,0], [[1,0,0,0],[0,0,0.5,0.6],[0.5,0,0.5,0],[0.2,0.1,0.4,0.3]], [[0.5,0,0.5,0],[0,0.1,0.8,0.1],[0,0.2,0.5,0.3],[0,0,0,1]])

alignement = [['G','A','T','T','C','A'],['G','-','C','T','-','A'], ['G','A','T','T','-','T'], ['G','-','-','T','C','G']]
"""

L=["HMM_100.fasta", "HMM_200.fasta","HMM_500.fasta", "HMM_1000.fasta","HMM_1500.fasta", "HMM_2000.fasta"]
NB = [100,200,500,1000,1500,2000]

for i in range (6):
    with open(L[i], "w") as f :
        for j in range(30):
            nouveau = HMM()
            alignement = charger_alignement("sequencesTP7.aln")
            nouveau.fromAlignement(alignement,ima(alignement))
            f.write(">sequence_HMM_n_"+ str(j)+ "\n")
            f.write(str("".join(nouveau.generer_sequence(NB[i]))))
            f.write("\n")





