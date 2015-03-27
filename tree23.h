#ifndef TREE23_H
#define TREE23_H

#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "queue23.h"      //not yet made

using namespace std;


class tree23{
private:
	node23 *head;
	bool needSplit;

public:

	tree23();
	~tree23();
	
	void insert1(double x, node23 *&L);
	void insert2(double x, node23 *&newLeaf, node23 *&L);		//1 root node only    2 is for next node general case
	void insert3(node23 *&oldParent, node23 *&newParent);
	bool isInTree(double x, node23 *&L); 
	node23*& findParent(double x, node23 *&L);
	double findMin(node23 *&L);
	double findMax(node23 *&L);
	void fixMin(node23 *&L);
	void remove(double x);
	void remove2(double x,node23 *&removenode);
	void minSwitch(node23 *&L );
	node23* search(double x, node23 *&L); ///
	void deletemin( node23 *&L);
	void deletemax( node23 *&L);
 	void levelorder(node23 *&L);
	node23*& getHead();
	void build(ifstream& file);

};

#endif
