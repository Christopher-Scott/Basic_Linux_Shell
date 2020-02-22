# CIS3207 Lab2 Shell - Christopher Scott
objects = dequeue.o enqueue.o init_queue.o print_queue.o\
			parse.o create_argv.o

test-funcs : test-funcs.c c_shell.h
	gcc -o test-funcs test-funcs.c -L. -lshell

libshell.a : $(objects)
	ar rcs libshell.a $(objects)
dequeue.o : dequeue.c c_shell.h
	gcc -c dequeue.c
enqueue.o : enqueue.c c_shell.h
	gcc -c enqueue.c
init_queue.o : init_queue.c c_shell.h
	gcc -c init_queue.c
print_queue.o : print_queue.c c_shell.h
	gcc -c print_queue.c

parse.o : parse.c c_shell.h
	gcc -c parse.c
create_argv.o : create_argv.c c_shell.h
	gcc -c create_argv.c
