#include "BoundedBuffer.cpp"
#include "BMP.cpp"
#include <iostream>
using namespace std;
#ifndef GRAYSCALE_CPP
#define GRAYSCALE_CPP
_Task GrayScale
{
    BoundedBuffer &Buffer;

  public:
    GrayScale(BoundedBuffer & buf) : Buffer(buf) {}

  private:
    void main()
    {
        for (;;)
        {
            yield(rand() % 20); // duerma un rato
            BMP img = Buffer.remove();
            if (img.getTamano() == -1) break;
            GreyScale(img);
        }
    }
    /* Funcion encargada de pasar la imagen a escala de grises.
    Entrada: Estructura con la informacion de la imagen. */
    void GreyScale(BMP image)
    {
        int R, G, B, grey, i, j;
        for (i = image.getAlto() - 1; i >= 0; i--)
        {
            for (j = 0; j < image.getAncho(); j++)
            {
                B = image.getPixelBE(i, j) * 0.11;
                G = image.getPixelGE(i, j) * 0.59;
                R = image.getPixelRE(i, j) * 0.3;
                grey = B + G + R;
                image.setPixelBE(i, j, grey);
                image.setPixelGE(i, j, grey);
                image.setPixelRE(i, j, grey);
            }
        }
    }
};
#endif