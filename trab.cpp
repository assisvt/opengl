#include <SDL/SDL.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// VITOR DE ASSUS
static void quit( int code )
{
    /*
     * Finaliza o SDL depois saiu do programa
     */
    SDL_Quit( );

    /* sai do programa */
    exit( code );
}

static void handle_key_down( SDL_keysym* keysym )
{

    /*
     * Se apertar ESC fecha o programa
     * exercicio alterar posição do triangulo usando as setas
     */
    switch( keysym->sym ) {
    case SDLK_ESCAPE:
        quit( 0 );
        break;
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

float ang=0;

float lado = 0;

static void draw_screen( void )
{

    static GLfloat v0[] = {  0.0f,  0.0f, 0.0f };
    static GLfloat v1[] = {  0.75f,-0.2f, 0.0f };
    static GLfloat v2[] = {  0.75f, 0.2f, 0.0f };

    static GLfloat t0[] = {  0.0f, 0.0f,  0.0f };
    static GLfloat t1[] = {  0.2f, 0.75f,  0.0f };
    static GLfloat t2[] = { -0.2f, 0.75f,  0.0f };

    static GLfloat s0[] = {  0.0f,  0.0f,   0.0f };
    static GLfloat s1[] = { -0.75f, 0.2f,   0.0f };
    static GLfloat s2[] = { -0.75f, -0.2f,  0.0f };

    static GLfloat q0[] = { -0.05f,  0.0f,  0.0f };
    static GLfloat q1[] = {  0.05f,  0.0f,  0.0f };
    static GLfloat q2[] = {  0.05f, -1.0f,  0.0f };
    static GLfloat q3[] = { -0.05f, -1.0f,  0.0f };




    // (x,y,z)


    static GLubyte red[]    = { 255,   0,   0, 255 };
    static GLubyte green[]  = {   0, 255,   0, 255 };
    static GLubyte blue[]   = {   0,   0, 255, 255 };


    /* Clear the color and depth buffers. */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* Carrega matriz identidade */
    glMatrixMode( GL_MODELVIEW );
    float PI=3.1415;
    ang+=0.1;
    if(ang>=360)
        ang=0;

    lado -= 0.0002;
    if (lado <= -2)
            lado = 2;




    GLfloat matRot[]={
        cos(ang),sin(ang),0,0,
       -sin(ang),cos(ang),0,0,
        0,       0,       1,0,
        0,       0,       0,1
    };

    GLfloat matScale[]={
        0.5,0,0,0,
        0,0.5,0,0,
        0,0,1,0,
        0,0,0,1
    };


    GLfloat matTranslacao[]={
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        -0.75,0.75,0,1
    };


    GLfloat matTranslacaoR1[]={
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0.5,-0.5,0,1
    };
    GLfloat matTranslacaoR2[]={
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        -0.5,0.5,0,1
    };

    GLfloat matSH[]={
        1,0.2,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };




    glLoadIdentity( );

    /*
    glMultMatrixf(matTranslacaoR2);
    glMultMatrixf(matRot);
    glMultMatrixf(matTranslacaoR1);

    glMultMatrixf(matTranslacao);
    glMultMatrixf(matScale);
    glMultMatrixf(matSH);
    */

    //glTranslatef(0.1f, 0.6f, 0.0f);


    glTranslatef(lado, 0.5,0);

    //glTranslatef(-0.75,0.75,0);
    //glScalef(0.5,0.5,1);

    glBegin(GL_QUADS);

    glColor4ubv(red);
    glVertex3fv(q3);
    glVertex3fv(q2);
    glVertex3fv(q1);
    glVertex3fv(q0);

    glEnd();


    glRotatef(ang,0,0,1);
    glTranslatef(-0.0f, -0.0f,  0.0f);


    /* Envia os pontos para a pipeline */
    glBegin( GL_TRIANGLES);

    glColor4ubv( green );
    glVertex3fv( v0 );
    glVertex3fv( v1 );
    glVertex3fv( v2 );

    glColor4ubv( red );
    glVertex3fv( t0 );
    glVertex3fv( t1 );
    glVertex3fv( t2 );

    glColor4ubv( blue );
    glVertex3fv( s0 );
    glVertex3fv( s1 );
    glVertex3fv( s2 );



    glEnd();


    SDL_GL_SwapBuffers( );
}

static void setup_opengl( int width, int height )
{
    // Modelo de sombra GL_SMOOTH ou GL_FLAT
    glShadeModel( GL_SMOOTH );


    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );


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
