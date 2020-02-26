# CIS3207 Lab2 Shell - Christopher Scott
objects = dequeue.o enqueue.o init_queue.o print_queue.o\
			parse.o create_argv.o

all: myshell test-funcs libc_shell.a

myshell: main.c c_shell.h libc_shell.a
	gcc -g -o myshell main.c -L. -lc_shell

test-funcs: test-funcs.c c_shell.h libc_shell.a
	gcc -g -o test-funcs test-funcs.c -L./ -lc_shell

libc_shell.a: $(objects)
	ar rcs libc_shell.a $(objects)

dequeue.o: dequeue.c c_shell.h
	gcc -g -c dequeue.c
enqueue.o: enqueue.c c_shell.h
	gcc -g -c enqueue.c
init_queue.o: init_queue.c c_shell.h
	gcc -g -c init_queue.c
print_queue.o: print_queue.c c_shell.h
	gcc -g -c print_queue.c

parse.o: parse.c c_shell.h
	gcc -g -c parse.c
create_argv.o: create_argv.c c_shell.h
	gcc -g -c create_argv.c
