SRCDIR=src
BINDIR=bin

CFLAGS=-O2 -Isrc/
LDFLAGS=-lSDL

MODULES=$(BINDIR)/main.o $(BINDIR)/shared_vars.o $(BINDIR)/events_manager.o $(BINDIR)/gol.o

all: gol2d

clean:
	rm $(BINDIR)/*.o
	rm $(BINDIR)/gol2d

$(BINDIR)/main.o:	$(SRCDIR)/main.c
	gcc -c $(CFLAGS) $(SRCDIR)/main.c -o $(BINDIR)/main.o

$(BINDIR)/shared_vars.o:	$(SRCDIR)/common/shared_vars.c
	gcc -c	$(CFLAGS) $(SRCDIR)/common/shared_vars.c -o $(BINDIR)/shared_vars.o

$(BINDIR)/events_manager.o:	$(SRCDIR)/events/events_manager.c
	gcc -c $(CFLAGS) $(SRCDIR)/events/events_manager.c -o $(BINDIR)/events_manager.o

$(BINDIR)/gol.o:	$(SRCDIR)/gol/gol.c
	gcc -c $(CFLAGS) $(SRCDIR)/gol/gol.c -o $(BINDIR)/gol.o

gol2d:	$(MODULES)
	gcc $(CFLAGS) $(MODULES) $(LDFLAGS) -o $(BINDIR)/gol2d

