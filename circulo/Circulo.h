#ifndef CIRCULO_H
#define CIRCULO_H
#include <GL/gl.h>

class Circulo
{
    public:
        Circulo(float Xc, float Yc, float R);
        void draw();
        void draw2();
        virtual ~Circulo();
        void update();
        float vx,vy;


    protected:

    private:
        GLfloat centro[3];
        float R;
};

#endif // CIRCULO_H

