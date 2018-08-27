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
<<<<<<< HEAD
		        //cout << "Inserto con clasificacion en: " << img.getNearlyBlack() << endl;
=======
            img.setNearlyBlack(classifyNearlyBlack(img, 60));
		    cout << "Inserto con clasificacion en: " << img.getNearlyBlack() << endl;
>>>>>>> b747ff193e6c3916fe3c2d942362054a6a45fc16
            BufferNB.insert(img);
        }
    }
    /* Funcion encargada clasificar la imagen binarizada.
    Entrada: Estructura con la informacion de la imagen y umbral de clasificacion.
    Salida: 1 si es nearly black o 0 si no es nearly black. */

    int classifyNearlyBlack(BMP image, int umbCla)
    {
<<<<<<< HEAD
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
=======
        float result = ((float)image.getPixelesNegros() / ((float)image.getAlto() * (float)image.getAncho())) * 100;
        if (result > umbCla)
            return 1;
        return 0;
>>>>>>> b747ff193e6c3916fe3c2d942362054a6a45fc16
    }
};
#endif
