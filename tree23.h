#ifndef TREE23_H
#define TREE23_H

#include <stdlib.h>
#include <iostream>
#include <fstream>

//#include "queue23.h"      //not yet made

using namespace std;

struct node23{
	int tag;
	double minSecond;
	double minThird;
	double key;
	node23 *parent;
	node23 *first;
	node23 *second;
	node23 *third;
}


class tree23{
private:
	node23 *head;

public:

	tree23();
	~tree23();
	
	void insert(double x, node23 *&L); 
	void remove(double x); 
	void minSwitch(node23 *&L );
	node*& search(double x, node23 *&L);
	void deletemin( node23 *&L);
	void deletemax( node23 *&L);
 	void levelorder(node23 *&L);
	node*& getHead();
	void build(ifstream& file);

};

#endif
