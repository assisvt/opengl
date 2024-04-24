#ifndef RETANGULO_H
#define RETANGULO_H


class Retangulo
{
    public:
        Retangulo(float x, float y, float l, float a);
        void draw();
        virtual ~Retangulo();
        float vx,vy;
        void update(float deltaTime);

    protected:

    private:
        float x,y,l,a;
};

#endif // RETANGULO_H

