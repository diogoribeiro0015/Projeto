#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "estruturas.h"
#include "funcoes.h"

#define MAX_SIZE 400
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

const char nome1[] = "Diogo Ribeiro";
const char num1[] = "IST90051";
const char nome2[] = "Ricardo Caetano";
const char num2[] = "IST90177";

/**
 * filledCircleRGBA: renders a filled circle
 * \param _circleX x pos
 * \param _circleY y pos
 * \param _circleR radius
 * \param _r red
 * \param _g gree
 * \param _b blue
 */
void filledCircleRGBA(SDL_Renderer * _renderer, int _circleX, int _circleY, int _circleR, int _r, int _g, int _b)
{
    int off_x = 0;
    int off_y = 0;
    float degree = 0.0;
    float step = M_PI / (_circleR*8);

    SDL_SetRenderDrawColor(_renderer, _r, _g, _b, 255);

    while (_circleR > 0)
    {
        for (degree = 0.0; degree < M_PI/2; degree+=step)
        {
            off_x = (int)(_circleR * cos(degree));
            off_y = (int)(_circleR * sin(degree));
            SDL_RenderDrawPoint(_renderer, _circleX+off_x, _circleY+off_y);
            SDL_RenderDrawPoint(_renderer, _circleX-off_y, _circleY+off_x);
            SDL_RenderDrawPoint(_renderer, _circleX-off_x, _circleY-off_y);
            SDL_RenderDrawPoint(_renderer, _circleX+off_y, _circleY-off_x);
        }
        _circleR--;
    }
}
void RenderTable( int _board_size_px[], TTF_Font *_font, SDL_Surface *_img[], SDL_Renderer* _renderer )
{
    SDL_Texture *table_texture;
    SDL_Rect tableSrc, tableDest;

    // set color of renderer to some color
    SDL_SetRenderDrawColor( _renderer, 255, 255, 255, 255 );

    // clear the window
    SDL_RenderClear( _renderer );

    tableDest.x = tableSrc.x = 0;
    tableDest.y = tableSrc.y = 0;
    tableSrc.w = 902;
    tableSrc.h = 451;
    tableDest.w = 902;
    tableDest.h = 451;

    // draws the table texture
    table_texture = SDL_CreateTextureFromSurface(_renderer, _img[0]);
    SDL_RenderCopy(_renderer, table_texture, &tableSrc, &tableDest);

    // destroy everything
    SDL_DestroyTexture(table_texture);
    // return for later use
}

/**
 * RenderLogo function: Renders the IST logo on the app window
 * \param x X coordinate of the Logo
 * \param y Y coordinate of the Logo
 * \param _logoIST surface with the IST logo image to render
 * \param _renderer renderer to handle all rendering in a window
 */
int RenderLogo(int x, int y, SDL_Surface *_logoIST, SDL_Renderer* _renderer)
{
    SDL_Texture *text_IST;
    SDL_Rect boardPos;

    // space occupied by the logo
    boardPos.x = x;
    boardPos.y = y;
    boardPos.w = _logoIST->w;
    boardPos.h = _logoIST->h;

    // render it
    text_IST = SDL_CreateTextureFromSurface(_renderer, _logoIST);
    SDL_RenderCopy(_renderer, text_IST, NULL, &boardPos);

    // destroy associated texture !
    SDL_DestroyTexture(text_IST);
    return _logoIST->h;
}

/**
 * RenderText function: Renders some text on a position inside the app window
 * \param x X coordinate of the text
 * \param y Y coordinate of the text
 * \param text string with the text to be written
 * \param _font TTF font used to render the text
 * \param _color color of the text
 * \param _renderer renderer to handle all rendering in a window
 */
int RenderText(int x, int y, const char *text, TTF_Font *_font, SDL_Color *_color, SDL_Renderer* _renderer)
{
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    SDL_Rect solidRect;

    solidRect.x = x;
    solidRect.y = y;
    // create a surface from the string text with a predefined font
    text_surface = TTF_RenderText_Blended(_font,text,*_color);
    if(!text_surface)
    {
        printf("TTF_RenderText_Blended: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    // create texture
    text_texture = SDL_CreateTextureFromSurface(_renderer, text_surface);
    // obtain size
    SDL_QueryTexture( text_texture, NULL, NULL, &solidRect.w, &solidRect.h );
    // render it !
    SDL_RenderCopy(_renderer, text_texture, NULL, &solidRect);
    // clear memory
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
    return solidRect.h;
}
void InitSDL()
{
    // init SDL library
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        printf(" Failed to initialize SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * InitFont: Initializes the SDL2_ttf font library
 */
void InitFont()
{
    // Init font library
    if(TTF_Init()==-1)
    {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

/**
 * CreateWindow: Creates a window for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \return pointer to the window created
 */
SDL_Window* CreateWindow(int width, int height)
{
    SDL_Window *window;
    // init window
    window = SDL_CreateWindow( "Warming_Up", WINDOW_POSX, WINDOW_POSY, width, height, 0 );
    // check for error !
    if ( window == NULL )
    {
        printf("Failed to create window : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return window;
}

/**
 * CreateRenderer: Creates a renderer for the application
 * \param width width in px of the window
 * \param height height in px of the window
 * \param _window represents the window for which the renderer is associated
 * \return pointer to the renderer created
 */
SDL_Renderer* CreateRenderer(int width, int height, SDL_Window *_window)
{
    SDL_Renderer *renderer;
    // init renderer
    renderer = SDL_CreateRenderer( _window, -1, 0 );

    if ( renderer == NULL )
    {
        printf("Failed to create renderer : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // set size of renderer to the same as window
    SDL_RenderSetLogicalSize( renderer, width, height );

    return renderer;
}

void InitEverything(int width, int height, TTF_Font **_font, SDL_Surface *_img[], SDL_Window** _window, SDL_Renderer** _renderer)
{
    InitSDL();
    InitFont();
    *_window = CreateWindow(902, 551);
    *_renderer = CreateRenderer(902, 551, *_window);

    // load the image of the world map
    _img[0] = IMG_Load("mapa.jpg");
    if (_img[0] == NULL)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    // this opens (loads) a font file and sets a size
    *_font = TTF_OpenFont("FreeSerif.ttf", 16);
    if(!*_font)
    {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}
void posicao_cidades(tempinfo* cidade,float pos_x[100],float pos_y[100])
{
    tempinfo* aux;
    char city[1001] = "Ronaldo";
    int a=0, n=0;

    aux=cidade;
    while(aux!=NULL)
    {
        if(strstr(aux->city, city) == NULL)
        {
            strcpy(city, aux->city);
            if(aux->latitude.direcao=='N')
            {
                pos_y[a]=451/2-(451*(aux->latitude.angulo)/180);
            }
            if(aux->latitude.direcao=='S')
            {
                pos_y[a]=451/2+(451*aux->latitude.angulo/180);
            }
            if(aux->longitude.direcao=='E')
            {
                pos_x[a]=451+(902*aux->longitude.angulo/360);
            }
            if(aux->longitude.direcao=='W')
            {
                pos_x[a]=451-(902*aux->longitude.angulo/360);
            }
            a++;
        }
    aux=aux->next;
    n++;
    }
}
//função que põe e atuliza as bolas no mapa
void bolas(SDL_Renderer* renderer, TTF_Font* _font, float pos_x[100], float pos_y[100], tempinfo* cidade, int year)
{
    int n=0;
    char city[1000]="Ronaldo";
    tempinfo* aux;
    float adicao[1000]={0.0};
    int p=0, d[1000]={0};
    float media[1000]={0.0};

    SDL_Color dark = {0, 0, 0};
    SDL_Color white = {255, 255, 255};
    char str[MAX_SIZE] = {0};
    SDL_Rect text_area = {25, 400, 0, 0};
    aux=cidade;
    while(aux!=NULL)
    {
        if(aux->date.ano==year)
        {
            if(strcmp(aux->city, city)==0)
            {
                adicao[p]=adicao[p]+aux->temp_media;
                d[p]=d[p]+1;
            }
            else if(strcmp(aux->city, city)!=0)
            {
                strcpy(city, aux->city);
                p++;
            }

        }
        aux=aux->next;
    }
    for(n=0; n<=p; n++)
    {
        media[n]=adicao[n]/d[n];
    }
    sprintf(str, "%d", year);
    TTF_SizeText(_font, str, &text_area.w, &text_area.h);
    SDL_SetRenderDrawColor(renderer, dark.r, dark.g, dark.b, 255);
    SDL_RenderFillRect(renderer, &text_area);
    RenderText(text_area.x, text_area.y, str, _font, &white, renderer);
    for(n=0; n<=p; n++)
    {
        if(media[n]<=-5)
        {
            filledCircleRGBA(renderer , pos_x[n], pos_y[n], 4 , 0, 0 , 255);
        }
        if(media[n]>-5 && media[n]<=-2)
        {
            filledCircleRGBA(renderer , pos_x[n], pos_y[n], 4 , 0, 255 , 255);
        }
        if(media[n]>-2 && media[n]<=10)
        {
           filledCircleRGBA(renderer , pos_x[n], pos_y[n], 4 , 255, 255 , 155);
        }
        if(media[n]>10 && media[n]<=20)
        {
            filledCircleRGBA(renderer , pos_x[n], pos_y[n], 4 , 255, 128 , 0);
        }
        if(media[n]>20)
        {
            filledCircleRGBA(renderer , pos_x[n], pos_y[n], 4 , 255, 0 , 0);
        }
    }
}
//Render do nome dos alunos
void NomeAlunos (SDL_Renderer *_renderer, TTF_Font *_font) {

    SDL_Color black = {0, 0, 0};

    RenderText(738, 460, nome1, _font, &black, _renderer);
    RenderText(738, 480, num1, _font, &black, _renderer);
    RenderText(738, 505, nome2, _font, &black, _renderer);
    RenderText(738, 525, num2, _font, &black, _renderer);

}
