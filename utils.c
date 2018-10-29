/******************************************************************************
 * File Name: utils.c
 * NAME
 *     bignum.c - implementation library for handling some utility functions
 * SYNOPSIS
 *     #include "utils.h"
 *     #include "estruturas.h"
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

/******************************************************************************
* ReadFile ()
* Arguments: fp - pointer to file
* Returns: - pointer to the list of maps to solve
* Description: Will read each map of the file and store it in a list of structs
*****************************************************************************/
Mapa *ReadFile(FILE *fp) {
  Mapa *head_maplist=NULL, *aux, *aux_prev=NULL;
  int row=0, colu=0, end=0;
  char linha_inteira[100];
  char *num;

  while (end==0) {
    aux= (Mapa*) malloc (sizeof(Mapa));
    if (head_maplist==NULL) head_maplist=aux;
    aux->nmapa=aux_prev;
    aux->coord=NULL;
    aux->map=NULL;

    /*Primeira linha*/
    fgets(linha_inteira, sizeof(linha_inteira), fp);
    linha_inteira[strlen(linha_inteira)-1]='\0';
    sscanf(linha_inteira, "%d %d %c %d", &(aux->lin), &(aux->col), &(aux->obj), &(aux->ntur));

    /*Linhas das coordenadas*/
    aux->coord = (Coords*) malloc((aux->ntur)*sizeof(Coords));
    for (row=1; row<=aux->ntur; row++) {
      fgets(linha_inteira, sizeof(linha_inteira), fp);
      linha_inteira[strlen(linha_inteira)-1]='\0';
      sscanf(linha_inteira, "%d %d", &(aux->coord[row].xcoord), &(aux->coord[row].ycoord));
      printf("%d %d\n", aux->coord[row].xcoord, aux->coord[row].ycoord);
    }

    /*Matriz*/
    aux->map = (int**) malloc((aux->lin)*sizeof(int*));
    for (row=0; row<aux->lin; row++) {
      fgets(linha_inteira, sizeof(linha_inteira), fp);
      linha_inteira[strlen(linha_inteira)-1]='\0';
      aux->map[row] = (int*) malloc ((aux->col)*sizeof(int));
      num = strtok(linha_inteira, " ");
      for (colu=0; colu<aux->col; colu++) {
        sscanf(num, "%d ", &(aux->map[row][colu]));
        printf("%d\n", aux->map[row][colu]);
        if (colu<(aux->col)-1) num = strtok(NULL, " ");
      }
    }
    aux_prev=aux;
    if (fgets(linha_inteira, sizeof(linha_inteira), fp)==NULL || linha_inteira[0]!='\n') end=1;
  }
  return(head_maplist);
}
/******************************************************************************
* VerifyCommandLine ()
* Arguments: argc - number of command-line arguments
*            argv - table of pointers for string arguments
* Returns: -
* Description: Will verify if the program was called correctly at command-line
*****************************************************************************/
void VerifyCommandLine(int argc, char* argv[]) {

  if (argc!=2 || strstr(argv[1], ".cities")==NULL) exit(1);
}

/******************************************************************************
* OpenFile()
* Arguments: argv - table of pointers for string arguments
* Returns: pointer to file that already exists
* Description: Will opne a file and verify if it was correctly open
*****************************************************************************/
FILE *OpenFile(char *argv[]) {
  FILE *fp;

  fp = fopen(argv[1], "r");
  if (fp == (FILE*) NULL)
    exit(1);

  return(fp);
}

void RandomPlay(int x, int y, int x_hipotese[1000][8], int y_hipotese[1000][8])
{
    int i=0, max_mov=8;

    x_hipotese[x][i]=x_hipotese[x][i]+2;
    y_hipotese[y][i]=y_hipotese[y][i]+1;
    i++;
    x_hipotese[x][i]=x_hipotese[x][i]+2;
    y_hipotese[y][i]=y_hipotese[y][i]-1;
    i++;
    x_hipotese[x][i]=x_hipotese[x][i]-2;
    y_hipotese[y][i]=y_hipotese[y][i]+1;
    i++;
    x_hipotese[x][i]=x_hipotese[x][i]-2;
    y_hipotese[y][i]=y_hipotese[y][i]-1;
    i++;
    x_hipotese[x][i]=x_hipotese[x][i]+1;
    y_hipotese[y][i]=y_hipotese[y][i]+2;
    i++;
    x_hipotese[x][i]=x_hipotese[x][i]+1;
    y_hipotese[y][i]=y_hipotese[y][i]-1;
    i++;
    x_hipotese[x][i]=x_hipotese[x][i]-1;
    y_hipotese[y][i]=y_hipotese[y][i]+2;
    i++;
    x_hipotese[x][i]=x_hipotese[x][i]-1;
    y_hipotese[y][i]=y_hipotese[y][i]-2;
}
