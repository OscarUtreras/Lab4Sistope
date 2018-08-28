#include "BoundedBuffer.cpp"
#include "BMP.cpp"
#include <iostream>
using namespace std;
#ifndef READIMAGE_CPP
#define READIMAGE_CPP
_Task ReadImage
{
  BoundedBuffer &Buffer;
  int n_images;

public:
  ReadImage(BoundedBuffer & buf, int n_images) : Buffer(buf), n_images(n_images) {}

private:
  void main()
  {
    cout << "Cantidad de imagenes: " << n_images << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    char *filename = (char *)malloc(sizeof(char) * 16);
    for (int i = 1; i <= n_images; i += 1)
    {
      yield(rand() % 20); // duerma un rato
      sprintf(filename, "imagen_%d.bmp", i);
      BMP img = this->LoadBMP(filename);
      cout << "=================================" << endl;
      cout << img.getName() << " leida." << endl;
      cout << "=================================" << endl
           << endl;
      img.setId(i);
      Buffer.insert(img);
    }
  }
  /* Función encargada cargar la imagen BMP.
    Entrada: nombre de la imagen.
    Salida: imagen cargada en un objeto BMP */
  BMP LoadBMP(char *filename)
  {
    BMP imagen;
    FILE *archivo; //Puntero FILE para el archivo de imágen a abrir
    int i, j, k, resto, aux_int;
    unsigned char R, B, G, V, var, aux_uchar;
    short int aux_sint;
    char bm[2];
    vector<char> aux_cv;
    aux_cv.resize(2);
    //Abrir el archivo de imágen
    archivo = fopen(filename, "rb+");
    if (!archivo)
    {
      //Si la imágen no se encuentra en la ruta dada
      printf("La imagen %s no se encontro\n", filename);
      exit(1);
    }
    imagen.setName(string(filename));
    //Leer la cabecera de la imagen y almacenarla en la estructura global img
    fseek(archivo, 0, SEEK_SET);
    fread(&bm, sizeof(char), 2, archivo);
    aux_cv[0] = bm[0];
    aux_cv[1] = bm[1];
    imagen.setBm(aux_cv);
    fread(&aux_int, sizeof(int), 1, archivo);
    imagen.setTamano(aux_int);
    fread(&aux_int, sizeof(int), 1, archivo);
    imagen.setReservado(aux_int);
    fread(&aux_int, sizeof(int), 1, archivo);
    imagen.setOffset(aux_int);
    fread(&aux_int, sizeof(int), 1, archivo);
    imagen.setTamanoMetadatos(aux_int);
    fread(&aux_int, sizeof(int), 1, archivo);
    imagen.setAlto(aux_int);
    fread(&aux_int, sizeof(int), 1, archivo);
    imagen.setAncho(aux_int);
    fread(&aux_sint, sizeof(short int), 1, archivo);
    imagen.setNumeroPlanos(aux_sint);
    fread(&aux_sint, sizeof(short int), 1, archivo);
    imagen.setProfundidadColor(aux_sint);
    fread(&aux_int, sizeof(int), 1, archivo);
    imagen.setTipoCompresion(aux_int);
    fread(&aux_int, sizeof(int), 1, archivo);
    imagen.setTamanoEstructura(aux_int);
    fread(&aux_int, sizeof(int), 1, archivo);
    imagen.setPxmh(aux_int);
    fread(&aux_int, sizeof(int), 1, archivo);
    imagen.setPxmv(aux_int);
    fread(&aux_int, sizeof(int), 1, archivo);
    imagen.setColoresUsados(aux_int);
    fread(&aux_int, sizeof(int), 1, archivo);
    imagen.setColoresImportantes(aux_int);
    //Validar ciertos datos de la cabecera de la imágen
    if (bm[0] != 'B' || bm[1] != 'M')
    {
      printf("La imagen debe ser un bitmap.\n");
      exit(1);
    }
    //*********************************************************************************************************
    //Colocar el cursor en el byte (
    //*********************************************************************************************************
    fseek(archivo, imagen.getOffset(), SEEK_SET);
    //*********************************************************************************************************
    //Reservar memoria para el arreglo que tendra los planos RGB de la imagen
    //*********************************************************************************************************
    imagen.setMemory();
    //*********************************************************************************************************
    //Padding
    //*********************************************************************************************************
    resto = (imagen.getAncho() * 3) % 4;
    if (resto != 0)
      resto = 4 - resto;
    //*********************************************************************************************************
    //Pasar la imágen a la  matriz especfica  R / G / B
    //*********************************************************************************************************
    //Iterar a través de las filas de píxeles, teniendo en cuenta que los datos comienza en la esquina inferior izquierda de la imagen BMP
    int contV = 0;
    for (i = imagen.getAlto() - 1; i >= 0; i--)
    {
      for (j = 0; j < imagen.getAncho(); j++)
      {
        fread(&B, sizeof(char), 1, archivo); //Byte Blue del pixel
        fread(&G, sizeof(char), 1, archivo); //Byte Green del pixel
        fread(&R, sizeof(char), 1, archivo); //Byte Red del pixel
        //cout << "Profundidad Color: "<< imagen.getProfundidadColor()<<endl;
        if (imagen.getProfundidadColor() == 32)
        {
          fread(&V, sizeof(char), 1, archivo); //Byte V del pixel
          imagen.setPixelVE(i, j, V);
          contV++;
        }
        imagen.setPixelRE(i, j, R);
        imagen.setPixelGE(i, j, G);
        imagen.setPixelBE(i, j, B);
      }
      for (k = 1; k <= resto; k++)
        fread(&var, sizeof(char), 1, archivo); //Leer los pixeles de relleno (Padding)
    }
    //Cerrrar el archivo
    fclose(archivo);
    return imagen;
  }
};
#endif
