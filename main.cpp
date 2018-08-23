#include "BMP.cpp"
#include "BoundedBuffer.cpp"
#include "ReadImage.cpp"
void uMain::main()
{
  srand (time(NULL));
	BoundedBuffer buf(4); // Monitor
  ReadImage *ri = new ReadImage( buf );
  delete ri;
  /*
	for ( int i = 0; i < NoOfProds; i += 1 )
		delete prods[i];
	for ( int i = 0; i < NoOfCons; i += 1 )
		buf.insert( -1 );
	for ( int i = 0; i < NoOfCons; i += 1 )
		delete cons[i];
  */
}
