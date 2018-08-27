#include "BoundedBuffer.cpp"
#include "BMP.cpp"
#include <iostream>
using namespace std;
#ifndef BINARY_CPP
#define BINARY_CPP
_Task Binary
{
    int pixelesNegros;
    BoundedBuffer &BufferGS;
    BoundedBuffer &BufferB;

  public:
    Binary(BoundedBuffer & bufGS, BoundedBuffer & bufB) : pixelesNegros(0), BufferGS(bufGS), BufferB(bufB) {}

  private:
    void main()
    {
        for (;;)
        {
            yield(rand() % 20); // duerma un rato
            BMP img = BufferGS.remove();
            if (img.getTamano() == -1)  break;
            convertToBinary(img, 60);
            cout << "=================================" << endl;
            cout << img.getName() << " binarizada." <<endl;
            cout << "=================================" << endl << endl;
            yield(rand() % 20); // duerma un rato
            img.setPixelesNegros(pixelesNegros);
            BufferB.insert(img);
            //SaveBMP(img);
        }
    }

    /* Funcion encargada de binarizar la imagen.
    Entrada: Estructura con la informacion de la imagen y umbral de binarizacion.
    Salida: imagen binarizada (arreglo con los pixeles de la imagen). */
    void convertToBinary(BMP image, int umbBinary)
    {
        int i, j, contador = 0;
        for (i = image.getAlto() - 1; i >= 0; i--)
        {
            for (j = 0; j < image.getAncho(); j++)
            {
                if (image.getPixelBE(i, j) > umbBinary)
                {
                    image.setPixelBE(i, j, 255);
                    image.setPixelGE(i, j, 255);
                    image.setPixelRE(i, j, 255);
                }
                else
                {
                    image.setPixelBE(i, j, 0);
                    image.setPixelGE(i, j, 0);
                    image.setPixelRE(i, j, 0);
                    pixelesNegros++;
                }
            }
        }
    }
};
#endif
