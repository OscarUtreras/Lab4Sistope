#include <uC++.h>
#include <iostream>
#include <queue>
#include "BMP.cpp"
using namespace std;
#ifndef BOUNDEDBUFFER_CPP
#define BOUNDEDBUFFER_CPP
_Monitor BoundedBuffer
{
	uCondition full, empty;
	int front, back, count, buf_size;
	queue<BMP> elements;

  public:
	BoundedBuffer(int buf_size) : front(0), back(0), count(0), buf_size(buf_size)
	{
	}
	_Nomutex int query() { return count; }
	void insert(BMP elem)
	{
		if (count == buf_size)
			empty.wait();
		elements.push(elem);
		count += 1;
		full.signal();
		cout << "Inserto " << elem.getTamano() << endl;
	}
	BMP remove()
	{
		if (count == 0)
			full.wait();
		BMP img = elements.front();
		elements.pop();
		count -= 1;
		empty.signal();
		cout << "Remove " << img.getTamano() << endl;
		return img;
	}
};
#endif
