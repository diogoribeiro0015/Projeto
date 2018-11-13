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
  Coords * pos_x_y;
  int i=0, x=0, y=0, fim=0, fim_y=0, fim_x=0;
  Coords* aux;

  VerifyCommandLine(argc, argv);
  fp = OpenFile(argv);
  Head = ReadFile(fp);

  x=Head->coord[0].xcoord;
  y=Head->coord[0].ycoord;
  fim_y=aux[head->ntur]->y.coord;
  fim_x=aux[head->ntur]->x.coord;

  while (fim!=1)
  {
    pos_x_y=RandomPlay(Head,x,y,pos_x_y,&tamanho);
    for(i=0; i<=tamanho; i++)
    {
      if(pos_x_y[i].xcoord==fim_x && pos_x_y[i].ycoord==fim_y)
        fim=1;
    }
  }
  return(0);
}
