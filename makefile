CC = clang

SDIR = src
IDIR = include
ODIR = obj

_OBJ = interface.o create_map.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

CFLAGS = -I$(IDIR) -Wall -Wextra -g
LIBS = -lncurses -lm

all: test

$(ODIR)/%.o: $(SDIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o core test
