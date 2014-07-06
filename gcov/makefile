CC = gcc

IDIR = ../include

OBJ = basis.o logic.o interface.o main.o

CFLAGS = -I$(IDIR) -Wall -Wextra -g -fprofile-arcs -ftest-coverage -p
LIBS = -lncurses -lm -lpanel -pthread

%.o: %.c
	@mkdir -p $(@D)
	@mkdir -p saves
	$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	rm *.o

gcovtest:
	gcov main.c
	gcov basis.c
	gcov logic.c
	gcov interface.c

.PHONY: clean
clean:
	rm -f core game *.gcno *.gcda *.gcov gmon.out
