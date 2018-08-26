#include "BoundedBuffer.cpp"
#include "BMP.cpp"
#include <iostream>
using namespace std;
#ifndef NEARLYBLACK_CPP
#define NEARLYBLACK_CPP
_Task NearlyBlack
{
    BoundedBuffer &BufferB;
    BoundedBuffer &BufferNB;

  public:
    NearlyBlack(BoundedBuffer &bufB, BoundedBuffer &bufNB) : BufferB(bufB), BufferNB(bufNB) {}

  private:
    void main()
    {
        for (;;)
        {
            yield(rand() % 20); // duerma un rato
            BMP img = BufferB.remove();
            if (img.getTamano() == -1)  break;
            yield(rand() % 20); // duerma un rato
            img.setNearlyBlack(classifyNearlyBlack(img, 60));
		    cout << "Inserto con clasificacion en: " << img.getNearlyBlack() << endl;
            BufferNB.insert(img);
        }
    }
    /* Funcion encargada clasificar la imagen binarizada.
    Entrada: Estructura con la informacion de la imagen y umbral de clasificacion.
    Salida: 1 si es nearly black o 0 si no es nearly black. */

    int classifyNearlyBlack(BMP image, int umbCla)
    {
        float result = ((float)image.getPixelesNegros() / ((float)image.getAlto() * (float)image.getAncho())) * 100;
        if (result > umbCla)
            return 1;
        return 0;
    }
};
#endif