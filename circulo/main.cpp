#include <SDL/SDL.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "circulo.h"
#include "retangulo.h"

Circulo *c1=new Circulo(0.5, 0.5, 0.2);
Circulo *c2=new Circulo(-0.5,-0.5,0.2);
Retangulo *r1=new Retangulo(0.5,-0.5,0.2,0.4);


static void quit( int code )
{
    /*
     * Finaliza o SDL depois saiu do programa
     */
    SDL_Quit( );

    /* sai do programa */
    exit( code );
}
static void handle_key_up( SDL_keysym* keysym )
{
    switch( keysym->sym ) {
    case SDLK_ESCAPE:
        quit( 0 );
        break;
        
        
    default:
        break;
    
}

static void handle_key_down( SDL_keysym* keysym )
{

    switch( keysym->sym ) {
    case SDLK_ESCAPE:
        quit( 0 );
        break;
        
    case SDLK_LEFT:
        cl->vx=0.0001;
    default:
        break;
    }

}

static void process_events( void )
{
    /* Funçao de tratamento de eventos */
    SDL_Event event;

    /* loop para tratar todos os eventos na fila */
    while( SDL_PollEvent( &event ) ) {

        switch( event.type ) {
        case SDL_KEYDOWN:
            /* trata tecla pressionada */
            handle_key_down( &event.key.keysym );
            break;
        case SDL_QUIT:
            /* fecha o programa */
            quit( 0 );
            break;
        }

    }

}

static void draw_screen( void )
{




    /* Clear the color and depth buffers. */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* Carrega matriz identidade */
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    //c1->vx=-0.0001;

    c1->draw2();
    c2->draw2();
    r1->draw();

    c1->update(1);
    c2->update(1);
    r1->update(1);

    SDL_GL_SwapBuffers( );
}

static void setup_opengl( int width, int height )
{
    // Modelo de sombra GL_SMOOTH ou GL_FLAT
    glShadeModel( GL_SMOOTH );


    //glCullFace( GL_BACK );
    //glFrontFace( GL_CCW );
    //glEnable( GL_CULL_FACE );


    /* Cor de fundo */
    glClearColor( 0, 0, 0, 0 );

    /* Configura tamanho da janela */
    glViewport( 0, 0, width, height );

    /*
     * Incializa matriz de projeção com identidade, ou seja sem projeção
     */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
}

int main( int argc, char* argv[] )
{


    /* Inicializa o SDL */
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        /* Se não conseguir da erro*/
        fprintf( stderr, "Video initialization failed: %s\n",
             SDL_GetError( ) );
        quit( 1 );
    }

    /*pega informações sobre o dispositivo de video*/
    const SDL_VideoInfo* info =  SDL_GetVideoInfo( );
    if( !info ) {
        /* Caso não encontrou , não deveria acontecer */
        fprintf( stderr, "Video query failed: %s\n",
             SDL_GetError( ) );
        quit( 1 );
    }
    /* tamanho da janela */
    int width = 640;
    int height = 480;

     /* bits por pixel */
    int bpp = info->vfmt->BitsPerPixel;


    /*
     * usa 16 bits para teste de profundidade
     * usa dois buffers para renderizar
     */
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    //modo de abertura
    int flags=0;
    flags+=SDL_OPENGL;
    //flags+=SDL_FULLSCREEN;

    if( SDL_SetVideoMode( width, height, bpp,flags ) == 0 ) {
        /*
         * erro não conseguiu abrir a janela
         */
        fprintf( stderr, "Video mode set failed: %s\n",
             SDL_GetError( ) );
        quit( 1 );
    }


    setup_opengl( width, height );

    /*
     * loop principal
     */
    while( 1 ) {
        /* trata os eventos */
        process_events( );
        /* desenha na tela */
        draw_screen( );
    }

    return 0;
}

