#ifndef	QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

//may need to put other struct here 

struct nodeQ{
	double data;
	nodeQ *next;
};


class queue{
private:
	nodeQ *head;
	bool flag;

public:
	queue();
	~queue();
	void insert(double x, nodeQ *&L);
	bool isEmpty();
	void pop();
	nodeQ *& peek();
	nodeQ*& getHead();
};


#endif