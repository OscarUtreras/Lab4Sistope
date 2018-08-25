#include "BoundedBuffer.cpp"
#include "BMP.cpp"
#include <iostream>
using namespace std;
#ifndef BINARY_CPP
#define BINARY_CPP
_Task Binary
{
    BoundedBuffer &BufferGS;
    BoundedBuffer &BufferB;

  public:
    Binary(BoundedBuffer & bufGS, BoundedBuffer & bufB) : BufferGS(bufGS), BufferB(bufB) {}

  private:
    void main()
    {
        for (;;)
        {
            yield(rand() % 20); // duerma un rato
            BMP img = BufferGS.remove();
            if (img.getTamano() == -1)  break;
            convertToBinary(img, 60);
            yield(rand() % 20); // duerma un rato
            BufferB.insert(img);
            SaveBMP(img);
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
                    contador++;
                }
            }
        }
        image.setPixelesNegros(contador);
    }

    void SaveBMP(BMP imagen)
    {
        char *filename = (char *)malloc(sizeof(char) * 16);
        sprintf(filename, "out_%d.bmp", imagen.getId());
        FILE *archivo; //Puntero FILE para el archivo de imágen a abrir
        int i, j, k, resto, var, aux_int;
        short int aux_sint;
        //Abrir el archivo de imágen
        archivo = fopen(filename, "wb+");
        if (!archivo)
        {
            //Si la imágen no se encuentra en la ruta dada
            printf("La imágen %s no se pudo crear\n", filename);
            exit(1);
        }
        char bm[2];
        vector<char> aux_cv;
        aux_cv.resize(2);
        aux_cv = imagen.getBm();
        bm[0] = aux_cv[0];
        bm[1] = aux_cv[1];
        //Leer la cabecera de la imagen y almacenarla en la estructura global img
        fseek(archivo, 0, SEEK_SET);
        fwrite(&bm, sizeof(char), 2, archivo);
        aux_int = imagen.getTamano();
        fwrite(&aux_int, sizeof(int), 1, archivo);
        aux_int = imagen.getReservado();
        fwrite(&aux_int, sizeof(int), 1, archivo);
        aux_int = imagen.getOffset();
        fwrite(&aux_int, sizeof(int), 1, archivo);
        aux_int = imagen.getTamanoMetadatos();
        fwrite(&aux_int, sizeof(int), 1, archivo);
        aux_int = imagen.getAlto();
        fwrite(&aux_int, sizeof(int), 1, archivo);
        aux_int = imagen.getAncho();
        fwrite(&aux_int, sizeof(int), 1, archivo);
        aux_sint = imagen.getNumeroPlanos();
        fwrite(&aux_sint, sizeof(short int), 1, archivo);
        aux_sint = imagen.getProfundidadColor();
        fwrite(&aux_sint, sizeof(short int), 1, archivo);
        aux_int = imagen.getTipoCompresion();
        fwrite(&aux_int, sizeof(int), 1, archivo);
        aux_int = imagen.getTamanoEstructura();
        fwrite(&aux_int, sizeof(int), 1, archivo);
        aux_int = imagen.getPxmh();
        fwrite(&aux_int, sizeof(int), 1, archivo);
        aux_int = imagen.getPxmv();
        fwrite(&aux_int, sizeof(int), 1, archivo);
        aux_int = imagen.getColoresUsados();
        fwrite(&aux_int, sizeof(int), 1, archivo);
        aux_int = imagen.getColoresImportantes();
        fwrite(&aux_int, sizeof(int), 1, archivo);
        //*********************************************************************************************************
        //Colocar el cursor en el lugar de lectura especifica
        //*********************************************************************************************************
        fseek(archivo, imagen.getOffset(), SEEK_SET);
        //*********************************************************************************************************
        //Pasar la estrucutra a imagen
        //*********************************************************************************************************
        resto = (imagen.getAncho() * 3) % 4; //Padding (Bytes necesarios para que el Pad row alcance a ser multiplo de 4 Bytes)
        if (resto != 0)
            resto = 4 - resto;
        //Iterar a través de las filas de píxeles, teniendo en cuenta que los datos comienza en la esquina inferior izquierda de la imagen BMP
        int contV = 0;
        char aux_char;
        for (i = imagen.getAlto() - 1; i >= 0; i--)
        {
            for (j = 0; j < imagen.getAncho(); j++)
            {
                //Ecribir los 3 bytes BGR al archivo BMP, en este caso todos se igualan al mismo valor (Valor del pixel en la matriz de la estructura imagen)
                aux_char = imagen.getPixelBE(i, j);
                fwrite(&aux_char, sizeof(char), 1, archivo); //Escribir el Byte Blue del pixel
                aux_char = imagen.getPixelGE(i, j);
                fwrite(&aux_char, sizeof(char), 1, archivo); //Escribir el Byte Green del pixel
                aux_char = imagen.getPixelRE(i, j);
                fwrite(&aux_char, sizeof(char), 1, archivo); //Escribir el Byte Red del pixel
                if (imagen.getProfundidadColor() == 32)
                {
                    aux_char = imagen.getPixelVE(i, j);
                    fwrite(&aux_char, sizeof(char), 1, archivo);
                    contV++; //Escribir el Byte Red del pixel
                }
            }
            //Padding (Bytes necesarios para que el Pad row alcance a ser multiplo de 4 Bytes)
            for (k = 1; k <= resto; k++)
                fwrite(&var, sizeof(char), 1, archivo); //Escribir los pixeles de relleno
        }
        //Cerrrar el archivo
        fclose(archivo);
    }

};
#endif