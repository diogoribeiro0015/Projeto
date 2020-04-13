#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"

#define MAX_SIZE 200

void Inicio(int argc, char* argv[],int* cidade_index, int *pais_index, int *grafico)
{
    int a=0;
    if(argc!=6)//tem de haver obrigatoriamente 6 argumentos
    {
        printf("Por favor insira 6 argumentos!\n");
        exit(EXIT_FAILURE);
    }

    for(a=0; a<argc; a++)
    {
        if(strcmp(argv[a], "-g")==0)
        {
            *grafico=1;
        }
        if(strcmp(argv[a], "-t")==0)
        {
            *grafico=0;
        }
        if(strcmp(argv[a], "-f1")==0 && a!=argc-1)
        {
            *pais_index=a+1;//guardar a aposição do argumento
            if(strstr(argv[a+1], "countries")==NULL)//para obrigar a que o documento a seguir ao -f1 é o fivheiro de countries
            {
                printf("Não pode ser seguido desse documento!\n");
                exit(EXIT_FAILURE);
            }
        }
        if(strcmp(argv[a], "-f2")==0 && a!=argc-1)
        {
            *cidade_index=a+1;//guardar a aposição do argumento
            if(strstr(argv[a+1], "cities")==NULL)//para obrigar a que o documento a seguir ao -f2 é o fivheiro de cites
            {
                printf("Não pode ser seguido desse documento!\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}
//função para guardar as cidades
tempinfo* guardar(FILE *f) {

    tempinfo* ptr_tempinfo=NULL;
    tempinfo* head_cidade=NULL;
    tempinfo* tail_cidade=NULL;
    tempinfo* aux=NULL;

    char frase[400]={0};
    char city[MAX_SIZE]={0};
    char country[MAX_SIZE]={0};
    float media=0.0;
    float incer=0.0;
    int day=0;
    int month=0;
    int year=0;
    float ang_lati=0.0, ang_longi=0.0;
    char dir_lati=0, dir_longi=0;
    int n=0;

    fgets(frase, sizeof(frase), f);//eliminar a primeira linhas
    while (fgets(frase, sizeof(frase), f) != NULL) {

        frase[strlen(frase)-1]='\0';

        sscanf(frase, "%d-%d-%d,%f,%f,%[^,],%[^,],%f%c,%f%c", &year, &month, &day, &media, &incer, city, country, &ang_lati, &dir_lati, &ang_longi, &dir_longi);
        if (dir_longi!='W') dir_longi='E';

        if (media!=0 && incer!=0) {

            ptr_tempinfo = (tempinfo*)malloc(sizeof(tempinfo));

            ptr_tempinfo->date.ano = year;
            ptr_tempinfo->date.mes = month;
            ptr_tempinfo->date.dia = day;
            ptr_tempinfo->temp_media = media;
            ptr_tempinfo->temp_incer = incer;
            strcpy(ptr_tempinfo->city, city);
            strcpy(ptr_tempinfo->pais, country);
            ptr_tempinfo->latitude.angulo = ang_lati;
            ptr_tempinfo->latitude.direcao = dir_lati;
            ptr_tempinfo->longitude.angulo = ang_longi;
            ptr_tempinfo->longitude.direcao = dir_longi;

            if (n!=0) {
                aux->next = ptr_tempinfo;
                ptr_tempinfo->prev=aux;
            }

            aux = ptr_tempinfo;
            tail_cidade=ptr_tempinfo;
            tail_cidade->next=NULL;

            if (n==0) {
                head_cidade = aux;
                head_cidade->prev=NULL;
            }

            n++;
            media = 0.0;
            incer = 0.0;
        }
    }
    rewind(f);
    return head_cidade;
}
//função que guarda o pais
tempinfo* guardar_pais(FILE *f)
{
    tempinfo* ptr_tempcountries;
    tempinfo* tempcountries_ord;
    tempinfo* ptr_compara;
    tempinfo* aux=NULL;

    char frase[1000]={0};
    char country[MAX_SIZE];
    float media=0.0;
    float incer=0.0;
    int day=0;
    int month=0;
    int year=0, ano=0, mes=0;
    int n=0, i=0;

    fgets(frase, sizeof(frase), f);//eliminar a primeira linha
    while (fgets(frase, sizeof(frase), f) != NULL)
    {
        if(strstr(frase, ",,")==NULL)
        {
            frase[strlen(frase)-1]='\0';
            frase[strlen(frase)-1]='\0';

            if(n==0)
                ptr_tempcountries = (tempinfo*)malloc(sizeof(tempinfo));
            else
                ptr_tempcountries = (tempinfo*)realloc(ptr_tempcountries, (n+1)*sizeof(tempinfo));
            ptr_compara=(tempinfo*)malloc(sizeof(tempinfo));

            sscanf(frase, "%d-%d-%d,%f,%f,%[^\n]", &year, &month, &day, &media, &incer, country);
            ptr_compara->temp_media = media;
            ptr_compara->temp_incer = incer;
            strcpy(ptr_compara->pais, country);
            ptr_compara->date.ano=year;
            ptr_compara->date.mes=month;
            ptr_compara->date.dia=day;
            ptr_tempcountries[n]=*ptr_compara; //guardar num vetor para a seguir ser usado para prdenar numa lista
            n++;
        }
    }

    for(ano=2013; ano>=1730; ano--)
    {
        for(mes=12; mes>=1; mes--)
        {
            for(i=0; i<=n; i++)
            {
                if(ptr_tempcountries[i].date.ano==ano && ptr_tempcountries[i].date.mes==mes)
                {
                    tempcountries_ord = (tempinfo*)malloc(sizeof(tempinfo));
                    *tempcountries_ord=ptr_tempcountries[i];

                    tempcountries_ord->next=aux;
                    if (aux!=NULL) aux->prev=tempcountries_ord;
                    aux=tempcountries_ord;
                }
            }
        }
    }

    rewind(f);
    free(ptr_tempcountries);
    ptr_tempcountries=NULL;
    n=0;
    return tempcountries_ord;
}
//Função axiliar para obter informação do teclado, com um maximo definido
int EscolherOpcao(int _max_opc) {

    char escolha[20]={0};
    int ret=0;

    do {
        fgets(escolha, 20, stdin);
        sscanf(escolha, "%d", &ret);
        if (ret<1 || ret>_max_opc) printf("Não existe essa opção, tente outra vez\n");
    } while (ret<1 || ret>_max_opc);

    printf("\n");

    return ret;
}

int MenuPrincipal() {

    int escolha=0;      //Opção escolhida pelo utilizador

    printf("MENU PRINCIPAL:\n");
    printf(" 1.Filtragem de dados\n 2.Histórico de temperaturas\n 3.Análise da temperatura por ano\n 4.Análise da temperatura global\n 5.Sair!\n");
    escolha = EscolherOpcao(5);

    printf("\n");

    return escolha;
}

int MenuFiltragemDados() {

    int escolha=0;      //opção escolhida pelo utilizador

    printf("MENU FILTRAGEM DE DADOS:\n");
    printf(" 1.Limpa critérios\n 2.Escolhe intervalo para análise\n 3.Escolhe mês para análise\n 4.Voltar para o menu principal\n");
    escolha = EscolherOpcao(4);

    return escolha;
}

int MenuHistTemp() {

    int escolha=0;      //Opção escolhida pelo utilizador

    printf("MENU HISTÓRICO DE TEMPERATURAS:\n");
    printf(" 1.Global\n 2.Por país\n 3.Por cidade\n 4.Redefinir periodo de amostragem\n 5.Voltar para o menu principal\n");
    escolha = EscolherOpcao(5);

    printf("\n");

    return escolha;
}

int MenuAnaliseTempAno() {

    int escolha=0;      //Opção escolhida pelo utilizador

    printf("MENU ANÁLISE DA TEMPERATURA POR ANO:\n");
    printf(" 1.Análise por país\n 2.Análise por cidade\n 3.Redefenir o número de elementos mostrados e ano a ser analisado\n 4.Voltar para o menu principal\n");
    escolha = EscolherOpcao(4);

    printf("\n");

    return escolha;
}

int MenuAnaliseTempGlobal() {

    int escolha=0;      //Opção escolhida pelo utilizador

    printf("MENU ANÁLISE DA TEMPERATURA GLOBAL:\n");
    printf(" 1.Aumento da temperatura global do planeta\n 2.Aumento da temperatura num país\n 3.Aumento da temperatura numa cidade\n 4.Redefinir M\n 5.Voltar para o menu principal\n");
    escolha = EscolherOpcao(5);

    printf("\n");

    return escolha;
}

int MenuAnaliseTempGloblalCidade()
{

    int escolha=0;      //Opção escolhida pelo utilizador

    printf("MENU ANALISE DA TEMPERATURA PO CIDADE:\n");
    printf(" 1.Imprimir aumento de temperatura\n 2.Redefinir cidade\n 3.Voltar\n");
    escolha = EscolherOpcao(3);

    printf("\n");

    return escolha;
}

//Função axiliar para obter informação do teclado, com um maximo definido
int MenuAnaliseTempGloblalPais(char _nome_pais[]) {

    int escolha=0;      //Opção escolhida pelo utilizador

    printf("MENU ANALISE DA TEMPERATURA POR PAIS:\n");
    printf(" 1.Imprimir aumento de temperatura no seguinte pais:%s\n 2.Redefinir pais\n 3.Voltar\n", _nome_pais);
    escolha = EscolherOpcao(3);

    printf("\n");

    return escolha;
}

//Função 1.1: Retira todos os filtros impostos anteriormente
void LimpaCriterios(data* _intervalo, int* _mes_i, int* _mes_f, int* _filtros1, int* _filtros2) {

    _intervalo->ano=0;
    _intervalo->mes=0;
    *_mes_i=0;
    *_mes_f=0;

    *_filtros1=0;
    *_filtros2=0;

    printf("Pesquisa sem filtros!\n\n");
}
//Função 1.2: Escolhe uma data inicial e vai analisar apenas os dados conseguidos a partir dessa data
int EscolheIntervalo(data* _intervalo) {

    printf("Analisar dados a partir de que data?\n");
    printf("Ano:");
    _intervalo->ano = EscolherOpcao(2018);
    printf("Mes:");
    _intervalo->mes = EscolherOpcao(12);

//    printf("%d %d\n", _intervalo->ano, _intervalo->mes);
    return 1;

}

//Função 1.3: Escolhe um periodo de meses e permite a análise de dados apenas nesse periodo
int EscolheMes(int* _mes_i, int* _mes_f) {

    printf("Analisar dados em que periodo do ano?(Jan=1, Fev=2, etc...)\n");
    printf("Mes inicial:");
    *_mes_i = EscolherOpcao(12);
    printf("Mes final:");
    *_mes_f = EscolherOpcao(12);
//    printf("%d %d\n", *_mes_i, *_mes_f);

    return 1;
}
//Função 2.4: vai definir/redifinir tempo de amostragem
void DefTempAmost(int* _t_anos) {

    printf("Defina o período de tempo:");
    *_t_anos = EscolherOpcao(500);
}
//Função auxiliar para se introduzir um nome do teclado
void GetName(char _nome[]) {

    char frase[MAX_SIZE]={0};
    fgets(frase, sizeof(frase), stdin);
    frase[strlen(frase)-1]='\n';
    sscanf(frase, "%[^\n]", _nome);

}
//Verificar se existe uma determinada cidade introduzida pelo utilizador
void CompareNameCity(tempinfo* _head, char _nome[]) {

    int val=1;
    tempinfo* aux=NULL;

    do {
        GetName(_nome);
        aux = _head;
        while (aux!=NULL && val!=0){
            val=strcmp(_nome, aux->city);
            aux=aux->next;
        }
        if (val!=0)printf("Esse nome não existe na nossa lista de dados\nTente de novo:");
    } while (val!=0);
}

//Verificar se existe um determinado pais introduzido pelo utilizador
void CompareNameCountry (tempinfo* _head, char _nome[]) {

    int val=1;
    tempinfo* aux=NULL;

    do {
        GetName(_nome);
        aux = _head;
        while (aux!=NULL){
            if (strstr(aux->pais, _nome) != NULL) val=0;
            aux=aux->next;
        }
        if (val!=0)printf("Esse pais não existe na nossa lista de dados\nTente de novo:");
    } while (val!=0);
}

//Função que vai filtrar a lista dos paises
void FiltraListasPais (tempinfo** _head_pais, data _intervalo, int _mes_i, int _mes_f, int _filtros1, int _filtros2) {

    tempinfo* aux=NULL;
    tempinfo* aux_next=NULL;
    tempinfo* aux_prev=NULL;

    aux=*_head_pais;
    if (_filtros1!=0) {
        while (aux!=NULL) {
            if (aux->date.ano<_intervalo.ano || (aux->date.ano==_intervalo.ano && aux->date.mes<_intervalo.mes)) {
                if (aux->prev==NULL) {
                    aux_next=aux->next;
                    aux_next->prev=NULL;
                    free(aux);
                    *_head_pais=aux_next;
                }
                else if (aux->prev!=NULL && aux->next!=NULL) {
                    aux_prev=aux->prev;
                    aux_next=aux->next;
                    aux_prev->next=aux_next;
                    aux_next->prev=aux_prev;
                    free(aux);
                }
                else if (aux->next==NULL) {
                    aux_prev=aux->prev;
                    aux_next=aux->next;
                    aux_prev->next=NULL;
                    free(aux);
                }
            }
            else {
                aux_next=aux->next;
            }
            aux=aux_next;
        }
    }

    aux=*_head_pais;
    if (_filtros2!=0) {
        while (aux!=NULL) {
            if ((_mes_i<=_mes_f && (aux->date.mes<_mes_i || aux->date.mes>_mes_f)) || (_mes_i>_mes_f && (aux->date.mes<_mes_i && aux->date.mes>_mes_f))) {
                if (aux->prev==NULL) {
                    aux_next=aux->next;
                    aux_next->prev=NULL;
                    free(aux);
                    *_head_pais=aux_next;
                }
                else if (aux->prev!=NULL && aux->next!=NULL) {
                    aux_prev=aux->prev;
                    aux_next=aux->next;
                    aux_prev->next=aux_next;
                    aux_next->prev=aux_prev;
                    free(aux);
                }
                else if (aux->next==NULL) {
                    aux_prev=aux->prev;
                    aux_next=aux->next;
                    aux_prev->next=NULL;
                    free(aux);
                }
            }
            else {
                aux_next=aux->next;
            }
            aux=aux_next;
        }
    }
}
//Função que vai filtrar a lista da cidade
void FiltraListasCidade (tempinfo** _head_cidade, data _intervalo, int _mes_i, int _mes_f, int _filtros1, int _filtros2) {

    tempinfo* aux=NULL;
    tempinfo* aux_next=NULL;
    tempinfo* aux_prev=NULL;

    aux=*_head_cidade;
    if (_filtros1!=0) {
        while (aux!=NULL) {
            if (aux->date.ano<_intervalo.ano || (aux->date.ano==_intervalo.ano && aux->date.mes<_intervalo.mes)) {
                if (aux->prev==NULL) {
                    aux_next=aux->next;
                    aux_next->prev=NULL;
                    free(aux);
                    *_head_cidade=aux_next;
                }
                else if (aux->prev!=NULL && aux->next!=NULL) {
                    aux_prev=aux->prev;
                    aux_next=aux->next;
                    aux_prev->next=aux_next;
                    aux_next->prev=aux_prev;
                    free(aux);
                }
                else if (aux->next==NULL) {
                    aux_prev=aux->prev;
                    aux_next=aux->next;
                    aux_prev->next=NULL;
                    free(aux);
                }
            }
            else {
                aux_next=aux->next;
            }
            aux=aux_next;
        }
    }

    aux=*_head_cidade;
    if (_filtros2!=0) {
        while (aux!=NULL) {
            if ((_mes_i<=_mes_f && (aux->date.mes<_mes_i || aux->date.mes>_mes_f)) || (_mes_i>_mes_f && (aux->date.mes<_mes_i && aux->date.mes>_mes_f))) {
                if (aux->prev==NULL) {
                    aux_next=aux->next;
                    aux_next->prev=NULL;
                    free(aux);
                    *_head_cidade=aux_next;
                }
                else if (aux->prev!=NULL && aux->next!=NULL) {
                    aux_prev=aux->prev;
                    aux_next=aux->next;
                    aux_prev->next=aux_next;
                    aux_next->prev=aux_prev;
                    free(aux);
                }
                else if (aux->next==NULL) {
                    aux_prev=aux->prev;
                    aux_next=aux->next;
                    aux_prev->next=NULL;
                    free(aux);
                }
            }
            else {
                aux_next=aux->next;
            }
            aux=aux_next;
        }
    }
}
//Função para apagar completamente listas da memoria
void EraseLists(tempinfo** _head) {

    tempinfo* aux=NULL;

    aux=*_head;
    while (aux->next!=NULL) {
        aux=aux->next;
        free(aux->prev);
    }
    *_head=NULL;
}
//função2.1
void parte21(tempinfo *pais, int periodo)
{
    int contagem=0;
    tempinfo *aux;
    int a=0, k=0, i=0, c=0, ano_inicial[100]={0}, ano_final[100]={0}, ano=1700;
    float media_final[100]={0.0}, max_valor[100]={0.0}, min_valor[100]={0.0};
    float adicao=0.0, media=0.0, maximo=-100.0, minimo=100.0, valor=0.0;
    char continuar;
    aux=pais;
    for(a=ano; a<=2013; a=a+periodo)
    {
        while(aux!=NULL)
        {
            if(aux->date.ano>=a && aux->date.ano<a+periodo)
            {
                contagem=contagem+1;//incrementar o divisor
                adicao = adicao + aux->temp_media;//somar todas as medias
                valor=aux->temp_media;//para verificar a seguir se é maximo ou minimo ou nenhum dos dois
                if(valor>maximo)//ver se ŕ minimo ou nao e se é maximo ou e ate quando
                {
                    maximo=valor;
                }
                if(valor<minimo)
                {
                    minimo=valor;
                }

            }
        aux=aux->next;
        }
    media=(adicao/contagem);
    media_final[i]=media;
    min_valor[i]=minimo;
    max_valor[i]=maximo;
    ano_inicial[i]=a;//para saber os anos
    ano_final[i]=a+periodo;//para saber os anos
    if(a+periodo>=2013)
        ano_final[i]=2014;
    aux=pais;
    i++;
    contagem=0;
    adicao=0.0;
    media=0.0;
    minimo=100.0;
    maximo=-100.0;
    }
    for(c=0; c<i; c++)
    {
         if(max_valor[c]!=-100.0)
         {
            k++;//para saber onde é a linha 20
            if(k==19)
            {
                printf("Deseja continuar a ver os resultados?\nDigite a tecla 'a' se sim e a tecla 'q' se não\n");
                scanf("%s", &continuar);

                while(continuar !='a' && continuar !='q')
                {
                    printf("Por favor insira 'a' ou 'q'!\n");
                    printf("Deseja continuar a ver os resultados?\nDigite a tecla 'a' se sim e a tecla 'q' se não\n");
                    scanf("%s", &continuar);
                }

                if(continuar=='a')
                    printf("%d-%d:   maximo:%.2f  || minimo: %.2f  || media: %.2f\n",ano_inicial[c], ano_final[c]-1, max_valor[c], min_valor[c], media_final[c]);
                if(continuar=='q') break;
            }
            else
                printf("%d-%d: maximo:%.2f  ||  minimo:%.2f  ||  media:%.2f\n", ano_inicial[c], ano_final[c]-1, max_valor[c], min_valor[c], media_final[c]);

        }
    }
    printf("\nEm alguns intervalos podemos ter anos sem dados!\n");
}
//função2.2
void parte22(tempinfo *pais, int periodo)
{
    int contagem=0;
    tempinfo *aux;
    int a=0, i=0, c=0, f=0, ano=1700, ano_inicial[100]={0}, ano_final[100]={0}, tamanho=0, k=0;
    float media_final[100]={0.0}, max_valor[100]={0.0}, min_valor[100]={0.0};
    float adicao=0.0, media=0.0, maximo=-20.0, minimo=30.0, valor=0.0;
    char continuar, country[100], nome[100];
    printf("Introduza o nome do pais:\n");
    fgets(nome,100,stdin);
    sscanf(nome,"%[^\n]", country);
    tamanho=strlen(country);
    aux=pais;
    for(a=ano; a<=2013; a=a+periodo)
    {
        while(aux!=NULL)
        {
            if(strncmp(country, aux->pais, tamanho)==0)
            {
                k++;//para verificar que existe
                {
                    if(aux->date.ano>=a && aux->date.ano<a+periodo)
                    {
                        contagem=contagem+1;
                        adicao = adicao + aux->temp_media;
                        valor=aux->temp_media;
                        if(valor>maximo)
                        {
                            maximo=valor;
                        }
                        if(valor<minimo)
                        {
                            minimo=valor;
                        }
                    }
                }
            }

        aux=aux->next;
        }

    media=(adicao/contagem);
    media_final[i]=media;
    min_valor[i]=minimo;
    max_valor[i]=maximo;
    ano_inicial[i]=a;
    ano_final[i]=a+periodo;
    if(a+periodo>=2013)
        ano_final[i]=2014;
    aux=pais;
    i++;
    contagem=0;
    adicao=0.0;
    media=0.0;
    minimo=30.0;
    maximo=-20.0;
    }

    if(k==0)//pois não encontramos na lista
    {
        printf("Não tenho informação desse pais!\n");
    }
    if(k!=0)
    {
        printf("\nEm alguns intervalos podemos ter anos sem dados!\n");
    }
    for(c=0; c<i; c++)
    {
        if(max_valor[c]!=-20.0000000000)// quer dizer que não atualizou, logo não queremos imprimir
        {
            f++;
            if(f==19)
            {
                printf("Deseja continuar a ver os resultados?\nDigite a tecla 'a' se sim e a tecla 'q' se não\n");
                scanf("%s", &continuar);
                while(continuar !='a' && continuar !='q')
                {
                    printf("Por favor insira 'a' ou 'q'!\n");
                    printf("Deseja continuar a ver os resultados?\nDigite a tecla 'a' se sim e a tecla 'q' se não\n");
                    scanf("%s", &continuar);
                }
                if(continuar=='a')
                    printf("%d-%d: maximo:%.2f  ||  minimo:%.2f  ||  media:%.2f\n", ano_inicial[c], ano_final[c]-1, max_valor[c], min_valor[c], media_final[c]);
                if(continuar=='q') break;
            }
            else
                printf("%d-%d: maximo:%.2f  ||  minimo:%.2f  ||  media:%.2f\n", ano_inicial[c], ano_final[c]-1, max_valor[c], min_valor[c], media_final[c]);
        }
    }
}
//função2.3
void parte23(tempinfo *cidade, int periodo)
{
    int contagem=0;
    tempinfo *aux;
    int ano=1700, f=0, a=0, i=0, c=0, k=0, ano_inicial[100]={0}, ano_final[100]={0};
    float media_final[100]={0.0}, max_valor[100]={0.0}, min_valor[100]={0.0};
    float adicao=0.0, media=0.0, maximo=-20.0, minimo=30.0, valor=0.0;
    char continuar;
    char city[100]={0}, nome[100];
    printf("Qual é o nome da cidade:\n");
    fgets(nome,100,stdin);
    sscanf(nome,"%[^\n]", city);
    aux=cidade;
    for(a=ano; a<=2013; a=a+periodo)
    {
        while(aux!=NULL)
        {
            if(strcmp(city, aux->city)==0)
            {
                k++;//para saber se existe
                {
                    if(aux->date.ano>=a && aux->date.ano<a+periodo)
                    {
                        contagem=contagem+1;
                        adicao = adicao + aux->temp_media;
                        valor=aux->temp_media;
                        if(valor>maximo)
                        {
                            maximo=valor;
                        }
                        if(valor<minimo)
                        {
                            minimo=valor;
                        }
                    }
                }
            }

        aux=aux->next;
        }

    media=(adicao/contagem);
    media_final[i]=media;
    min_valor[i]=minimo;
    max_valor[i]=maximo;
    ano_inicial[i]=a;
    ano_final[i]=a+periodo;
    if(a+periodo>=2013)
        ano_final[i]=2014;
    aux=cidade;
    i++;
    contagem=0;
    adicao=0.0;
    media=0.0;
    minimo=30.0;
    maximo=-20.0;
    }
    if(k==0)
    {
        printf("Não temos informação dessa cidade!\n");
    }
    if(k!=0)
    {
        printf("\nEm alguns intervalos podemos ter anos sem dados!\n");
    }
    for(c=0; c<i; c++)
    {
        if(max_valor[c]!=-20.00000)
         {
            f++;
            if(f==19)
            {
                printf("Deseja continuar a ver os resultados?\nDigite a tecla 'a' se sim e a tecla 'q' se não\n");
                scanf("%s", &continuar);

                while(continuar !='a' && continuar !='q')
                {
                    printf("Por favor insira 'a' ou 'q'!\n");
                    printf("Deseja continuar a ver os resultados?\nDigite a tecla 'a' se sim e a tecla 'q' se não\n");
                    scanf("%s", &continuar);
                }
                if(continuar=='a')
                {
                    printf("%d-%d: maximo:%.2f  ||  minimo:%.2f  ||  media:%.2f\n", ano_inicial[c], ano_final[c]-1, max_valor[c], min_valor[c], media_final[c]);
                }
                if(continuar=='q') break;

            }
            else
                printf("%d-%d: maximo:%.2f  ||  minimo:%.2f  ||  media:%.2f\n", ano_inicial[c], ano_final[c]-1, max_valor[c], min_valor[c], media_final[c]);
        }
    }
}
//função3.1
void parte31(tempinfo *pais, int ano, int n)
{
    analise* paises;
    analise* aux_analise;
    int contagem=0;
    tempinfo *aux;
    int i=0, e=0, a=0, c=0, p=0, k=0;
    float media_final=0.0, valor=0.0;
    float maximo=-20.0, minimo=30.0, media=0.0, diferenca=0.0;
    aux=pais;
    while(aux!=NULL)
    {
        if(aux->date.ano==ano && aux->date.mes==1)
        {
            if(p==0)
                paises=(analise*)malloc(sizeof(analise));
            else
                paises=(analise*)realloc(paises, (p+1)*sizeof(analise));
            strcpy(paises[p].nome,aux->pais);
            p=p+1;//contar o numero de cidades

        }
    aux=aux->next;
    }
    aux=pais;
    for(i=0; i<p; i++)
    {
        while(aux!=NULL)
        {
            if(strcmp(paises[i].nome,aux->pais)==0 && aux->date.ano==ano)
            {
                k++;//saber que existe
                media=media+aux->temp_media;//somar a media
                contagem=contagem+1;//incrementar o divisor
                valor=aux->temp_media;
                if(valor>maximo)
                {
                    maximo=valor;
                }
                if(valor<minimo)
                {
                    minimo=valor;
                }
            }
            aux=aux->next;
        }
        media_final=(media/contagem);
        paises[i].media=media_final;
        diferenca=maximo-minimo;
        paises[i].diferenca=diferenca;
        contagem=0;
        media=0.0;
        maximo=-100.0;
        minimo=100.0;
        aux=pais;
    }
    if(k==0)
    {
        printf("Não temos informação desse ano!\n\n");
        return;
    }
    for(a=0; a<p; a++)
    {
        for(e=0; e<p; e++)
        {
            if(paises[a].media>paises[e].media)
            {
                aux_analise=(analise*)malloc(sizeof(analise));
                *aux_analise=paises[e];
                paises[e]=paises[a];
                paises[a]=*aux_analise;
            }
        }
    }
    printf("Paises mais quentes:\n\n");
    for(c=0; c<n; c++)
    {
        printf("Pais: %s\n", paises[c].nome);
    }
    printf("\nPaises mais frios:\n\n");
    for(c=p-1; c>=p-n; c--)
    {
        printf("Pais: %s\n", paises[c].nome);
    }
    for(a=0; a<p; a++)
    {
        for(e=0; e<p; e++)
        {
            if(paises[a].diferenca>paises[e].diferenca)
            {
                aux_analise=(analise*)malloc(sizeof(analise));
                *aux_analise=paises[e];
                paises[e]=paises[a];
                paises[a]=*aux_analise;
            }
        }
    }
    printf("\nPaises com temperaturas mais extremas:\n\n");
    for(c=0; c<n; c++)
    {
        printf("Pais: %s\n", paises[c].nome);
    }

    free(paises);
    free(aux_analise);

}
//função3.2
void parte32(tempinfo *cidade, int ano, int n)
{
    analise* city;
    analise* aux_analise;
    int contagem=0;
    tempinfo *aux;
    int i=0, e=0, a=0, c=0, p=0, k=0;
    float media_final=0.0, valor=0.0;
    float maximo=-100.0, minimo=100.0, media=0.0, diferenca=0.0;
    aux=cidade;
    while(aux!=NULL)
    {
        if(aux->date.ano==ano && aux->date.mes==1)
        {
            if(p==0)
                city=(analise*)malloc(sizeof(analise));
            else
                city=(analise*)realloc(city, (p+1)*sizeof(analise));
            strcpy(city[p].nome,aux->city);
            p=p+1;//contar o numero de cidades

        }
    aux=aux->next;
    }
    aux=cidade;
    for(i=0; i<p; i++)
    {
        while(aux!=NULL)
        {
            if(strcmp(city[i].nome, aux->city)==0 && aux->date.ano==ano)
            {
                k++;//para saber se existe ou não
                media=media+aux->temp_media;
                contagem=contagem+1;
                valor=aux->temp_media;
                if(valor>maximo)
                {
                    maximo=valor;
                }
                if(valor<minimo)
                {
                    minimo=valor;
                }
            }
            aux=aux->next;
        }
        media_final=(media/contagem);
        city[i].media=media_final;
        diferenca=maximo-minimo;
        city[i].diferenca=diferenca;
        contagem=0;
        media=0.0;
        maximo=-100.0;
        minimo=100.0;
        aux=cidade;
    }
    if(k==0)
    {
        printf("Não temos informação desse ano!\n");
        return;
    }
    for(a=0; a<p; a++)
    {
        for(e=0; e<p; e++)
        {
            if(city[a].media>city[e].media)
            {
                aux_analise=(analise*)malloc(sizeof(analise));
                *aux_analise=city[e];
                city[e]=city[a];
                city[a]=*aux_analise;
            }
        }
    }
    printf("Cidades mais quentes:\n\n");
    for(c=0; c<n; c++)
    {
        printf("Cidade: %s\n",city[c].nome);
    }
    printf("\nCidades mais frios:\n\n");
    for(c=p-1; c>=p-n; c--)
    {
        printf("Cidade: %s\n", city[c].nome);
    }
    for(a=0; a<p; a++)
    {
        for(e=0; e<p; e++)
        {
            if(city[a].diferenca>city[e].diferenca)
            {
                aux_analise=(analise*)malloc(sizeof(analise));
                *aux_analise=city[e];
                city[e]=city[a];
                city[a]=*aux_analise;
            }
        }
    }
    printf("\nCidades com temperaturas mais extremas:\n\n");
    for(c=0; c<n; c++)
    {
        printf("Cidade: %s\n",city[c].nome);
    }
    free(city);
    free(aux_analise);
}

//Função 4.3: Analisar o aumento da temperatura global
void MovingAverageGlobal(tempinfo* _head, int _m_aver, data _intervalo, int _mes_i, int _mes_f) {

    float resfinal[5]={0};
    float resmes[13]={0.0};
    int i=0, j=1, k=0, n=0, nmes=0;
    int anos[5]={1860,1910,1960,1990,2013};
    float media=0.0;
    tempinfo* aux=NULL;
    float maxima=-100.0, minima=100.0;
    float aumento=0.0;

    for (i=0; i<5; i++) {
        for (j=1; j<=12; j++) {
            for (k=0; k<_m_aver; k++) {
                aux=_head;
                while (aux!=NULL) {
                    if (aux->date.ano>=_intervalo.ano && aux->date.mes>=_intervalo.mes && ((_mes_i<=_mes_f && aux->date.mes>=_mes_i && aux->date.mes<=_mes_f) || (_mes_i>=_mes_f && (aux->date.mes>=_mes_i || aux ->date.mes<=_mes_f)))) {
                        if (aux->date.ano==anos[i]-k && aux->date.mes==j) {
                            media=media+aux->temp_media;
                            n++;
                        }
                    }
                    aux=aux->next;
                }
            }
            if (n!=0) resmes[j]=media/n;
            media=0.0;
            n=0;
        }
        for (j=1; j<=12; j++) {
            media=media+resmes[j];
            if (resmes[j]!=0) nmes++;
        }
        if (nmes!=0) resfinal[i]=media/nmes;
        nmes=0;
        media=0.0;
    }

//    for (i=0; i<5; i++) {
//        printf("Media por ano: %f\n", resfinal[i]);
//    }

    for (i=0; i<5; i++) {
        if (resfinal[i]<minima && resfinal[i] != 0.0) minima=resfinal[i];
        if (resfinal[i]>maxima) maxima=resfinal[i];
    }

    aumento = maxima-minima;
    printf("O aumento da temperatura global foi de %fºC\n\n", aumento);

}

//Função 4.2: Analisar as temperaturas de um pais por MA
void MovingAverageCountry(tempinfo* _head, int _m_aver, char _nome_pais[], data _intervalo, int _mes_i, int _mes_f) {

    float resfinal[5]={0};
    float resmes[13]={0.0};
    int i=0, j=1, k=0, n=0, nmes=0;
    int anos[5]={1860,1910,1960,1990,2013};
    float media=0.0;
    tempinfo* aux=NULL;
    float maxima=-100.0, minima=100.0;
    float aumento=0.0;

    for (i=0; i<5; i++) {
        for (j=1; j<=12; j++) {
            for (k=0; k<_m_aver; k++) {
                aux=_head;
                while (aux!=NULL) {
                    if (strstr(aux->pais, _nome_pais)) {
                        if (aux->date.ano>=_intervalo.ano && aux->date.mes>=_intervalo.mes && ((_mes_i<=_mes_f && aux->date.mes>=_mes_i && aux->date.mes<=_mes_f) || (_mes_i>=_mes_f && (aux->date.mes>=_mes_i || aux ->date.mes<=_mes_f)))) {
                            if (aux->date.ano==anos[i]-k && aux->date.mes==j) {
                                media=media+aux->temp_media;
                                n++;
                            }
                        }
                    }
                    aux=aux->next;
                }
            }
            if (n!=0) resmes[j]=media/n;
            media=0.0;
            n=0;
        }
        for (j=1; j<=12; j++) {
            media=media+resmes[j];
            if (resmes[j]!=0) nmes++;
        }
        if (nmes!=0) resfinal[i]=media/nmes;
        nmes=0;
        media=0.0;
    }
    for (i=0; i<5; i++) {
        if (resfinal[i]<minima && resfinal[i] != 0.0) minima=resfinal[i];
        if (resfinal[i]>maxima) maxima=resfinal[i];
    }

    aumento = maxima-minima;
    printf("O aumento da temperatura no seguinte pais:%s, foi de %fºC\n\n", _nome_pais, aumento);

}

//Função 4.3: Analisar as temperaturas de uma cidade por MA
void MovingAverageCity(tempinfo* _head, int _m_aver, char _nome_cidade[], data _intervalo, int _mes_i, int _mes_f) {

    float resfinal[5]={0};
    float resmes[13]={0.0};
    int i=0, j=1, k=0, n=0, nmes=0;
    int anos[5]={1860,1910,1960,1990,2013};
    float media=0.0;
    tempinfo* aux=NULL;
    float maxima=-100.0, minima=100.0;
    float aumento=0.0;

    for (i=0; i<5; i++) {
        for (j=1; j<=12; j++) {
            for (k=0; k<_m_aver; k++) {
                aux=_head;
                while (aux!=NULL) {
                    if (strstr(aux->city, _nome_cidade)) {
                        if (aux->date.ano>=_intervalo.ano && aux->date.mes>=_intervalo.mes && ((_mes_i<=_mes_f && aux->date.mes>=_mes_i && aux->date.mes<=_mes_f) || (_mes_i>=_mes_f && (aux->date.mes>=_mes_i || aux ->date.mes<=_mes_f)))) {
                            if (aux->date.ano==anos[i]-k && aux->date.mes==j) {
                                media=media+aux->temp_media;
                                n++;
                            }
                        }
                    }
                    aux=aux->next;
                }
            }
            if (n!=0) resmes[j]=media/n;
            media=0.0;
            n=0;
        }
        for (j=1; j<=12; j++) {
            media=media+resmes[j];
            if (resmes[j]!=0) nmes++;
        }
        if (nmes!=0) resfinal[i]=media/nmes;
        nmes=0;
        media=0.0;
    }

//    for (i=0; i<5; i++) {
//        printf("Media por ano: %f\n", resfinal[i]);
//    }

    for (i=0; i<5; i++) {
        if (resfinal[i]<minima && resfinal[i] != 0.0) minima=resfinal[i];
        if (resfinal[i]>maxima) maxima=resfinal[i];
    }

    aumento = maxima-minima;
    printf("O aumento da temperatura na seguinte cidade:%s, foi de %fºC\n\n", _nome_cidade, aumento);

}
