VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS = -ggdb -O0 -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g -I src
CC = gcc

all: clean valgrind-alumno

valgrind-chanutron: pruebas_chanutron
	valgrind $(VALGRIND_FLAGS) ./pruebas_chanutron

pruebas_chanutron: src/*.c pruebas_chanutron.o
	$(CC) $(CFLAGS) src/*.c pruebas_chanutron.o -o pruebas_chanutron


valgrind-alumno: pruebas_alumno
	valgrind $(VALGRIND_FLAGS) ./pruebas_alumno

pruebas_alumno: src/*.c pruebas_alumno.c
	$(CC) $(CFLAGS) src/*.c pruebas_alumno.c -o pruebas_alumno

valgrind-ejemplo: ejemplo
	valgrind $(VALGRIND_FLAGS) ./ejemplo

ejemplo: src/*.c ejemplo.c
	$(CC) $(CFLAGS) src/*.c ejemplo.c -o ejemplo

valgrind-interactivo: interactivo
	valgrind $(VALGRIND_FLAGS) ./interactivo

interactivo: *.c *.h
	$(CC) $(CFLAGS) abb.c mostrar_abb.c interactivo.c -o interactivo 2>&1

clean:
	rm -f pruebas_alumno pruebas_chanutron ejemplo

# VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
# CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
# CC = gcc

# all: clean valgrind-alumno

# valgrind-chanutron: pruebas_chanutron
# 	valgrind $(VALGRIND_FLAGS) ./pruebas_chanutron

# pruebas_chanutron: src/*.c pruebas_chanutron.o
# 	$(CC) $(CFLAGS) src/*.c pruebas_chanutron.o -o pruebas_chanutron


# valgrind-alumno: pruebas_alumno
# 	valgrind $(VALGRIND_FLAGS) ./pruebas_alumno

# pruebas_alumno: src/*.c pruebas_alumno.c
# 	$(CC) $(CFLAGS) src/*.c pruebas_alumno.c -o pruebas_alumno

# valgrind-ejemplo: ejemplo
# 	valgrind $(VALGRIND_FLAGS) ./ejemplo

# ejemplo: src/*.c ejemplo.c
# 	$(CC) $(CFLAGS) src/*.c ejemplo.c -o ejemplo

# clean:
# 	rm -f pruebas_alumno pruebas_chanutron ejemplo