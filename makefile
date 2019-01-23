CC = cc

SRCDIR = ./src
INCDIR = ./inc
BINDIR = ./bin

CFLAGS = -g -Wall

RM = /bin/rm -f

OBJ = $(BINDIR)/dubleLinkedList.o
SOURCES = $(SRCDIR)/dubleLinkedList.c

all: clean $(OBJ)

$(OBJ): $(SOURCES)
	$(CC) -c -o$(OBJ) -I$(INCDIR) $(SOURCES) $(CFLAGS)

clean:
	$(RM) $(BINDIR)/*
