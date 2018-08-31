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
    int umbral;

  public:
    NearlyBlack(BoundedBuffer & bufB, BoundedBuffer & bufNB, int umbral) : BufferB(bufB), BufferNB(bufNB), umbral(umbral) {}

  private:
    void main()
    {
        for (;;)
        {
            yield(rand() % 20); // duerma un rato
            BMP img = BufferB.remove();
            if (img.getTamano() == -1)
                break;
            yield(rand() % 20); // duerma un rato
            img.setNearlyBlack(classifyNearlyBlack(img, umbral));
            BufferNB.insert(img);
        }
    }
    /* Funcion encargada clasificar la imagen binarizada.
    Entrada: Estructura con la informacion de la imagen y umbral de clasificacion.
    Salida: 1 si es nearly black o 0 si no es nearly black. */

    int classifyNearlyBlack(BMP image, int umbCla)
    {
        float result = ((float)image.getPixelesNegros() / ((float)image.getAlto() * (float)image.getAncho())) * 100;
        cout << "=================================" << endl;
        if (result > umbCla)
        {
            cout << image.getName() << " es nearly black." << endl;
            cout << "=================================" << endl
                 << endl;
            return 1;
        }
        cout << image.getName() << " no es nearly black." << endl;
        cout << "=================================" << endl
             << endl;
        return 0;
    }
};
#endif
