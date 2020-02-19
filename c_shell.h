//
// Created by Chris on 2/17/2020.
//

#ifndef LAB2_C_SHELL_H
#define LAB2_C_SHELL_H
#include <stdlib.h>
#include <stdio.h>
#define IN_REDIR 1
#define OUT_REDIR 2
#define OUT_APPEN 4
#define PIPING 8

int parse(char **, size_t, char *);

#endif //LAB2_C_SHELL_H
