#include "Circulo.h"
#include <math.h>

Circulo::Circulo(float Xc, float Yc, float R)
{
    this->centro[0]= Xc;
    this->centro[1]= Yc;
    this->centro[2]= 0;
    this->R=R;
    this->
}

Circulo::~Circulo()
{
    //dtor
}

void Circulo::draw()
{
    glBegin(GL_TRIANGLE_FAN);

    glVertex3fv(this->centro);

    int nPontos=30;
    float ang =0;
    for(int i=0; i<nPontos+1;i++){
        GLfloat p_i[3];
        p_i[0]=this->centro[0] + cos(ang)*this->R;
        p_i[1]=this->centro[1] + sin(ang)*this->R;
        p_i[2]=0;
        glVertex3fv(p_i);
        ang+=2*M_PI/nPontos;
    }
        glEnd();
}


void Circulo::draw2()
{
    glPushMatrix();
    glTranslatef(this->centro[0], this-> centro[1], 0);
    glScalef(this->R, this-> R,1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 0);
    float ang=0;
    int nPontos=30;
    for(int i=0; i<nPontos+1;i++) {
        glVertex3f(cos(ang),sin(ang), 0);
        ang+=2*M_PI/nPontos;
    }

    glEnd();

    //glScalef(1.0/this->R, 1.0/this->R,1);
    //glTranslatef(-this->centro[0], this-> centro[1], 0);
    glPopMatrix();
}

void Circulo::update(float deltaTime)
{
    this->centro[0]+=vx*deltaTime;
    this->centro[1]+=vy*deltaTime;
}


