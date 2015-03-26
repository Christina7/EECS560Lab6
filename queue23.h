#ifndef	QUEUE23_H
#define QUEUE23_H

#include <iostream>
using namespace std;

//may need to put other struct here 


struct node23{
	int tag;
	double minSecond;
	double minThird;
	double key;
	node23 *parent;
	node23 *first;
	node23 *second;
	node23 *third;
};


struct nodeQ{
	node23 *data;
	nodeQ *next;
};

class queue23{
private:
	nodeQ *head;
	bool flag;

public:
	queue23();
	~queue23();
	void insert(node23 *&x, nodeQ *&L);
	bool isEmpty();
	void pop();
	nodeQ *& peek();
	nodeQ*& getHead();
};


#endif