CC = gcc
BIN_DIST = bin
MPC_DIST = ./mpc
STD = -std=c99
MKDIR = mkdir -p
CFLAGS = $(STD) -Wall -g
LFLAGS = 
PLATFORM = $(shell uname)

ifeq ($(findstring Linux,$(PLATFORM)),Linux)
	LFLAGS += -ledit -lm
endif

ifeq ($(findstring Darwin,$(PLATFORM)),Darwin)
	LFLAGS += -ledit -lm
endif

ifeq ($(findstring MINGW,$(PLATFORM)),MINGW)
endif

SRC = $(wildcard src/*.c)
MPC_LIB = mpc/mpc.c
EXECUTABLE = $(BIN_DIST)/prompt

.PHONY: all clean
all: $(BIN_DIST)/.dirstamp $(EXECUTABLE)

$(BIN_DIST)/.dirstamp:
	$(MKDIR) $(BIN_DIST)
	touch $@

$(BIN_DIST)/prompt: $(MPC_LIB) $(SRC)
	$(CC) $(CFLAGS) -I$(MPC_DIST) $^ $(LFLAGS) -o $@

clean:
	rm -rf -- $(BIN_DIST)