# CIS3207 Lab2 Shell - Christopher Scott
objects = dequeue.o enqueue.o init_queue.o print_queue.o\
			parse.o create_argv.o is_builtin.o run_builtin.o\
			buildpath.o clean_node.o init_cmd.o prompt.o fullpath.o\
			echo.o cd.o clr.o dir.o env.o help.o c_pause.o

all: myshell test-funcs libc_shell.a

myshell: main.c c_shell.h libc_shell.a
	gcc -g -o myshell main.c -L. -lc_shell

test-funcs: test-funcs.c c_shell.h libc_shell.a
	gcc -g -o test-funcs test-funcs.c -L./ -lc_shell

libc_shell.a: $(objects)
	ar rcs libc_shell.a $(objects)

# Data Structures
dequeue.o: dequeue.c c_shell.h
	gcc -g -c dequeue.c
enqueue.o: enqueue.c c_shell.h
	gcc -g -c enqueue.c
init_queue.o: init_queue.c c_shell.h
	gcc -g -c init_queue.c
print_queue.o: print_queue.c c_shell.h
	gcc -g -c print_queue.c

# Shell functions
parse.o: parse.c c_shell.h
	gcc -g -c parse.c
create_argv.o: create_argv.c c_shell.h
	gcc -g -c create_argv.c
is_builtin.o: is_builtin.c	c_shell.h
	gcc -g -c is_builtin.c
run_builtin.o: run_builtin.c c_shell.h
	gcc -g -c run_builtin.c
buildpath.o: buildpath.c c_shell.h
	gcc -g -c buildpath.c
clean_node.o: clean_node.c c_shell.h
	gcc -g -c clean_node.c
init_cmd.o: init_cmd.c	c_shell.h
	gcc -g -c init_cmd.c
promt.o: prompt.c c_shell.h
	gcc -g -c prompt.c
fullpath.o: fullpath.c c_shell.h
	gcc -g -c fullpath.c

# Built ins
echo.o: echo.c c_shell.h
	gcc -g -c echo.c
cd.o: cd.c c_shell.h
	gcc -g -c cd.c
clr.o: clr.c c_shell.h
	gcc -g -c clr.c
dir.o: dir.c c_shell.h
	gcc -g -c dir.c
env.o: env.c c_shell.h
	gcc -g -c env.c
help.o: help.c c_shell.h
	gcc -g -c help.c
c_pause.o: c_pause.c c_shell.h
	gcc -g -c c_pause.c
