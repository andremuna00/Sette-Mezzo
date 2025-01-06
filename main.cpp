/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

//The headers
#include <ctime>
#include <cstdlib>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <windows.h>

const int LARGHEZZA_SCHERMO = 800;
const int ALTEZZA_SCHERMO = 600;
const int SCREEN_BPP = 32;

const int CLIP_SICOLORE = 0;
const int CLIP_SI = 1;
const int CLIP_NOCOLORE = 2;
const int CLIP_NO = 3;

SDL_Surface *bottoni = NULL;
SDL_Surface *message = NULL;
SDL_Surface *messaggio = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *Uno = NULL;
SDL_Surface *Due = NULL;
SDL_Surface *Tre = NULL;
SDL_Surface *Quattro = NULL;
SDL_Surface *Cinque = NULL;
SDL_Surface *Sei = NULL;
SDL_Surface *Sette = NULL;
SDL_Surface *Figura = NULL;
SDL_Surface *Carta = NULL;
SDL_Surface *Retro = NULL;
SDL_Surface *Sfondo = NULL;

SDL_Event event;

TTF_Font *scritta = NULL;
TTF_Font *titolo = NULL;
TTF_Font *corsivo = NULL;

SDL_Color Colore_testo = { 0, 0, 0 };

SDL_Rect clips[ 4 ];

class Bottone_si
{
    private:
    SDL_Rect box;

    SDL_Rect* clip;

    public:
    Bottone_si( int x, int y, int w, int h );

    void handle_events();

    void show();
};

class Bottone_no
{
    private:
    SDL_Rect box;

    SDL_Rect* clip2;

    public:

    Bottone_no( int x, int y, int w, int h );

    void handle_events2();

    void show2();
};
class Inizio
{
    private:

    SDL_Rect box;

    SDL_Rect* clip3;

    public:
    Inizio( int x, int y, int w, int h );

    bool handle_events3();

    void show3();
};

SDL_Surface *carica_immagine( std::string filename )
{

    SDL_Surface* immagine_caricata = NULL;

    SDL_Surface* immagine_ottimizzata = NULL;

    immagine_caricata = IMG_Load( filename.c_str() );

    if( immagine_caricata != NULL )
    {
        immagine_ottimizzata = SDL_DisplayFormat( immagine_caricata );

        SDL_FreeSurface( immagine_caricata );

        if( immagine_ottimizzata != NULL )
        {
            SDL_SetColorKey( immagine_ottimizzata, SDL_SRCCOLORKEY, SDL_MapRGB( immagine_ottimizzata->format, 0, 0xFF, 0xFF ) );
        }
    }

    return immagine_ottimizzata;
}

void applica_immagine( int x, int y, SDL_Surface* sorgente, SDL_Surface* destinazione, SDL_Rect* clip = NULL )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( sorgente, clip, destinazione, &offset );
}

bool init()
{
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    screen = SDL_SetVideoMode( LARGHEZZA_SCHERMO, ALTEZZA_SCHERMO, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL )
    {
        return false;
    }
    
    if( TTF_Init() == -1 )
    {
        return false;
    }

    SDL_WM_SetCaption( "Sette e mezzo", NULL );

    return true;
}

bool load_files()
{
    bottoni = carica_immagine( "button.png" );

    if( bottoni == NULL )
    {
        return false;
    }
    
    Sfondo = carica_immagine( "sfondo.png" );

    if( Sfondo == NULL )
    {
        return false;
    }
    
    Retro = carica_immagine( "Retro.png" );

    if( Retro == NULL )
    {
        return false;
    }
    
    scritta = TTF_OpenFont( "game_over.ttf", 60 );

    if( scritta == NULL )
    {
        return false;
    }
    
    titolo = TTF_OpenFont( "game_over.ttf", 230 );

    if( titolo == NULL )
    {
        return false;
    }
    
    corsivo = TTF_OpenFont( "Corsivo.ttf", 30 );

    if( corsivo == NULL )
    {
        return false;
    }
    
    Uno = carica_immagine( "Uno.png" );

    if( Uno == NULL )
    {
        return false;
    }
    
    Due = carica_immagine( "Due.png" );

    if( Due == NULL )
    {
        return false;
    }
    
    Tre = carica_immagine( "Tre.png" );

    if( Tre == NULL )
    {
        return false;
    }
    
    Quattro = carica_immagine( "Quattro.png" );

    if( Quattro == NULL )
    {
        return false;
    }
    
    Cinque = carica_immagine( "Cinque.png" );

    if( Cinque == NULL )
    {
        return false;
    }
    
    Sei = carica_immagine( "Sei.png" );

    if( Sei == NULL )
    {
        return false;
    }
    
    Sette = carica_immagine( "Sette.png" );

    if( Sette == NULL )
    {
        return false;
    }
    
    Figura = carica_immagine( "Figura.png" );

    if( Figura == NULL )
    {
        return false;
    }

    return true;
}

void clean_up()
{
    SDL_FreeSurface( bottoni );
    SDL_FreeSurface( message );
    SDL_FreeSurface( messaggio );
    SDL_FreeSurface( Sfondo );
    SDL_FreeSurface( Retro );
    SDL_FreeSurface( Uno );
    SDL_FreeSurface( Due );
    SDL_FreeSurface( Tre );
    SDL_FreeSurface( Quattro );
    SDL_FreeSurface( Cinque );
    SDL_FreeSurface( Sei );
    SDL_FreeSurface( Sette );
    SDL_FreeSurface( Figura );
    TTF_CloseFont( scritta );
    TTF_CloseFont( titolo );
    TTF_CloseFont( corsivo );

    TTF_Quit();

    SDL_Quit();
}

void set_clips()
{
    clips[ CLIP_SI ].x = 0;
    clips[ CLIP_SI ].y = 0;
    clips[ CLIP_SI ].w = 160;
    clips[ CLIP_SI ].h = 120;

    clips[ CLIP_NO ].x = 160;
    clips[ CLIP_NO ].y = 0;
    clips[ CLIP_NO ].w = 160;
    clips[ CLIP_NO ].h = 120;

    clips[ CLIP_SICOLORE ].x = 0;
    clips[ CLIP_SICOLORE ].y = 120;
    clips[ CLIP_SICOLORE ].w = 160;
    clips[ CLIP_SICOLORE ].h = 120;

    clips[ CLIP_NOCOLORE ].x = 160;
    clips[ CLIP_NOCOLORE ].y = 120;
    clips[ CLIP_NOCOLORE ].w = 160;
    clips[ CLIP_NOCOLORE ].h = 120;
}

Bottone_si::Bottone_si( int x, int y, int w, int h )
{
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;

    clip = &clips[ CLIP_SI ];
    applica_immagine(0, 0, Sfondo, screen, NULL);
}
Bottone_no::Bottone_no( int x, int y, int w, int h )
{
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;

    clip2 = &clips[ CLIP_NO ];
}
Inizio::Inizio( int x, int y, int w, int h )
{
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    applica_immagine(0, 0, Sfondo, screen, NULL);
}
bool Inizio::handle_events3()
{  
    int x=0;
    int y=0;
    if( event.type == SDL_MOUSEBUTTONUP )
    {
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            x = event.button.x;
            y = event.button.y;

            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                return true;
            }    
        }
    }
    
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            x = event.button.x;
            y = event.button.y;

            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                return true;
            }
        }
    }
    return false;
}

void Bottone_si::show()
{
    applica_immagine( box.x, box.y, bottoni, screen, clip );
}

void Bottone_no::show2()
{
    applica_immagine( box.x, box.y, bottoni, screen, clip2 );
}
void scritte()
{
     message = TTF_RenderText_Solid( scritta, "PUNTEGGIO", Colore_testo );
     applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , 0, message, screen, NULL ); 
     message = TTF_RenderText_Solid( scritta, "Si = estrazione carta", Colore_testo );
     applica_immagine( 0, 0, message, screen, NULL );
     message = TTF_RenderText_Solid( scritta, "No = turno PC", Colore_testo );
     applica_immagine(  0, 30, message, screen, NULL ); 
}

int main( int argc, char* args[] )
{
    srand(time(0));

    bool quit = false;
    bool quit1 = false;
    bool perso = false;
    bool vinto = false;
    bool premere=false;

    if( init() == false )
    {
        return 1;
    }

    if( load_files() == false )
    {
        return 1;
    }

    set_clips();
    bool stop=false;
    bool controllo=true;
    bool perso1=false;
    bool premere2=true;
    
    double somma2=0;
    double somma=0;
    int altezza=10;
    int distanza=0;
    int i=1;
    Inizio schermo( 0, 0, 800, 600 );
    Bottone_si si( 0, 600-120, 320, 240 );
    Bottone_no no (800-160, 600-120, 320, 240);
    if(premere2==true)
    {
           applica_immagine (0, 0, Sfondo, screen, NULL);
           message = TTF_RenderText_Solid( titolo, "SETTE E MEZZO", Colore_testo );
           applica_immagine((LARGHEZZA_SCHERMO - message->w)/2, (ALTEZZA_SCHERMO - message->h)/2, message, screen, NULL );
                             
           message = TTF_RenderText_Solid( scritta, "Premere un tasto per continuare", Colore_testo );
           applica_immagine((LARGHEZZA_SCHERMO - message->w)/2, (ALTEZZA_SCHERMO - message->h)/2+80, message, screen, NULL );
                             
           message = TTF_RenderText_Solid( corsivo, "© Andrea Munarin", Colore_testo );
           applica_immagine(0, ALTEZZA_SCHERMO - message->h, message, screen, NULL );
           
    }

    while( quit == false )
    {

        if( SDL_PollEvent( &event ) )
        {
            int x = 0, y = 0;
            

            {   
                
                 
                 
                message = TTF_RenderText_Solid( scritta, "Si = estrazione carta", Colore_testo );
                applica_immagine( 0, 0, message, screen, NULL );
     
                message = TTF_RenderText_Solid( scritta, "No = turno PC", Colore_testo );
                applica_immagine(  0, 30, message, screen, NULL );
     
                message = TTF_RenderText_Solid( scritta, "PUNTEGGIO", Colore_testo );
                applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , 0, message, screen, NULL ); 

                if( event.type == SDL_MOUSEBUTTONUP )
                {
                    message = TTF_RenderText_Solid( scritta, "PUNTEGGIO", Colore_testo );
                    applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , 0, message, screen, NULL ); 
                    message = TTF_RenderText_Solid( scritta, "Si = estrazione carta", Colore_testo );
                    applica_immagine( 0, 0, message, screen, NULL );
     
                    message = TTF_RenderText_Solid( scritta, "No = turno PC", Colore_testo );
                    applica_immagine(  0, 30, message, screen, NULL );  
                    if( event.button.button == SDL_BUTTON_LEFT )
                    {
                        
                                            x = event.button.x;
                                            y = event.button.y;
                                            if(premere!=true&&premere2!=true)
                                                {
                                            if( ( x > 0 ) && ( x < 0 + 320 ) && ( y > 600-120 ) && ( y < 600-120 + 240 ) )
                                            {
                                                if(controllo==true)
                                                {
                                                applica_immagine(0, 0, Sfondo, screen, NULL);
                                                }
                                                    int carta=rand()%10+1;
                                                    switch(carta)
                                                    {
                                                                 case 1:
                                                                      Carta = Uno;
                                                                      somma+=1;
                                                                      message = TTF_RenderText_Solid( scritta, "1,0", Colore_testo );
                                                                      altezza+=30;
                                                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);   
                                                                      break;
                                                                 case 2:
                                                                      Carta = Due;
                                                                      somma+=2;
                                                                      message = TTF_RenderText_Solid( scritta, "2,0", Colore_testo );
                                                                      altezza+=30;
                                                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
                                                                      break;
                                                                 case 3:
                                                                      Carta = Tre;
                                                                      somma+=3;
                                                                      message = TTF_RenderText_Solid( scritta, "3,0", Colore_testo );
                                                                      altezza+=30;
                                                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
                                                                      break;
                                                                 case 4:
                                                                      Carta = Quattro;
                                                                      somma+=4;
                                                                      message = TTF_RenderText_Solid( scritta, "4,0", Colore_testo );
                                                                      altezza+=30;
                                                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
                                                                      break;
                                                                 case 5:
                                                                      Carta = Cinque;
                                                                      somma+=5;
                                                                      message = TTF_RenderText_Solid( scritta, "5,0", Colore_testo );
                                                                      altezza+=30;
                                                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
                                                                      break;
                                                                 case 6:
                                                                      Carta = Sei;
                                                                      somma+=6;
                                                                      message = TTF_RenderText_Solid( scritta, "6,0", Colore_testo );
                                                                      altezza+=30;
                                                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
                                                                      break;
                                                                 case 7:
                                                                      Carta = Sette;
                                                                      somma+=7;
                                                                      message = TTF_RenderText_Solid( scritta, "7,0", Colore_testo );
                                                                      altezza+=30;
                                                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
                                                                      break;
                                                                 case 8:
                                                                      Carta = Figura;
                                                                      somma+=0.5;
                                                                      message = TTF_RenderText_Solid( scritta, "0,5", Colore_testo );
                                                                      altezza+=30;
                                                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
                                                                      break;
                                                                 case 9:
                                                                      Carta = Figura;
                                                                      somma+=0.5;
                                                                      message = TTF_RenderText_Solid( scritta, "0,5", Colore_testo );
                                                                      altezza+=30;
                                                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
                                                                      break;
                                                                 case 10:
                                                                      Carta = Figura;
                                                                      somma+=0.5;
                                                                      message = TTF_RenderText_Solid( scritta, "0,5", Colore_testo );
                                                                      altezza+=30;
                                                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
                                                                      break;
                                                                 default:
                                                                         break;
                                                    }
                                                    controllo=false;
                                                    applica_immagine(distanza, ( ALTEZZA_SCHERMO - Carta->h )/2, Carta, screen);
                                                    distanza+=120;
                                                    
                                                    
                                            }
                                            }
                    }
     }
     if( event.type == SDL_MOUSEBUTTONDOWN )
            {
            if( event.button.button == SDL_BUTTON_LEFT )
            {
             x = event.button.x;
             y = event.button.y;
             if(premere2!=true||premere!=true)
             {
             if(premere!=true)
             {
            if( ( x > 0 ) && ( x < 0 + 320 ) && ( y > 600-120 ) && ( y < 600-120 + 240 ) )
            {
                applica_immagine( distanza, ( ALTEZZA_SCHERMO - 315 ) / 2, Retro, screen, NULL);
                SDL_Flip( screen );
            }
            if( ( x > 800-160 ) && ( x < 800-160 + 320 ) && ( y > 600-120 ) && ( y < 600-120 + 240 ) )
            {
                applica_immagine( ( LARGHEZZA_SCHERMO - 226 ) / 2, ( ALTEZZA_SCHERMO - 315 ) / 2, Retro, screen, NULL);
                SDL_Flip( screen );
            }
            }
            }
            }
            }
            if(somma>7.5)
            {
            message = TTF_RenderText_Solid( scritta, "__", Colore_testo );

                        applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
            //applica_immagine(0,0, Sfondo, screen, NULL);
            if(somma==8)
            {
                        message = TTF_RenderText_Solid( scritta, "8,0", Colore_testo );
                        altezza+=30;
                        applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
            }
            if(somma==8.5)
            {
                        message = TTF_RenderText_Solid( scritta, "8,5", Colore_testo );
                        altezza+=30;
                        applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
            }
            if(somma==9)
            {
                        message = TTF_RenderText_Solid( scritta, "9,0", Colore_testo );
                        altezza+=30;
                        applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
            }
            if(somma==9.5)
            {
                        message = TTF_RenderText_Solid( scritta, "9,5", Colore_testo );
                        altezza+=30;
                        applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
            }
            if(somma==10)
            {
                        message = TTF_RenderText_Solid( scritta, "10,0", Colore_testo );
                        altezza+=30;
                        applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
            }
            if(somma==10.5)
            {
                        message = TTF_RenderText_Solid( scritta, "10,5", Colore_testo );
                        altezza+=30;
                        applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
            }
            if(somma==11)
            {
                        message = TTF_RenderText_Solid( scritta, "11,0", Colore_testo );
                        altezza+=30;
                        applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
            }
            if(somma==11.5)
            {
                        message = TTF_RenderText_Solid( scritta, "11,5", Colore_testo );
                        altezza+=30;
                        applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
            }
            if(somma==12)
            {
                        message = TTF_RenderText_Solid( scritta, "12,0", Colore_testo );
                        altezza+=30;
                        applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
            }
            if(somma==12.5)
            {
                        message = TTF_RenderText_Solid( scritta, "12,5", Colore_testo );
                        altezza+=30;
                        applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL);  
            }
            somma=0;
            altezza=10;
            distanza-=120;
            applica_immagine(distanza, ( ALTEZZA_SCHERMO - Carta->h )/2, Carta, screen);
            distanza=0;
            message = TTF_RenderText_Solid( titolo, "HAI PERSO", Colore_testo );
            applica_immagine(  (LARGHEZZA_SCHERMO - message->w)/2 , (ALTEZZA_SCHERMO - message->w)/2-35, message, screen, NULL);
            controllo=true;
            perso1=true;
            }
              
     message = TTF_RenderText_Solid( scritta, "PUNTEGGIO", Colore_testo );
     applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , 0, message, screen, NULL );   

    if( event.type == SDL_MOUSEBUTTONUP )
    {
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            if(premere2==true)
            {
                              premere2=false;
                              applica_immagine(0,0,Sfondo,screen,NULL); 
            }
            if(premere==true)
            {
            premere=false;
            applica_immagine(0,0,Sfondo,screen,NULL);
            
            }
            x = event.button.x;
            y = event.button.y;

            if( ( x > 800-160 ) && ( x < 800-160 + 320 ) && ( y > 600-120 ) && ( y < 600-120 + 240 ) )
            {
                  
                applica_immagine(0, 0, Sfondo, screen, NULL);
                int distanza=0;
                int lunghezza=226;
                int altezza=10;
                do
                {   
                    int carta=rand()%10+1;
                    switch(carta)
                    {
                                 case 1:
                                      Carta = Uno;
                                      somma2+=1;
                                      message = TTF_RenderText_Solid( scritta, "1,0", Colore_testo );
                                      altezza+=30;
                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL); 
                                      break;
                                 case 2:
                                      Carta = Due;
                                      somma2+=2;
                                      message = TTF_RenderText_Solid( scritta, "2,0", Colore_testo );
                                      altezza+=30;  
                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL); 
                                      break;
                                 case 3:
                                      Carta = Tre;
                                      somma2+=3;
                                      message = TTF_RenderText_Solid( scritta, "3,0", Colore_testo );
                                      altezza+=30;  
                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL); 
                                      break;
                                 case 4:
                                      Carta = Quattro;
                                      somma2+=4;
                                      message = TTF_RenderText_Solid( scritta, "4,0", Colore_testo );
                                      altezza+=30; 
                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL); 
                                      break;
                                 case 5:
                                      Carta = Cinque;
                                      somma2+=5;
                                      message = TTF_RenderText_Solid( scritta, "5,0", Colore_testo );
                                      altezza+=30;
                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL); 
                                      break;
                                 case 6:
                                      Carta = Sei;
                                      somma2+=6;
                                      message = TTF_RenderText_Solid( scritta, "6,0", Colore_testo );
                                      altezza+=30;
                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL); 
                                      break;
                                 case 7:
                                      Carta = Sette;
                                      somma2+=7;
                                      message = TTF_RenderText_Solid( scritta, "7,0", Colore_testo ); 
                                      altezza+=30;
                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL); 
                                      break;
                                 case 8:
                                      Carta = Figura;
                                      somma2+=0.5;
                                      message = TTF_RenderText_Solid( scritta, "0,5", Colore_testo );
                                      altezza+=30;
                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL); 
                                      break;
                                 case 9:
                                      Carta = Figura;
                                      somma2+=0.5;
                                      message = TTF_RenderText_Solid( scritta, "0,5", Colore_testo );
                                      altezza+=30;
                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL); 
                                      break;
                                 case 10:
                                      Carta = Figura;
                                      somma2+=0.5;
                                      message = TTF_RenderText_Solid( scritta, "0,5", Colore_testo );
                                      altezza+=30; 
                                      applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , altezza, message, screen, NULL); 
                                      break;
                                 default:
                                         break;
                    }
                    
                    message = TTF_RenderText_Solid( scritta, "PUNTEGGIO", Colore_testo );
                    applica_immagine(  LARGHEZZA_SCHERMO - message->w-10 , 0, message, screen, NULL ); 
                      
                    applica_immagine(distanza, ( ALTEZZA_SCHERMO - Carta->h )/2, Carta, screen);
                    distanza+=120;
                    
                    message = TTF_RenderText_Solid( scritta, "TURNO PC", Colore_testo );
                    applica_immagine( ( LARGHEZZA_SCHERMO - message->w ) / 2, 10, message, screen, NULL );
                    if(somma2>somma)
                    {
                    stop=true;
                    }
                }
                while(somma2<=somma);
                distanza=0;
                if(somma2>somma&&somma2<=7.5)
                {
                                                somma2=0;
                                                somma=0;
                                                altezza=10;
                                                distanza=0;
                                                message = TTF_RenderText_Solid( titolo, "HAI PERSO", Colore_testo );
                                                applica_immagine(  (LARGHEZZA_SCHERMO - message->w)/2 , (ALTEZZA_SCHERMO - message->w)/2-30, message, screen, NULL); 
                                                controllo=true;
                                                perso=true;
                }
                else
                {
                                                somma2=0;
                                                somma=0;
                                                altezza=10;
                                                distanza=0;
                                                message = TTF_RenderText_Solid( titolo, "HAI VINTO", Colore_testo );
                                                applica_immagine( (LARGHEZZA_SCHERMO - message->w)/2 , (ALTEZZA_SCHERMO - message->w)/2-40, message, screen, NULL);
                                                controllo=true;
                                                vinto=true;
                }
                
            }
        }
    } 
                if(vinto!=true&&perso!=true&&premere2!=true&&perso1!=true)
                {
                si.show();
                no.show2();
                scritte();
                }
                else
                {
                    if(vinto==true||perso==true||perso1==true)
                    {
                    premere=true;
                    vinto=false;
                    perso=false;
                    perso1=false;
                    altezza=10;
                    distanza=0;
                }
            }

            if( event.type == SDL_MOUSEMOTION )
               {
                   if(premere==true)
                   {
                   applica_immagine(0, 0, Sfondo, screen, NULL);    
                   message = TTF_RenderText_Solid(scritta, "Premere un tasto per giocare", Colore_testo );
                   applica_immagine((LARGHEZZA_SCHERMO - message->w)/2 , (ALTEZZA_SCHERMO - message->w)/2, message, screen, NULL);    
                   }
                   if(premere2==true)
                   {
                    applica_immagine (0, 0, Sfondo, screen, NULL);
                    message = TTF_RenderText_Solid( titolo, "SETTE E MEZZO", Colore_testo );
                    applica_immagine((LARGHEZZA_SCHERMO - message->w)/2, (ALTEZZA_SCHERMO - message->h)/2, message, screen, NULL );
                             
                    message = TTF_RenderText_Solid( scritta, "Premere un tasto per continuare", Colore_testo );
                    applica_immagine((LARGHEZZA_SCHERMO - message->w)/2, (ALTEZZA_SCHERMO - message->h)/2+80, message, screen, NULL );
                             
                    message = TTF_RenderText_Solid( corsivo, "© Andrea Munarin", Colore_testo );
                    applica_immagine(0, ALTEZZA_SCHERMO - message->h, message, screen, NULL ); 
                   }
                   }
                      
               }
            if( event.type == SDL_QUIT )
            {

                quit = true;
            }
        }

        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }
        
    }
    
    clean_up();

    return 0;
}
