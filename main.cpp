#include <stdlib.h> /* srand, rand */
#include <time.h>
#include "BMP.cpp"
#include "BoundedBuffer.cpp"
#include "ReadImage.cpp"
#include "GrayScale.cpp"
#include "Binary.cpp"
#include "NearlyBlack.cpp"
<<<<<<< HEAD
#include "SaveImage.cpp"
=======
#include "SaveBMP.cpp"
>>>>>>> b747ff193e6c3916fe3c2d942362054a6a45fc16

void uMain::main()
{
	srand(time(NULL));
	BoundedBuffer bufRI(4, "Read Image / Gray Scale"); // Monitor
	BoundedBuffer bufGS(4, "Gray Scale / Binary"); // Monitor
	BoundedBuffer bufB(4, "Binary / Nearly Black"); // Monitor
	BoundedBuffer bufNB(4, "Nearly Black / Save Image"); // Monitor

	//Imagen para parar
	BMP *img = new BMP(-1);

	ReadImage *ri = new ReadImage(bufRI);
	GrayScale *gs = new GrayScale(bufRI, bufGS);
	Binary *b = new Binary(bufGS,bufB);
	NearlyBlack *nb = new NearlyBlack(bufB,bufNB);
<<<<<<< HEAD
	SaveImage *si = new SaveImage(bufNB);
=======
	SaveBMP *si = new SaveBMP(bufNB);
>>>>>>> b747ff193e6c3916fe3c2d942362054a6a45fc16

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
	for ( int i = 0; i < NoOfProds; i += 1 )
		delete prods[i];
	for ( int i = 0; i < NoOfCons; i += 1 )
		bufRI.insert( -1 );
	for ( int i = 0; i < NoOfCons; i += 1 )
		delete cons[i];
  */
}
