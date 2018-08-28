#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <string.h> /*strcmp */
#include "BMP.cpp"
#include "BoundedBuffer.cpp"
#include "ReadImage.cpp"
#include "GrayScale.cpp"
#include "Binary.cpp"
#include "NearlyBlack.cpp"
#include "SaveImage.cpp"
/* Función que obtiene los valores de cada parametro ingresado.
Entrada: argc, argv, cantidad de imagenes, umbral de bonarizacion, umbral de clasificacion y bandera (indica si se muestra informacion por pantalla).
Salida: cantidad de imagenes, umbral de bonarizacion, umbral de clasificacion y bandera por referencia. */
int getArguments(int argc, char **argv, int *n_images, int *umbBinary, int *umbClassi, int *flag, int *bufferSize)
{
	int c;
	opterr = 0;
	while ((c = getopt(argc, argv, "c:u:n:B:b")) != -1)
		switch (c)
		{
		case 'c':
			if (strcmp(optarg, "-u") == 0)
			{
				cout << "Tiene que ingresar la cantidad de imagenes luego de -c" << endl;
				return 1;
			}
			sscanf(optarg, "%d", n_images);
			break;
		case 'u':
			if (strcmp(optarg, "-n") == 0)
			{
				cout << "Tiene que ingresar el umbral para binarizar la imagen luego de -u" << endl;
				return 1;
			}
			sscanf(optarg, "%d", umbBinary);
			break;
		case 'n':
			if (strcmp(optarg, "-B") == 0)
			{
				cout << "Tiene que ingresar el umbral para la clasificacion luego de -n" << endl;
				return 1;
			}
			sscanf(optarg, "%d", umbClassi);
			break;
		case 'B':
			if (strcmp(optarg, "-b") == 0)
			{
				cout << "Tiene que ingresar la cantidad de imagenes que soportan los buffers luego de -B" << endl;
				return 1;
			}
			sscanf(optarg, "%d", bufferSize);
			break;
		case 'b':
			*flag = 1;
			break;
		case '?':
			if (optopt == 'c' || optopt == 'B' || optopt == 'u' || optopt == 'n')
				fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
			else if (isprint(optopt))
				fprintf(stderr, "Opcion desconocida '%c'\n", optopt);
			else
				fprintf(stderr, "Opcion con caracter desconocido `\\x%x'.\n", optopt);
			return 1;
		default:
			exit(1);
		}
	return 0;
}

void uMain::main()
{
	srand(time(NULL)); // Inicializardor para los random usados al insertar y sacar del buffer
	int i, n_images = -1, umbBinary = -1, umbClassi = -1, flag = -1, bufferSize = -1;
	int test = getArguments(argc, argv, &n_images, &umbBinary, &umbClassi, &flag, &bufferSize);
	if (argc < 9)
		cout << "Faltan argumentos, por favor ejecute el programa con los argumentos necesarios." << endl;
	else
	{
		if (test == 0)
		{
			BoundedBuffer bufRI(bufferSize, "Read Image / Gray Scale");   // Buffer para ReadImage
			BoundedBuffer bufGS(bufferSize, "Gray Scale / Binary");		 // Buffer para GrayScale
			BoundedBuffer bufB(bufferSize, "Binary / Nearly Black");		 // Buffer para Binary
			BoundedBuffer bufNB(bufferSize, "Nearly Black / Save Image"); // Buffer para NearlyBlack

			//Imagen para parar
			BMP *img = new BMP(-1);

			ReadImage *ri = new ReadImage(bufRI, n_images);
			GrayScale *gs = new GrayScale(bufRI, bufGS);
			Binary *b = new Binary(bufGS, bufB, umbBinary);
			NearlyBlack *nb = new NearlyBlack(bufB, bufNB, umbClassi);
			SaveImage *si = new SaveImage(bufNB,flag);

			delete ri;
			bufRI.insert(*img);
			delete gs;
			bufGS.insert(*img);
			delete b;
			bufB.insert(*img);
			delete nb;
			bufNB.insert(*img);
			delete si;
			/*
			delete bufRI;
			delete bufGS;
			delete bufB;
			delete bufNB;
			*/

		}
		else
			cout << "Ejecute nuevamente con los parametros correctos." << endl;
	}
}
