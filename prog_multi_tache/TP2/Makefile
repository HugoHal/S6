########################################
#~ définitions
########################################

# Executables à générer
BIN=bin/client  bin/serveur bin/client2chen bin/serveur2

# liste des fichiers sources 
SRCS0=client.c
SRCS1=serveur.c
SRCS2=client2chen.c
SRCS3=serveur2.c

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.c
	gcc -Wall -Iinclude -c $< -o $@

bin/client: $(SRCS0:%.c=obj/%.o)
	gcc -o $@ $+

bin/serveur: $(SRCS1:%.c=obj/%.o)
	gcc -o $@ $+

bin/client2chen : $(SRCS2:%.c=obj/%.o)
	gcc -o $@ $+

bin/serveur2: $(SRCS3:%.c=obj/%.o)
	gcc -o $@ $+

clean:
	rm -f $(BIN) obj/*.o *~
