CC = cc

SRCDIR = ./src
INCDIR = ./inc
BINDIR = ./bin

CFLAGS = -g -Wall -std=c11 -D_XOPEN_SOURCE=700 -D_POSIX_C_SOURCE=200809L -D_POSIX_SOURCE=1 -D_DEFAULT_SOURCE=1 -D_GNU_SOURCE=1

RM = /bin/rm -f

OBJ = $(BINDIR)/dubleLinkedList.o
SOURCES = $(SRCDIR)/dubleLinkedList.c

all: clean $(OBJ)

$(OBJ): $(SOURCES)
	$(CC) -c -o$(OBJ) -I$(INCDIR) $(SOURCES) $(CFLAGS)

clean:
	$(RM) $(BINDIR)/*
