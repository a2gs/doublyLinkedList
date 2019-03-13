CC = cc
AR = ar
RANLIB = ranlib

SRCDIR = ./src
INCDIR = ./inc
BINDIR = ./bin

CFLAGS_OPTIMIZATION = -g
#CFLAGS_OPTIMIZATION = -O3
CFLAGS_VERSION = -std=c11
CFLAGS_WARNINGS = -Wall -Wextra
CFLAGS_DEFINES = -D_XOPEN_SOURCE=700 -D_POSIX_C_SOURCE=200809L -D_POSIX_SOURCE=1 -D_DEFAULT_SOURCE=1 -D_GNU_SOURCE=1
CFLAGS = $(CFLAGS_OPTIMIZATION) $(CFLAGS_VERSION) $(CFLAGS_WARNINGS) $(CFLAGS_DEFINES)

RM = rm -rf

OBJ = $(BINDIR)/liba2gs_doublyLinkedList.o
LIB = $(BINDIR)/liba2gs_doublyLinkedList.a
SOURCES = $(SRCDIR)/liba2gs_doublyLinkedList.c

all: clean libDLlinked

libDLlinked: $(SOURCES)
	$(CC) -c -o$(OBJ) -I$(INCDIR) $(SOURCES) $(CFLAGS) -Wno-unused-variable
	$(AR) rc $(LIB) $(OBJ)
	$(RANLIB) $(LIB)
	-$(RM) $(OBJ)

sample: clean libDLlinked
	$(CC) -o $(BINDIR)/sample $(SRCDIR)/sample.c $(CFLAGS) -I$(INCDIR) -L$(BINDIR) -la2gs_doublyLinkedList -Wno-unused-parameter

clean:
	-$(RM) $(BINDIR)/*
