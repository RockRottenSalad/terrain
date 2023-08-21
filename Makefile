
CC = clang
DEBUG_CFLAGS = -m64 -g -Wall -Wpedantic
RELEASE_CFLAGS = -m64 -O3 -Wall -Wpedantic

LD_FLAGS = -lX11 -lglfw3 -lGL -lpthread -lXrandr -lXi -ldl -lm

OBJDIR = obj
INCLUDEDIR = lib
#SRCDIR = src
SRCDIR  = $(wildcard src/**/*.c) $(wildcard src/*.c)
DEBUGDIR = bin/debug
RELEASEDIR = bin/release

all:
	$(CC) -c $(SRCDIR) $(DEBUG_CFLAGS) -I $(INCLUDEDIR)
	mv *.o $(OBJDIR)
	$(CC) $(OBJDIR)/*.o -o $(DEBUGDIR)/main $(LD_FLAGS)
	$(CC) -c $(SRCDIR) $(RELEASE_CFLAGS) -I $(INCLUDEDIR)
	mv *.o $(OBJDIR)
	$(CC) $(OBJDIR)/*.o -o $(RELEASEDIR)/main $(LD_FLAGS)

debug:
	$(CC) -c $(SRCDIR) $(DEBUG_CFLAGS) -I $(INCLUDEDIR)
	mv *.o $(OBJDIR)
	$(CC) $(OBJDIR)/*.o -o $(DEBUGDIR)/main $(LD_FLAGS)
	./$(DEBUGDIR)/main

release:
	$(CC) -c $(SRCDIR) $(RELEASE_CFLAGS) -I $(INCLUDEDIR)
	mv *.o $(OBJDIR)
	$(CC) $(OBJDIR)/*.o -o $(RELEASEDIR)/main $(LD_FLAGS)
	./$(RELEASEDIR)/main

test:
	$(CC) -c $(SRCDIR) $(DEBUG_CFLAGS) -I $(INCLUDEDIR)
	mv *.o $(OBJDIR)
	$(CC) $(OBJDIR)/*.o -o $(DEBUGDIR)/main $(LD_FLAGS)

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(RELEASEDIR)/main
	rm -f $(DEBUGDIR)/main
