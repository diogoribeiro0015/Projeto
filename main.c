#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "funcoes.h"

#define MAX_SIZE 400

int main(int argc, char* argv[]) {
    data intervalo={0,0,0};     //Variavel que vai ser utilizada na filtragem de dados para escolher um intervalo de tempo
    int mes_i=1;        //Variavel que vai ser utilizada na filtragem de dados para escolher um mes inicail
    int mes_f=12;        //Variavel que vai ser utilizada na filtragem de dados para escolher um mes final
    int filtros1=0;     //Se igual a 1, existem filtros aplicados em relação à data inicial de análise das temperaturas
    int filtros2=0;     //Se igual a 1, existem filtros aplicados em relação a um periodo de meses
    int sair=0;         //Variavel usada para retornar ao menu anterior
    int t_anos=0;       //Variavel que define o periodo de tempo, na função histórico de amostragens (T)
    int numn=0;         //Variavel que define o numero de paises ou cidades na função da analise temperatura por ano (N)
    int ano=0;  //Variavel que define o ano a analisar na função analisar por ano
    int board_size_px[2] = {0};
    int m_aver=0;       //Auxiliar na função 4(AnaliseGlobal) (M)
    int grafico=-1;      //saber se o utilizador quer parte grafica ou não
    int pais_index=0; // guardar o nome que vem a seguir ao -f1
    int cidade_index=0; // guardar o nome que vem a seguir ao -f2
    char nome_cidade[MAX_SIZE]={0};       //Guardar o nome da cidade a analisar na função 4
    char nome_pais[MAX_SIZE]={0};        //Guardar o nome do país a analisar na funçao 4
    float pos_x[1001]={0.0};            //tirar as coordenadas para pixeis
    float pos_y[1001]={0.0};            //coordenadas para pixeis
    int ano_bolas=1849;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *serif = NULL;
    SDL_Surface *imgs[2];
    SDL_Event event;
    int quit = 0;
    int width = (TABLE_SIZE + LEFT_BAR_SIZE);
    int height = TABLE_SIZE;
    tempinfo* cidade = NULL;  //Ponteiros auxiliar na construção da lista das cidades
    tempinfo* pais = NULL;        //Ponteiros auxiliares na construção da lista dos paises
    Inicio(argc, argv, &cidade_index, &pais_index, &grafico);
    FILE* f1 = fopen( argv[pais_index], "r");
    if(f1==NULL) {

        printf("Can't open file!!\n");

        exit(EXIT_FAILURE);

    }
    pais=guardar_pais(f1);

    FILE* f2 = fopen(argv[cidade_index], "r");
    if(f2==NULL) {

        printf("Can't open file!\n");

        exit(EXIT_FAILURE);
    }
    cidade=guardar(f2);
    if(grafico==0)
    {
        do {
            switch (MenuPrincipal()) {
                do
                {
                    case 1:
                    switch (MenuFiltragemDados())
                    {
                        //IMPLEMENTADO
                        case 1:
                            LimpaCriterios(&intervalo, &mes_i, &mes_f, &filtros1, &filtros2);
                            EraseLists(&cidade);
                            EraseLists(&pais);
                            cidade = guardar(f2);
                            pais = guardar_pais(f1);
                            break;
                        //IMPLEMENTADO
                        case 2:
                            filtros1 = EscolheIntervalo(&intervalo);
                            FiltraListasCidade(&cidade, intervalo, mes_i, mes_f, filtros1, filtros2);
                            FiltraListasPais(&pais, intervalo, mes_i, mes_f, filtros1, filtros2);
                            break;
                        case 3:
                            filtros2 = EscolheMes(&mes_i, &mes_f);
                            FiltraListasCidade(&cidade, intervalo, mes_i, mes_f, filtros1, filtros2);
                            FiltraListasPais(&pais, intervalo, mes_i, mes_f, filtros1, filtros2);
                            break;
                        //IMPLEMENTADO
                        case 4:
                            sair=1;
                            break;
                    }
                } while (sair!=1);
                sair=0;
                break;
            case 2:
                DefTempAmost(&t_anos);
                do
                {
                    switch (MenuHistTemp())
                    {
                        case 1:
                            parte21(pais,t_anos);
                            break;
                        case 2:
                            parte22(pais, t_anos);
                            break;
                        case 3:
                            parte23(cidade, t_anos);
                            break;
                        case 4:
                        DefTempAmost(&t_anos);
                            break;
                        case 5:
                            sair=1;
                            break;
                    }
                } while (sair!=1);
                sair=0;
                break;
            case 3:
                printf("Qual o ano a analisar:");
                ano = EscolherOpcao(2018);
                printf("Quantos elementos quer visualizar?(N):");
                numn = EscolherOpcao(20);
                do {
                    switch (MenuAnaliseTempAno()) {
                        case 1:
                            parte31(pais, ano, numn);
                            break;
                        case 2:
                            parte32(cidade, ano, numn);
                            break;
                        case 3:
                            printf("Redefinir o ano a analisar:");
                            ano=EscolherOpcao(2018);
                            printf("Redefinir o numero de elementos a visualizar\n");
                            numn = EscolherOpcao(20);
                            break;
                        case 4:
                            sair=1;
                            break;
                        }
                } while (sair!=1);
                sair=0;
                break;
            case 4:
                printf("Definir M:");
                m_aver = EscolherOpcao(12);
                do {
                    switch (MenuAnaliseTempGlobal()) {
                        case 1:
                            MovingAverageGlobal(pais, m_aver, intervalo, mes_i, mes_f);
                            break;
                        case 2:
                            printf("Qual o país que quer analisar:");
                            CompareNameCountry(pais, nome_pais);
                        do {
                            switch (MenuAnaliseTempGloblalPais(nome_pais)) {
                                case 1:
                                    MovingAverageCountry(pais, m_aver, nome_pais, intervalo, mes_i, mes_f);
                                    break;
                                case 2:
                                    printf("Qual o pais que quer analisar:");
                                    CompareNameCountry(pais, nome_pais);
                                    break;
                                case 3:
                                    sair=1;
                                    break;
                            }
                        } while (sair!=1);
                        sair=0;
                        break;
                        case 3:
                            printf("Qual a cidade que quer analisar:");
                            CompareNameCity(cidade, nome_cidade);
                            do {
                                switch (MenuAnaliseTempGloblalCidade(nome_cidade)) {
                                    case 1:
                                        MovingAverageCity(cidade, m_aver, nome_cidade, intervalo, mes_i, mes_f);
                                        break;
                                    case 2:
                                        printf("Qual a cidade que quer analisar:");
                                        CompareNameCity(cidade, nome_cidade);
                                        break;
                                    case 3:
                                        sair=1;
                                        break;
                                }
                            } while (sair!=1);
                            sair=0;
                            break;
                        case 4:
                            printf("Redefinir M:");
                            m_aver = EscolherOpcao(400);
                            break;
                        case 5:
                            sair=1;
                            break;
                    }

                } while (sair!=1);
                sair=0;
                break;
            case 5:
                sair=1;
                break;
            }
        } while (sair!=1);
    }

    if (grafico == 1)
    {
        posicao_cidades(cidade, pos_x, pos_y);
        // initialize graphics
        InitEverything(width, height, &serif, imgs, &window, &renderer);
        while( quit == 0 )
        {
            // while there's events to handle
            while( SDL_PollEvent( &event ) )
            {
                if( event.type == SDL_QUIT )
                {
                    quit=1;
                }
                else if ( event.type == SDL_KEYDOWN )
                {
                    switch ( event.key.keysym.sym )
                    {
                        case SDLK_q:
                            quit=1;
                            break;
                        default:
                            break;
                    }
                }

//                else if ( event.type == SDL_MOUSEMOTION )
//                {
//                    printf("Moving Mouse: %d %d\n", event.button.x, event.button.y);
//                }
            }
            // render game table
            RenderTable( board_size_px, serif, imgs, renderer);
            // render in the screen all changes above
            bolas(renderer, serif, pos_x, pos_y, cidade, ano_bolas);
            //Render nome dos alunos
            NomeAlunos(renderer, serif);

            SDL_RenderPresent(renderer);
            ano_bolas++;
            if(ano_bolas>2013)
            {
                ano_bolas=1849;
            }
            // add a delay
            SDL_Delay( 300 );



        }

        // free memory allocated for images and textures and closes everything including fonts
        TTF_CloseFont(serif);
        SDL_FreeSurface(imgs[0]);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    EraseLists(&cidade);
    EraseLists(&pais);
    fclose(f1);
    fclose(f2);
    free(pais);
    free(cidade);
    return EXIT_SUCCESS;
}
