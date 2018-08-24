#include <stdlib.h> /* srand, rand */
#include <time.h>
#include "BMP.cpp"
#include "BoundedBuffer.cpp"
#include "ReadImage.cpp"
#include "GrayScale.cpp"
void uMain::main()
{
	srand(time(NULL));
	BoundedBuffer buf(4); // Monitor
	BMP *img = new BMP();
	img->setTamano(-1);
	ReadImage *ri = new ReadImage(buf);
	GrayScale *gs = new GrayScale(buf);
	delete ri;
	buf.insert(*img);
	delete gs;
	/*
	for ( int i = 0; i < NoOfProds; i += 1 )
		delete prods[i];
	for ( int i = 0; i < NoOfCons; i += 1 )
		buf.insert( -1 );
	for ( int i = 0; i < NoOfCons; i += 1 )
		delete cons[i];
  */
}
