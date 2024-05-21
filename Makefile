CC=gcc
CFLAGS = -Wall -Wextra -Wconversion -pedantic-errors -g -fsanitize=undefined,address -fno-omit-frame-pointer -fstack-protector-all -D_FORTIFY_SOURCE=2 -Wl,-z,relro,-z,now -Wl,-z,noexecstack -fPIE -pie -Wformat -Wformat-security -Werror=format-security
DEPS = cli.h
OBJ = crypto.o test.o helper.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

crypto: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o crypto
