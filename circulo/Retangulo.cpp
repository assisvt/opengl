#include "Retangulo.h"
#include <GL/gl.h>
Retangulo::Retangulo(float x, float y, float l, float a)
{
    this->x=x;
    this->y=y;
    this->l=l;
    this->a=a;
    this->vx=0;
    this->vy=0;
}

Retangulo::~Retangulo()
{
    //dtor
}

void Retangulo::draw(){ //va,ps passar em sentido anti-horario
    glBegin(GL_QUADS);

    glVertex3f(this->x, this->y, 0);
    glVertex3f(this->x+this->l,this->y,0);
    glVertex3f(this->x+this->l,this->y+this->a,0);
    glVertex3f(this->x, this->y+this->a,0);
    glEnd();

}

void Retangulo::update(float deltaTime) {
    this->x+=this->vx*deltaTime;
    this->y+=this->vy*deltaTime;

}

