#ifndef _FUNCOES_H
#define _FUNCOES_

#define MAX(a,b)    (((a)>(b))?(a):(b))
#define M_PI 3.14159265
#define STRING_SIZE 100       // max size for some strings
#define TABLE_SIZE 2000        // main game space size
#define LEFT_BAR_SIZE 150     // left white bar size
#define WINDOW_POSX 150       // initial position of the window: x
#define WINDOW_POSY 150       // initial position of the window: y
#define SQUARE_SEPARATOR 8    // square separator in px
#define BOARD_SIZE_PER 0.7f   // board size in % wrt to table size
#define MAX_BOARD_POS 15      // maximum size of the board
#define MAX_COLORS 5
#define MARGIN 5

void Inicio(int, char*[],int*, int*, int*);
tempinfo* guardar(FILE *);
tempinfo* guardar_pais(FILE *);
int EscolherOpcao(int);
int MenuPrincipal();
int MenuFiltragemDados();
int MenuHistTemp();
int MenuAnaliseTempAno();
int MenuAnaliseTempGlobal();
int MenuAnaliseTempGloblalCidade(char[]);
int MenuAnaliseTempGloblalPais(char[]);
void LimpaCriterios(data*, int*, int*, int*, int*);
int EscolheIntervalo(data*);
int EscolheMes(int*, int*);
void DefTempAmost(int*);
void GetName(char[]);
void CompareNameCity(tempinfo*, char[]);
void CompareNameCountry (tempinfo*, char[]);
void FiltraListasCidade (tempinfo**, data, int, int, int, int);
void FiltraListasPais (tempinfo**, data, int, int, int, int);
void EraseLists(tempinfo**);
void parte21(tempinfo *, int);
void parte22(tempinfo *, int);
void parte23(tempinfo *, int);
void parte31(tempinfo *, int, int);
void parte32(tempinfo *, int, int);
void MovingAverageGlobal(tempinfo*, int, data, int, int);
void MovingAverageCountry(tempinfo*, int, char[], data, int, int);
void MovingAverageCity(tempinfo*, int, char[], data, int, int);
void posicao_cidades(tempinfo *, float[], float[]);
void InitEverything(int , int , TTF_Font **, SDL_Surface **, SDL_Window ** , SDL_Renderer ** );
void InitSDL();
void InitFont();
SDL_Window* CreateWindow(int , int );
SDL_Renderer* CreateRenderer(int , int , SDL_Window *);
int RenderText(int, int, const char *, TTF_Font *, SDL_Color *, SDL_Renderer *);
void RenderTable(int [], TTF_Font *, SDL_Surface **, SDL_Renderer *);
void ProcessMouseEvent(int , int , int [], int , int *, int * );
void RenderPoints(int [][MAX_BOARD_POS], int, int, int [], int, SDL_Renderer *);
void RenderStats( SDL_Renderer *, TTF_Font *, int [], int , int );
void filledCircleRGBA(SDL_Renderer * , int , int , int , int , int , int );
void bolas(SDL_Renderer*, TTF_Font*, float [], float [], tempinfo*, int);
void NomeAlunos (SDL_Renderer *_renderer, TTF_Font *);
#endif

