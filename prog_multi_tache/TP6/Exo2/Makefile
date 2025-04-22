# Nom des exécutables
INIT = semInit
RDV = rendezVous

# Fichiers sources
SRC_INIT = semInit.c
SRC_RDV = rendezVous.c

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -O2

.PHONY: all clean run test

# Compilation complète
all: $(INIT) $(RDV)

# Règle pour semInit
$(INIT): $(SRC_INIT)
	$(CC) $(CFLAGS) -o $(INIT) $(SRC_INIT)

# Règle pour rendezVous
$(RDV): $(SRC_RDV)
	$(CC) $(CFLAGS) -o $(RDV) $(SRC_RDV)

# Nettoyage des fichiers compilés
clean:
	rm -f $(INIT) $(RDV)

# Lancer un test avec 5 processus
test: all
	@echo "Initialisation du sémaphore..."
	./$(INIT) 1 5 pourCle.txt 42
	@echo "Lancement des 5 processus rendezVous..."
	for i in $$(seq 1 5); do \
		./$(RDV) pourCle.txt 42 & \
	done
	wait
	@echo "Test terminé ✅"

# Lance le programme (customisable)
run: $(RDV)
	./$(RDV) pourCle.txt 42
