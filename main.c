/******************************************************************************
* File Name: main.c
* Authors: Diogo Ribeiro nº
*          Ricardo Caetano nº
* Last modified: /11/2108
* COMMENTS
*		Main program
*****************************************************************************/

 #include <stdio.h>
 #include <stdlib>

/******************************************************************************
* main ()
* Arguments: argc - number of command-line arguments
*            argv - table of pointers for string arguments
* Returns: int
* Description: main Program
*****************************************************************************/
int main(int argc, char* argv[]) {

  VerifyCommandLine(argc, argv[]);
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
