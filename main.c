/******************************************************************************
* File Name: main.c
* Authors: Diogo Ribeiro nº 90051
*          Ricardo Caetano nº 90177
* Last modified: /11/2108
* COMMENTS
*		Main program
*****************************************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "estruturas.h"
 #include "utils.h"

/******************************************************************************
* main ()
* Arguments: argc - number of command-line arguments
*            argv - table of pointers for string arguments
* Returns: int
* Description: main Program
*****************************************************************************/
int main(int argc, char* argv[])
{

  FILE *fp;
  Mapa *Head;
  int x_inicio[1000][8]={{0}}, y_inicio[1000][8]={{0}};
  int x_fim[1000][8]={{0}}, y_fim[1000][8]={{0}};
  int i=0, a=0, x=0, y=0;

  VerifyCommandLine(argc, argv);
  fp = OpenFile(argv);
  Head = ReadFile(fp);

  x=Head->coord->xcoord;
  y=Head->coord->ycoord;

  while (x_inicio!=x_inicio && y_fim!=y_inicio)
  {
    RandomPlay(x,y,x_inicio, y_inicio);
    for(i=0; i<8; i++)
    {
      for(a=0; a<8; a++)
      {
        //if(x_inicio[x][i]==x_fim[x_final][a] && y_hipotese[y_inicial][i]==y_hipotese[y_final][a])
      }
    }

  }
  return(0);
}
