GENERATES = README liboutput.so liboutput_static.a
TRASH = *.o *~ o.* file_*
PROGS = prog prog-a prog-so
NUMBERS = 0 1 2

CC = cc
AR = ar
LDFLAGS = -L.

%.o:    %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -fPIC -c $< -o $@

all:    README prog prog-a prog-so

prog:   const.o fun.o prog.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

prog-a: prog.o liboutput_static.a
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

prog-so: prog.o liboutput.so
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

prog.o fun.o: outlib.h

liboutput_static.a: fun.o const.o
	$(AR) rcs $@ $^

liboutput.so: fun.o const.o
	$(CC) $(LDFLAGS) -shared $^ -o $@ $(LDLIBS)

README: prog
	./$< 2> $@

test: all
	set -eu; \
	for program in $(PROGS); do \
		LD_LIBRARY_PATH=$(CURDIR) ./$$program > file_$${program}_0 2>&1; \
		LD_LIBRARY_PATH=$(CURDIR) ./$$program 1 > file_$${program}_1 2>&1; \
		LD_LIBRARY_PATH=$(CURDIR) ./$$program 1 2 3 > file_$${program}_2 2>&1; \
	done; \
	for num in $(NUMBERS); do \
		cmp file_prog_$$num file_prog-a_$$num; \
		cmp file_prog_$$num file_prog-so_$$num; \
		cmp file_prog-a_$$num file_prog-so_$$num; \
	done

clean:
	rm -f $(TRASH) $(GENERATES) $(PROGS)
