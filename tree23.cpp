#include <iostream>
#include <fstream>
#include "tree23.h"
using namespace std;

tree23::tree23(){
	head = NULL;
}


tree23::~tree23(){
	//will do deletemin till empty 
}



void tree23::insert(double x, node23 *&L){

}


void tree23::remove(double x){

}


void tree23::minSwitch(node23 *&L){

}

//finds node to be removed
node23*& tree23::search(double x, node23 *&L){
	return head;//not done 
}

//deletes minimum node23
void tree23::deletemin(node23 *&L){

}

//deletes maximum node23
void tree23::deletemax(node23 *&L){

}

//Prints tree in level order
void tree23::levelorder(node23 *&L){
	queue q;
	node23 *temp[800000];	// RISK DIDN'T DO CHECKS TO MAKE SURE IT DOESN'T EXCEED ARRAY SIZE
	int i = 0;
	int curr = 0;
	if (L == NULL){
		cout << "Empty tree";
	}
	else{
		q.insert(L->minSecond, q.getHead());
		q.insert(L->minThird, q.getHead());
		while (!q.isEmpty()){
			cout << q.peek()->data << " ";
			q.pop();
			if (L->first != NULL){
				q.insert(L->first->minSecond, q.getHead());
				q.insert(L->first->minThird, q.getHead());
				temp[i] = L->first;
				i++;
			}
			if (L->second != NULL){
				q.insert(L->second->minSecond, q.getHead());
				q.insert(L->second->minThird, q.getHead());
				temp[i] = L->second;
				i++;
			}
			if (L->third != NULL){
				q.insert(L->third->minSecond, q.getHead());
				q.insert(L->third->minThird, q.getHead());
				temp[i] = L->third;
				i++;
			}
			if (q.peek() != NULL){
				L = temp[curr]; //q.peek()->data;
				curr++;
			}
		}
	}

}

//returns head
node23*& tree23::getHead(){
	return head;
}


void tree23::build(ifstream& file){

}

