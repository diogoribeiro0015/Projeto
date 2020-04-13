#ifndef _ESTRUTURAS_H
#define _ESTRUTURAS_
//estrutura para a data
typedef struct data{
    int dia;
    int mes;
    int ano;
}data;
//estrutura para guardar as coordenadas
typedef struct geo_coord{
    float angulo;
    char direcao;
}geo_coord;
//estrutura para guardar do doc tempcities.csv
typedef struct tempinfo{
    float temp_media;
    float temp_incer;
    char pais[400];
    char city[400];
    data date;
    geo_coord latitude;
    geo_coord longitude;
    struct tempinfo *next;
    struct tempinfo *prev;
} tempinfo;

typedef struct analise{
    float media;
    float diferenca;
    char nome[400];
}analise;
//estrutura para guardar do doc tempcountries.csv
#endif // _ESTRUTURAS_H_
