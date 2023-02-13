CC = g++
CFLAGS = -g -O0 -Wall

BIN=chess-ai

all: $(BIN)

run: $(BIN)
	./$^

debug: $(BIN)
	gdb ./$^

$(BIN): main.cpp
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) -rf $(BIN) *.dSYM *.o vgcore.*
