SRCDIR=src
BINDIR=bin

CFLAGS=-O2 -Isrc/
LDFLAGS=-lSDL -lSDL_image

MODULES=$(BINDIR)/main.o $(BINDIR)/shared_vars.o $(BINDIR)/events_manager.o $(BINDIR)/gol.o \
		$(BINDIR)/drawing_base.o $(BINDIR)/drawing_gui.o $(BINDIR)/drawing_gol.o 

PROGNAME=yagol

all: $(PROGNAME)

clean:
	rm $(BINDIR)/*.o
	rm $(BINDIR)/$(PROGNAME)

$(BINDIR)/main.o:	$(SRCDIR)/main.c
	gcc -c $(CFLAGS) $(SRCDIR)/main.c -o $(BINDIR)/main.o

$(BINDIR)/shared_vars.o:	$(SRCDIR)/common/shared_vars.c
	gcc -c	$(CFLAGS) $(SRCDIR)/common/shared_vars.c -o $(BINDIR)/shared_vars.o

$(BINDIR)/events_manager.o:	$(SRCDIR)/events/events_manager.c
	gcc -c $(CFLAGS) $(SRCDIR)/events/events_manager.c -o $(BINDIR)/events_manager.o

$(BINDIR)/drawing_base.o:	$(SRCDIR)/drawing/drawing_base.c
	gcc -c $(CFLAGS) $(SRCDIR)/drawing/drawing_base.c -o $(BINDIR)/drawing_base.o

$(BINDIR)/drawing_gui.o:	$(SRCDIR)/drawing/drawing_gui.c
	gcc -c $(CFLAGS) $(SRCDIR)/drawing/drawing_gui.c -o $(BINDIR)/drawing_gui.o

$(BINDIR)/drawing_gol.o:	$(SRCDIR)/drawing/drawing_gol.c
	gcc -c $(CFLAGS) $(SRCDIR)/drawing/drawing_gol.c -o $(BINDIR)/drawing_gol.o

$(BINDIR)/gol.o:	$(SRCDIR)/gol/gol.c
	gcc -c $(CFLAGS) $(SRCDIR)/gol/gol.c -o $(BINDIR)/gol.o

$(PROGNAME):	$(MODULES)
	gcc $(CFLAGS) $(MODULES) $(LDFLAGS) -o $(BINDIR)/$(PROGNAME)

