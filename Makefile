
CC=gcc
CFLAGS=-g -Wall
OBJS=cli_interaction.o client.o host.o main.o
BIN=$(BINDIR)/cchat
BINDIR=bin
SRC=src/impl
OBJ=obj
RM=rm
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

all: $(BIN)

release: CFLAGS=-Wall -02 -DNDBUG
release: clean
release: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -lncurses


$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 


clean:
	$(RM) -fr $(OBJ)/* $(BINDIR)/*