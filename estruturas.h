#ifndef _ESTRUTURAS_H
#define _ESTRUTURAS_

typedef struct Coords{
  int xcoord;
  int ycoord;
} Coords;

typedef struct Mapa{
  int lin;
  int col;
  char obj;
  int ntur;
  Coords *coord;
  int **map;
  struct Mapa *nmapa;
} Mapa;

#endif
