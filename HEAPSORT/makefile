# Variables
CC = gcc
CFLAGS = -Wall
LIBS = -lm
SRC = monticulo.c
OBJ = monticulo.o
EXEC = monticulo

# Regla para compilar el programa
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LIBS)

# Regla para compilar el archivo monticulos.c a objeto
$(OBJ): monticulo.c monticulo.h
	$(CC) $(CFLAGS) -c monticulo.c

# Limpiar archivos generados
clean:
	rm -f $(OBJ) $(EXEC)

# Ejecutar el programa
run: $(EXEC)
	./$(EXEC)

# Regla por defecto
all: $(EXEC)