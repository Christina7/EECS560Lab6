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


//Insert a node23 into the tree
void tree23::insert(double x, node23 *&L){

	if (isInTree(x, L)){
		cout << "Number already in tree \n";
	}
	else{

		node23 * newLeaf = new node23;
		newLeaf->first = NULL;
		newLeaf->second = NULL;
		newLeaf->third = NULL;
		newLeaf->tag = 1; //is leaf
		newLeaf->minSecond = -1;
		newLeaf->minThird = -1;
		newLeaf->key = x;
		newLeaf->parent = NULL;
		if (L == NULL){ //new tree
			L = newLeaf;
		}
																			//--------------------done for 1 node--------------------
		else{
			if ((L->tag == 1) && (L->parent == NULL)){	//is leaf without parent so only one node23 currently in tree should only be one case
				if (x < L->key){
					L->parent = new node23;
					L->parent->first = new node23;//with x
					L->parent->first->first = NULL;
					L->parent->first->second = NULL;
					L->parent->first->third = NULL;
					L->parent->first->tag = 1; //is leaf
					L->parent->first->minSecond = -1;
					L->parent->first->minThird = -1;
					L->parent->first->key = x;
					L->parent->first->parent = L->parent;
					L->parent->second = L;//

					L->parent->third = NULL;
					L->parent->tag = 0; //is not leaf
					L->parent->minSecond = L->parent->second->key; //find min
					L->parent->minThird = -1;
					L->parent->key = -1;
					L->parent->parent = NULL;

					head = L->parent;
					head->parent = NULL;
				}
				else if (x > L->key){
					L->parent = new node23;
					L->parent->second = new node23;//with x
					L->parent->second->first = NULL;
					L->parent->second->second = NULL;
					L->parent->second->third = NULL;
					L->parent->second->tag = 1; //is leaf
					L->parent->second->minSecond = -1;
					L->parent->second->minThird = -1;
					L->parent->second->key = x;
					L->parent->second->parent = L->parent;
					L->parent->first = L;//

					L->parent->third = NULL;
					L->parent->tag = 0; //is not leaf
					L->parent->minSecond = L->parent->second->key; //find min
					L->parent->minThird = -1;
					L->parent->key = -1;
					L->parent->parent = NULL;
				 
					head = L->parent;
					head->parent = NULL;
				}
				else{
					cout << " Error in inserting second node";
				}
																						//--------------------done for 2 node--------------------
			}
			else if (L->tag == 0){		//general case; more than 2 nodes
				if (x < L->minSecond){			//goes into the first and moves everything over
					if (x == L->first->key){
						cout << "Error in finding a duplicate isInTree";
					}
					else {
						if (L->second->tag == 1){	//at parent
							if (L->third == NULL){		//is 2node
								if (L->parent == NULL){		//is 2node root
									L->third = L->second;
									L->second = L->first;
									L->first = newLeaf;
									newLeaf->parent = L;
									L->minSecond = findMin(L->second);
									L->minThird = findMin(L->third);
								}
							}
							else if (L->third != NULL){	//is 3node
								if (L->parent == NULL) { //is 3node root
									node23 * rootNew = new node23;
									rootNew->parent = NULL;
									rootNew->tag = 0;
									rootNew->first = new node23;//
									rootNew->second = new node23;//
									//rootNew->minSecond = findMin(rootNew->second);//
									rootNew->minThird = -1;//
									rootNew->key = -1;

									rootNew->first->parent = rootNew;
									rootNew->first->tag = 0;
									rootNew->first->key = -1;
									rootNew->first->first = newLeaf;
									rootNew->first->second = L->first;
									rootNew->first->third = NULL;
									rootNew->first->minSecond = findMin(rootNew->first->second);
									rootNew->first->minThird = -1;

									rootNew->second->parent = rootNew;
									rootNew->second->tag = 0;
									rootNew->second->key = -1;
									rootNew->second->first = L->second;
									rootNew->second->second = L->third;
									rootNew->second->third = NULL;
									rootNew->second->minSecond = findMin(rootNew->second->second);
									rootNew->second->minThird = -1;

									rootNew->minSecond = findMin(rootNew->second);
									//rootNew->minThird = findMin(rootNew->third);
									head = rootNew;
									head->parent = NULL;
								}
							}

						}
					}

				}
				else if (x > L->minSecond){		//goes to end 

					if (L->second->tag == 1){	//at parent
						if (L->third == NULL){		//is 2node
							if (L->parent == NULL){		//is 2node root
								L->third = newLeaf;
								newLeaf->parent = L;
								L->minThird = findMin(L->third);
							}
						}
						else if (L->third != NULL){	//is 3node
							if (L->parent == NULL) { //is 3node root
								node23 * rootNew = new node23;
								rootNew->parent = NULL;
								rootNew->tag = 0;
								rootNew->first = new node23;//
								rootNew->second = new node23;//
								//rootNew->minSecond = findMin(rootNew->second);//
								rootNew->minThird = -1;//
								rootNew->key = -1;

								rootNew->first->parent = rootNew;
								rootNew->first->tag = 0;
								rootNew->first->key = -1;
								rootNew->first->first = L->first;
								rootNew->first->second = L->second;
								rootNew->first->third = NULL;
								rootNew->first->minSecond = findMin(rootNew->first->second);
								rootNew->first->minThird = -1;

								rootNew->second->parent = rootNew;
								rootNew->second->tag = 0;
								rootNew->second->key = -1;
								rootNew->second->first = L->third;
								rootNew->second->second = newLeaf;
								rootNew->second->third = NULL;
								rootNew->second->minSecond = findMin(rootNew->second->second);
								rootNew->second->minThird = -1;

								rootNew->minSecond = findMin(rootNew->second);
								head = rootNew;
								head->parent = NULL;
							}
						}
					}
				}
				else{
					cout << "Number already in tree---";		//need to put splitting here
				}
			}															//--------------------done for inserting only 3 node--------------------
		}
	}
}

//finds if node is in tree
bool tree23::isInTree(double x, node23 *&L){
	if (L == NULL){
		return false;
	}
	else{
		if ((L->key == x) || (L->minSecond == x) || (L->minSecond == x)){
			return true;
		}
		else{
			if (L->tag == 0){
				if (x < L->minSecond){
					isInTree(x, L->first);
				}
				else if (x > L->minSecond){
					if (L->minThird != NULL){
						if (x < L->minThird){
							isInTree(x, L->second);
						}
						else{
							isInTree(x, L->third);
						}
					}
					else {
						isInTree(x, L->second);
					}
				}
			}
			else{
				return false;
			}
		}
	}
}

//finds parent for insertion
node23*& tree23::findParent(double x, node23 *&L){
	if (L = NULL){
		return L->parent;
	}
	else{
		if (L->tag == 0){
			if (x < L->minSecond){
				findParent(x, L->first);
			}
			else if (x > L->minSecond){
				if (L->minThird != NULL){
					if (x < L->minThird){
						findParent(x, L->second);
					}
					else{
						findParent(x, L->third);
					}
				}
				else {
					findParent(x, L->second);
				}
			}
		}
	}
}



//returns minimum number for getting minSecond and minThirds
double tree23::findMin(node23 *&L){
	if (L == NULL){
		return -1;
	}
	else if (L->tag == 1){
		return L->key;
	}
	else if (L->tag == 0){
		if (L->first == NULL){
			cout << "first is null look at findMin";
		}
		findMin(L->first);
	}
};

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
void tree23::levelorder(node23 *&L){		//need to adjust for leaves and not leaves
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

