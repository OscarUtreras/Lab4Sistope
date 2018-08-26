#include <stdlib.h> /* srand, rand */
#include <time.h>
#include "BMP.cpp"
#include "BoundedBuffer.cpp"
#include "ReadImage.cpp"
#include "GrayScale.cpp"
#include "Binary.cpp"
#include "NearlyBlack.cpp"

void uMain::main()
{
	srand(time(NULL));
	BoundedBuffer bufRI(4); // Monitor
	BoundedBuffer bufGS(4); // Monitor
	BoundedBuffer bufB(4); // Monitor
	BoundedBuffer bufNB(4); // Monitor

	//Imagen para parar
	BMP *img = new BMP();
	img->setTamano(-1);

	ReadImage *ri = new ReadImage(bufRI);
	GrayScale *gs = new GrayScale(bufRI, bufGS);
	Binary *b = new Binary(bufGS,bufB);
	NearlyBlack *nb = new NearlyBlack(bufB,bufNB);

	delete ri;
	bufRI.insert(*img);
	delete gs;
	bufGS.insert(*img);
	delete b;
	bufB.insert(*img);
	delete nb;
	/*
	for ( int i = 0; i < NoOfProds; i += 1 )
		delete prods[i];
	for ( int i = 0; i < NoOfCons; i += 1 )
		bufRI.insert( -1 );
	for ( int i = 0; i < NoOfCons; i += 1 )
		delete cons[i];
  */
}
