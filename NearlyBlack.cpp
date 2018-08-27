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
		        //cout << "Inserto con clasificacion en: " << img.getNearlyBlack() << endl;
            BufferNB.insert(img);
        }
    }
    /* Funcion encargada clasificar la imagen binarizada.
    Entrada: Estructura con la informacion de la imagen y umbral de clasificacion.
    Salida: 1 si es nearly black o 0 si no es nearly black. */

    void classifyNearlyBlack(BMP image, int umbCla)
    {
        //cout << "=============================" << endl;
        //cout << "Alto: " << image.getAlto() << endl;
        //cout << "Ancho: " << image.getAncho() << endl;
        //cout << "P Negros: " << image.getPixelesNegros() << endl;
        float result = ((float)image.getPixelesNegros() / ((float)image.getAlto() * (float)image.getAncho())) * 100;
		    //cout << "Resultado: " << result << endl;
        //cout << "=============================" << endl;
        cout << "=================================" << endl;
        if (result > umbCla)
        {
          cout << image.getName()<< " es nearly black."  << endl;
          cout << "=================================" << endl << endl;
          return image.setNearlyBlack(1);
        }
        cout <<image.getName()<< " no es nearly black." << endl;
        cout << "=================================" << endl << endl;
        return image.setNearlyBlack(0);
    }
};
#endif
