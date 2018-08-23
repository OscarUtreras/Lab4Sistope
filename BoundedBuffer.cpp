#include <uC++.h>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <vector>
#include "BMP.cpp"
using namespace std;
#ifndef BOUNDEDBUFFER_CPP
#define BOUNDEDBUFFER_CPP
_Monitor BoundedBuffer {
		uCondition full, empty;
		int front, back, count, buf_size;
		vector<BMP> elements;
	public:
		BoundedBuffer(int buf_size) : front(0), back(0), count(0), buf_size(buf_size)
		{
			elements.resize(buf_size);
		}
		_Nomutex int query() { return count; }
		void insert(BMP elem) {

			if (count == buf_size) empty.wait();
			elements[back] = elem;
			back = (back+1)% buf_size;
			count += 1;
			full.signal();
			cout<<"Inserto"<<endl;
		}
		BMP remove() {
			if (count == 0) full.wait();
			BMP elem = elements[front];
			front = (front+1)%buf_size;
			count -= 1;
			empty.signal();
			cout<<"Remove"<<endl;
			return elem;
		}
};
#endif
