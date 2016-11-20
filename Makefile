CC = gcc
CFLAGS = -Wall -std=c99
LIBCHECK = `pkg-config --cflags --libs check`

OBJ_DIR = obj
BIN_DIR = bin

check: rpn-convert-test
	./bin/rpn-convert-test

build: rpn-convert.o

rpn-convert-test: rpn-convert-test.o rpn-convert.o rpn-string.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ $(LIBCHECK) -o $(BIN_DIR)/$@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

.PHONY: clean
clean:
	rm -rf *.o *.h.gch bin
