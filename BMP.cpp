#include <iostream>
using namespace std;
#ifndef BMP_CPP
#define BMP_CPP
class BMP
{
  char bm[2];                 //(2 Bytes) BM (Tipo de archivo)
  int tamano;                 //(4 Bytes) Tamaño del archivo en bytes
  int reservado;              //(4 Bytes) Reservado
  int offset;                 //(4 Bytes) offset, distancia en bytes entre la img y los píxeles
  int tamanoMetadatos;        //(4 Bytes) Tamaño de Metadatos (tamaño de esta estructura = 40)
  int alto;                   //(4 Bytes) Ancho (numero de píxeles horizontales)
  int ancho;                  //(4 Bytes) Alto (numero de pixeles verticales)
  short int numeroPlanos;     //(2 Bytes) Numero de planos de color
  short int profundidadColor; //(2 Bytes) Profundidad de color (debe ser 24 para nuestro caso)
  int tipoCompresion;         //(4 Bytes) Tipo de compresión (Vale 0, ya que el bmp es descomprimido)
  int tamanoEstructura;       //(4 Bytes) Tamaño de la estructura Imagen (Paleta)
  int pxmh;                   //(4 Bytes) Píxeles por metro horizontal
  int pxmv;                   //(4 Bytes) Píxeles por metro vertical
  int coloresUsados;          //(4 Bytes) Cantidad de colores usados
  int coloresImportantes;     //(4 Bytes) Cantidad de colores importantes
  int pixelesNegros;          //Cantidad de pixeles negros luego de la binarizacion
  unsigned char **pixelR;     //Puntero a los pixeles del plano R (Rojo)
  unsigned char **pixelG;     //Puntero a los pixeles del plano G (Verde)
  unsigned char **pixelB;     //Puntero a los pixeles del plano B (Azul)
  unsigned char **pixelV;     //Puntero a los pixeles del plano V
public:
  BMP(){}
  void setTamano(int tamano)
  {
    this->tamano = tamano;
  }
  int getTamano()
  {
    return this->tamano;
  }
  void display()
  {
    cout<<"BM= "<<this->bm<<endl;
    cout<<"Tamano= "<<this->tamano<<endl;
    cout<<"Reservado= "<<this->reservado<<endl;
    cout<<"Offset= "<<this->offset<<endl;
    cout<<"TamanoMetadatos= "<<this->tamanoMetadatos<<endl;
    cout<<"Alto= "<<this->alto<<endl;
    cout<<"Ancho= "<<this->ancho<<endl;
    cout<<"NumeroPlanos= "<<this->numeroPlanos<<endl;
    cout<<"ProfundidadColor= "<<this->profundidadColor<<endl;
    cout<<"TipoCompresion= "<<this->tipoCompresion<<endl;
    cout<<"TamanoEstructura= "<<this->tamanoEstructura<<endl;
    cout<<"Pxmh= "<<this->pxmh<<endl;
    cout<<"Pxmv= "<<this->pxmv<<endl;
    cout<<"ColoresUsados= "<<this->coloresUsados<<endl;
    cout<<"ColoresImportantes= "<<this->coloresImportantes<<endl;
  }
};
#endif
