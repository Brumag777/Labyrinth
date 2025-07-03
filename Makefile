CC = gcc
BASE_FLAGS = -Wall -Wextra -pedantic -O1 -g
SANITIZE_FLAGS = -fsanitize=address -fno-omit-frame-pointer
COVERAGE_FLAGS = --coverage
CFLAGS = $(BASE_FLAGS) $(SANITIZE_FLAGS) $(COVERAGE_FLAGS)
LDFLAGS = -lcunit

SRC = Menus.c MemoryManagement.c \
	  Logica/Auxiliares.c Logica/LogicaNivel.c Logica/AI.c \
	  Interface/Imprime.c Interface/Logo.c \
	  LerFicheiros/Niveis.c LerFicheiros/NiveisConcluidos.c
OBJ = $(SRC:.c=.o)
MAIN_OBJ = Main.o $(OBJ)

all: Labyrinth

Labyrinth: $(MAIN_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f Jogo Testes *.o *.gcov *.gcda *.gcno \
					  Auxiliares/*.o Auxiliares/*.gcov Auxiliares/*.gcda Auxiliares/*.gcno \
					  Interface/*.o Interface/*.gcov Interface/*.gcda Interface/*.gcno \
					  LerFicheiros/*.o LerFicheiros/*.gcov LerFicheiros/*.gcda LerFicheiros/*.gcno \
					  Logica/*.o Logica/*.gcov Logica/*.gcda Logica/*.gcno