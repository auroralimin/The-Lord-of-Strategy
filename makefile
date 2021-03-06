CC = clang

SDIR = src
IDIR = include
ODIR = obj

_OBJ1 = basis.o logic.o interface.o main.o
_OBJ2 = basis.o logic.o interface.o cunit_test.o cunit_main.o
OBJ1 = $(patsubst %,$(ODIR)/%,$(_OBJ1))
OBJ2 = $(patsubst %,$(ODIR)/%,$(_OBJ2))

CFLAGS = -I$(IDIR) -Wall -Wextra -g
LIBS = -lncurses -lm -pthread -lpanel -lcunit

$(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p saves
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ1)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test: $(OBJ2)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f $(ODIR)/*.o core game test
