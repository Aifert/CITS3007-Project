CC=gcc
CFLAGS = -Wall -Wextra -Wconversion -pedantic-errors -g -fsanitize=undefined,address
DEPS = cli.h
OBJ = crypto.o test.o helper.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

crypto: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o crypto
