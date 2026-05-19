# Nom de l'exécutable
EXEC = metro

# Compilateur
CC = gcc

# Fichiers source
SRC = main.c \
      station.c \
      hash.c \
      edge.c \
      tri.c \
      dijkstra.c \
      menu.c

# Fichiers objets
OBJ = $(SRC:.c=.o)

# Règle par défaut
all: $(EXEC)

# Édition de liens
$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ)

# Compilation des fichiers source
%.o: %.c
	$(CC) -c $<

# Nettoyage
clean:
	rm -f $(OBJ) $(EXEC)

mrproper: clean

.PHONY: all clean mrproper
