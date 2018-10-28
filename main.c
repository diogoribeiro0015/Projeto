/******************************************************************************
* File Name: main.c
* Authors: Diogo Ribeiro nº
*          Ricardo Caetano nº
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
int main(int argc, char* argv[]) {

  FILE *fp;
  Mapa *Head;

  VerifyCommandLine(argc, argv);
  fp = OpenFile(argv);
  Head = ReadFile(fp);


  return(0);
}
