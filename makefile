CC = gcc

SDIR = src
IDIR = include
ODIR = obj

_OBJ1 = basis.o logic.o interface.o main.o
_OBJ2 = basis.o logic.o interface.o cUnit_main.o
OBJ1 = $(patsubst %,$(ODIR)/%,$(_OBJ1))
OBJ2 = $(patsubst %,$(ODIR)/%,$(_OBJ2))

CFLAGS = -I$(IDIR) -Wall -Wextra -g
LIBS = -lncurses -lm -pthread -lcunit

SPLINT = splint
SPLINTFLAGS = -weak +infloops +sysdirerrors -compdef \
              -warnposix -type -fixedformalarray -annotationerror \

SPLINT_SOURCE = src/basis.c src/logic.c src/interface.c src/main.c

main: game
cunit: test

$(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ1)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

test: $(OBJ2)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

splinttest:
	$(SPLINT) $(SPLINTFLAGS) -I $(IDIR) $(SPLINT_SOURCE)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o core test
	rm -f $(ODIR)/*.o core game
