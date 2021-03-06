/******************************************************************************
 * File Name: utils.h
 * NAME
 *     bignum.h - implementation library for handling some utility functions
 * SYNOPSIS
 *     #include <stdio.h>
 *     #include <stdlib.h>
*****************************************************************************/
#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>

void VerifyCommandLine(int argc, char* argv[]);

FILE *OpenFile(char *argv[]);

Mapa *ReadFile(FILE *fp);

Coords* RandomPlay(Mapa*,int, int, Coords*, int*);

#endif
