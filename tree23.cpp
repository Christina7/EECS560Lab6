#include <iostream>
#include <fstream>
#include "tree23.h"

using namespace std;

tree23::tree23(){
	head = NULL;
	needSplit = false;
}


tree23::~tree23(){
	//will do deletemin till empty 
}


//Insert up to two node23 into the tree after that it is passed to insert2 
void tree23::insert1(double x, node23 *&L){

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

				insert2(x, newLeaf,findParent(x, L));
			}
		}
	}
}
/*
//Insert a node23 into the tree
void tree23::insert2(double x, node23 *&newLeaf, node23 *&L){
	
				if (x < L->minSecond){			//goes into the first and moves everything over
					if (x == L->first->key){
						cout << "Error in finding a duplicate isInTree";
					}
					else {
						if (L->second->tag == 1){	//at parent
							if (L->third == NULL){		//is 2node
								//if (L->parent == NULL){		//is 2node root
									L->third = L->second;
									L->second = L->first;
									L->first = newLeaf;
									newLeaf->parent = L;
									L->minSecond = findMin(L->second);
									L->minThird = findMin(L->third);
								//}
							}
							else if (L->third != NULL){	//is 3node
								//if (L->parent == NULL) { //is 3node root
									node23 * parentNew = new node23;
									parentNew->parent = NULL;///////////////////////////////////////////////////
									parentNew->tag = 0;
									parentNew->first = new node23;//
									parentNew->second = new node23;//
									//parentNew->minSecond = findMin(parentNew->second);//
									parentNew->minThird = -1;//
									parentNew->key = -1;

									parentNew->first->parent = parentNew;
									parentNew->first->tag = 0;
									parentNew->first->key = -1;
									parentNew->first->first = newLeaf;
									parentNew->first->second = L->first;
									parentNew->first->third = NULL;
									parentNew->first->minSecond = findMin(parentNew->first->second);
									parentNew->first->minThird = -1;

									parentNew->second->parent = parentNew;
									parentNew->second->tag = 0;
									parentNew->second->key = -1;
									parentNew->second->first = L->second;
									parentNew->second->second = L->third;
									parentNew->second->third = NULL;
									parentNew->second->minSecond = findMin(parentNew->second->second);
									parentNew->second->minThird = -1;

									parentNew->minSecond = findMin(parentNew->second);
									//parentNew->minThird = findMin(parentNew->third);
									head = parentNew;
									head->parent = NULL;
								//}
							}

						}
					}

				}
				else if (x > L->minSecond){		//goes to end 

					if (L->second->tag == 1){	//at parent
						if (L->third == NULL){		//is 2node
							//if (L->parent == NULL){		//is 2node root
								L->third = newLeaf;
								newLeaf->parent = L;
								L->minThird = findMin(L->third);
							//}
						}
						else if (L->third != NULL){	//is 3node
							if (L->parent == NULL) { //is 3node root
								node23 * parentNew = new node23;
								parentNew->parent = NULL;
								parentNew->tag = 0;
								parentNew->first = new node23;//
								parentNew->second = new node23;//
								//parentNew->minSecond = findMin(parentNew->second);//
								parentNew->minThird = -1;//
								parentNew->key = -1;

								parentNew->first->parent = parentNew;
								parentNew->first->tag = 0;
								parentNew->first->key = -1;
								parentNew->first->first = L->first;
								parentNew->first->second = L->second;
								parentNew->first->third = NULL;
								parentNew->first->minSecond = findMin(parentNew->first->second);
								parentNew->first->minThird = -1;

								parentNew->second->parent = parentNew;
								parentNew->second->tag = 0;
								parentNew->second->key = -1;
								parentNew->second->first = L->third;
								parentNew->second->second = newLeaf;
								parentNew->second->third = NULL;
								parentNew->second->minSecond = findMin(parentNew->second->second);
								parentNew->second->minThird = -1;

								parentNew->minSecond = findMin(parentNew->second);
								head = parentNew;
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
*/

//general case for insertion
void tree23::insert2(double x, node23 *&newLeaf, node23 *&L){

	if (L->second->tag == 1){	//at parent
		if (L->third == NULL){		//is 2node just insert and adjust kids
			if (x < L->first->key){
				L->third = L->second;
				L->second = L->first;
				L->first = newLeaf;
				newLeaf->parent = L;
				L->minSecond = findMin(L->second);
				L->minThird = findMin(L->third);
			}
			else if ((x > L->first->key) && (x < L->second->key)){
				L->third = L->second;
				L->second = newLeaf;
				newLeaf->parent = L;
				L->minSecond = findMin(L->second);
				L->minThird = findMin(L->third);				
				
			}
			else if (x > L->second->key){
				L->third = newLeaf;
				newLeaf->parent = L;
				L->minThird = findMin(L->third);
			}
			/*if (x < L->minSecond){
				L->third = L->second;
				L->second = L->first;
				L->first = newLeaf;
				newLeaf->parent = L;
				L->minSecond = findMin(L->second);
				L->minThird = findMin(L->third);
			}
			else if (x > L->minSecond){
				L->third = newLeaf;
				newLeaf->parent = L;
				L->minThird = findMin(L->third);
			}*/
		}
		else{
			if (L->third != NULL){	//is 3node
				node23 * parentNew = new node23;
				parentNew->parent = NULL;
				parentNew->tag = 0;
				//parentNew->first = new node23;//
				//parentNew->second = new node23;//////////////////////////////////////////////////////////take care of kids
				//parentNew->minSecond = findMin(parentNew->second);//
				parentNew->minThird = -1;//
				parentNew->key = -1;
				parentNew->third = NULL;

				if (x < L->first->key){

					parentNew->second = L->third;
					parentNew->first = L->second;
					parentNew->first->parent = parentNew;
					parentNew->second->parent = parentNew;
					L->third = NULL;
					L->second = L->first;
					L->first = newLeaf;
					newLeaf->parent = L;

					parentNew->minSecond = findMin(parentNew->second);
					L->minSecond = findMin(L->second);
					L->minThird = findMin(L->third);

				}
				else if ((x > L->first->key) && (x < L->second->key)){


					parentNew->second = L->third;
					parentNew->first = L->second;
					parentNew->second->parent = parentNew;
					parentNew->first->parent = parentNew;
					L->third = NULL;
					L->second = newLeaf;
					newLeaf->parent = L;

					parentNew->minSecond = findMin(parentNew->second);
					L->minSecond = findMin(L->second);
					L->minThird = findMin(L->third);

				}
				else if ((x > L->second->key) && (x < L->third->key)){

					parentNew->second = L->third;
					parentNew->second->parent = parentNew;
					parentNew->first = newLeaf;
					L->third = NULL;
					newLeaf->parent = parentNew;

					parentNew->minSecond = findMin(parentNew->second);
					L->minSecond = findMin(L->second);
					L->minThird = findMin(L->third);

				}

				else if (x > L->third->key){

					parentNew->second = newLeaf;
					parentNew->first = L->third;
					L->third = NULL;
					newLeaf->parent = parentNew;
					parentNew->first->parent = parentNew;
					parentNew->minSecond = findMin(parentNew->second);
					L->minSecond = findMin(L->second);
					L->minThird = findMin(L->third);
				}


				insert3(L, parentNew );

			}
		}
	}
}



//putting everything together
void tree23::insert3(node23 *& oldParent, node23 *&newParent){
	if (oldParent->parent == NULL){		//is root
		node23 * newRoot = new node23;		//makes new 
		newRoot->tag = 0;
		newRoot->first = oldParent;
		newRoot->second = newParent;
		newRoot->minThird = -1;
		newRoot->minSecond = findMin(newRoot->second);		//breaks here at 20
		newRoot->key = -1;
		newRoot->third = NULL;
		newRoot->parent = NULL;
		oldParent->parent = newRoot;
		newParent->parent = newRoot;
		head = newRoot;
	
	}
	else{ 
		node23 * conParent = oldParent->parent;
		if (conParent->third == NULL){		//is 2node
			if (conParent->first == oldParent){		//oldparent if first child
				conParent->third = conParent->second;
				conParent->second = newParent;
				newParent->parent = conParent;
				conParent->third->parent = conParent;
				conParent->second->parent = conParent;
				conParent->minSecond = findMin(conParent->second);
				conParent->minThird = findMin(conParent->third);
			}
			else{//is second child
				conParent->third = newParent;
				newParent->parent = conParent;
				conParent->minSecond = findMin(conParent->second);
				conParent->minThird = findMin(conParent->third);
			}
		}
		else{ //is 3node
			node23 * newconParent = new node23;
			newconParent->tag = 0;
			newconParent->key = -1;
			newconParent->third = NULL;

			if (conParent->first == oldParent){
				newconParent->second = conParent->third;
				newconParent->first = conParent->second;
				newconParent->second->parent = newconParent;
				newconParent->first->parent = newconParent;				
				conParent->second = newParent;
				conParent->second->parent = conParent;
				conParent->third = NULL;
				newconParent->minSecond = findMin(newconParent->second);
				newconParent->minThird = findMin(newconParent->third);
				conParent->minSecond = findMin(conParent->second);
				conParent->minThird = findMin(conParent->third);
			}

			else if (conParent->second == oldParent){
				newconParent->second = conParent->third;
				newconParent->first = newParent;
				newconParent->second->parent = newconParent;
				newconParent->first->parent = newconParent;		
				conParent->third = NULL;
				newconParent->minSecond = findMin(newconParent->second);
				newconParent->minThird = findMin(newconParent->third);
				conParent->minSecond = findMin(conParent->second);
				conParent->minThird = findMin(conParent->third);
			}

			else if (conParent->third == oldParent){
				newconParent->second = newParent;
				newconParent->first = conParent->third;
				newconParent->second->parent = newconParent;
				newconParent->first->parent = newconParent;		
				conParent->third = NULL;
				newconParent->minSecond = findMin(newconParent->second);
				newconParent->minThird = findMin(newconParent->third);
				conParent->minSecond = findMin(conParent->second);
				conParent->minThird = findMin(conParent->third);
			}

			insert3(conParent, newconParent);
		}

	}

}




//finds if node is in tree
bool tree23::isInTree(double x, node23 *&L){
	if (L == NULL){
		return false;
	}
	else{
		if ((L->key == x) || (L->minSecond == x) || (L->minThird == x)){
			return true;
		}
		else{
			if (L->tag == 0){
				if (x < L->minSecond){
					isInTree(x, L->first);
				}
				else if (x > L->minSecond){
					if (L->third != NULL){
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
	if ((L == NULL)||(L->tag == 1)){
		return L->parent;
	}
	else{
		if (L->tag == 0){
			if (x < L->minSecond){
				findParent(x, L->first);
			}
			else if (x > L->minSecond){
				if (L->third != NULL){
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
	double value;
	if (L == NULL){
		return -1;
	}
	else if (L->tag == 1){
		value = L->key;
		return value;
	}
	else{ // if (L->tag == 0){
		if (L->first == NULL){
			cout << "first is null look at findMin";
		}
		findMin(L->first);
	}
}

//returns maximum number for removing max
double tree23::findMax(node23 *&L){
	double value;
	if (L == NULL){
		return -1;
	}
	else if (L->tag == 1){
		value = L->key;
		return value;
	}
	else{ // if (L->tag == 0){
		if (L->third == NULL){
			findMax(L->second);
		}
		else{
			findMax(L->third);
		}
		
	}
}


//fixes mins bottom up after remove craziness 
void tree23::fixMin(node23 *&L){
	if ((L->tag == 1) && (L != NULL)){
		L->minSecond = -1;
		L->minThird = -1;
	}
	else if (L->tag == 0){
		fixMin(L->first);
		L->minSecond = findMin(L->second);
		L->minThird = findMin(L->third);
		fixMin(L->second);
		L->minSecond = findMin(L->second);
		L->minThird = findMin(L->third);
		if (L->third != NULL){
			fixMin(L->third);
			L->minSecond = findMin(L->second);
			L->minThird = findMin(L->third);
		}
	}
}



void tree23::remove(double x){

	node23 * removenode = search(x, head);		//finds parent of the node to delete
	if (removenode == NULL){
		cout << "Error number not in tree";
	}
	else{
		remove2(x, removenode);
	}
}

void tree23::remove2(double x, node23 *&removenode){			//if x = -1 works just as if you had regular case but removenode is actual node to be removed versus parent of a leaf
		if ((removenode->parent == NULL) && (removenode->tag == 1)){		//if root is leaf just delete root
			delete head;
			head = NULL;
		}//---------------------------------------------------------------------------------------------------------------------------------- 
		else {		//not root
			node23 * parentnode = removenode->parent;
			if (removenode->third != NULL){		//is 3node
				if (removenode->first->key == x){		//find where the node is and adjust the kids
					delete removenode->first;
					removenode->first = removenode->second;
					removenode->second = removenode->third;
					removenode->first->parent = removenode;
					removenode->second->parent = removenode;
					removenode->third = NULL;
					removenode->minSecond = findMin(removenode->second);
					removenode->minThird = findMin(removenode->third);
				}
				else if ((x == -1) && (removenode == parentnode->first)) {
					delete removenode;
					parentnode->first = parentnode->second;
					parentnode->second = parentnode->third;
					parentnode->first->parent = parentnode;
					parentnode->second->parent = parentnode;
					parentnode->third = NULL;
					parentnode->minSecond = findMin(parentnode->second);
					parentnode->minThird = findMin(parentnode->third);
				}

				else if (removenode->second->key == x){
					delete removenode->second;
					removenode->second = removenode->third;
					removenode->third = NULL;
					removenode->second->parent = removenode;
					removenode->minSecond = findMin(removenode->second);
					removenode->minThird = findMin(removenode->third);
				}
				else if ((x == -1) && (removenode == parentnode->second)){
					delete removenode;
					parentnode->second = parentnode->third;
					parentnode->second->parent = parentnode;
					parentnode->third = NULL;
					parentnode->minSecond = findMin(parentnode->second);
					parentnode->minThird = findMin(parentnode->third);
				}

				else if (removenode->third->key == x){
					delete removenode->third;
					removenode->third = NULL;
					removenode->minSecond = findMin(removenode->second);
					removenode->minThird = findMin(removenode->third);		
				}
				else if ((x == -1) && (removenode == parentnode->third)){
					delete removenode;
					parentnode->third = NULL;
					parentnode->minSecond = findMin(parentnode->second);
					parentnode->minThird = findMin(parentnode->third);
				}
			}
			else{		//is 2node interior							
				if (removenode->parent == NULL){	//is root 
					node23 * temp = removenode;

					if (removenode->first->key == x){
						head = removenode->second;
						delete removenode->first;
						delete temp;
					}
					else if (removenode->second->key == x){
						head = removenode->first;
						delete removenode->second;
						delete temp;
					}

				}
				else if ((x == -1) && (parentnode->parent == NULL)){
					node23 * temp = parentnode;
					if (removenode == parentnode->first) {
						head = parentnode->second;
						delete removenode;
						delete temp;
					}
					else {
						head = parentnode->first;
						delete removenode;
						delete temp;
					}
				}

				else if (x != -1){			//not root
					node23 * auntSue;
					node23 * grandpa = removenode->parent;
					if ((grandpa->first->third != NULL) && (removenode == grandpa->second)){
						auntSue = grandpa->first;
						if (removenode->second->key == x){
							removenode->second = removenode->first;
							removenode->second->parent = removenode;
						}

						removenode->first = auntSue->third;
						removenode->first->parent = removenode;

						auntSue->minSecond = findMin(auntSue->second);
						auntSue->minThird = findMin(auntSue->third);
					}
					else if ((grandpa->second->third != NULL) && ((removenode == grandpa->first)||(removenode == grandpa->third))){
						auntSue = grandpa->second;
						if (removenode == grandpa->first){
							if (removenode->first->key == x){
								removenode->first = removenode->second;
								removenode->first->parent = removenode;
							}
							removenode->second = auntSue->first;
							auntSue->first = auntSue->second;
							auntSue->second = auntSue->third;
							removenode->second->parent = removenode;
							auntSue->first->parent = auntSue;
							auntSue->second->parent = auntSue;
							auntSue->third = NULL;
							auntSue->minThird = -1;
						}
						else{
							if (removenode->second->key == x){
								removenode->second = removenode->first;
								removenode->second->parent = removenode;
							}

							removenode->first = auntSue->third;
							removenode->first->parent = removenode;
							auntSue->third = NULL;
							auntSue->minThird = -1;
						}
					}
					else if ((grandpa->third->third != NULL) && (removenode == grandpa->second)){
						auntSue = grandpa->third;
						if (removenode->first->key == x){
							removenode->first = removenode->second;
							removenode->first->parent = removenode;
						}
						removenode->second = auntSue->first;
						auntSue->first = auntSue->second;
						auntSue->second = auntSue->third;
						removenode->second->parent = removenode;
						auntSue->first->parent = auntSue;
						auntSue->second->parent = auntSue;
						auntSue->third = NULL;
						auntSue->minThird = -1;
					} /// -----------------------------------------------------------------------------------------------------------------------------------------
					else{
						node23 * sibling;
						if (removenode->first->key == x) {		//last kid
							sibling = removenode->second;
						}
						else {
							sibling = removenode->first;
						}
						if (removenode == grandpa->first) {
							auntSue = grandpa->second;

							auntSue->third = auntSue->second;
							auntSue->second = auntSue->first;
							auntSue->first = sibling;
							auntSue->third->parent = auntSue;
							auntSue->second->parent = auntSue;
							auntSue->first->parent = auntSue;
						}
		
						else if (removenode == grandpa->second) {	
							auntSue = grandpa->first;		
							if (auntSue->third == NULL) {
								auntSue->third = sibling;
								auntSue->third->parent = auntSue;
							}
							else {
								auntSue = grandpa->third;

								auntSue->third = auntSue->second;
								auntSue->second = auntSue->first;
								auntSue->first = sibling;
								auntSue->third->parent = auntSue;
								auntSue->second->parent = auntSue;
								auntSue->first->parent = auntSue;
							}
						}
						
						else {
							auntSue = grandpa->second;
							auntSue->third = sibling;
							auntSue->third->parent = auntSue;
						}

						if (removenode->first->key == x) {
							delete removenode->first;
						}
						else if (removenode->second->key == x) {
							delete removenode->second;
						}

						remove2(-1, removenode);

					}
				}
				else if(x == -1){
					node23* grandpa = parentnode->parent;
					node23* auntSue;
					if ((grandpa->first->third != NULL) && (grandpa->second == parentnode)){
						auntSue = grandpa->first;
						if (removenode == parentnode->second) {
							parentnode->second = parentnode->first;
							parentnode->second->parent = parentnode;
						}

						parentnode->first = auntSue->third;
						parentnode->first->parent = parentnode;

						auntSue->third = NULL;
						auntSue->minThird = findMin(auntSue->third);
					}
					else if ((grandpa->second->third != NULL) && (grandpa->first == parentnode || grandpa->third == parentnode)) {
						auntSue = grandpa->second;
						if (parentnode == grandpa->first) {
							if (removenode == parentnode->first) {
								parentnode->first = parentnode->second;
								parentnode->first->parent = parentnode;
							}

							parentnode->second = auntSue->first;
							auntSue->first = auntSue->second;
							auntSue->second = auntSue->third;
							parentnode->second->parent = parentnode;
							auntSue->first->parent = auntSue;
							auntSue->second->parent = auntSue;
							
							auntSue->third = NULL;
							auntSue->minThird = -1;
						}
						
						else {
							if (removenode == parentnode->second) {
								parentnode->second = parentnode->first;
								parentnode->second->parent = parentnode;
							}
							parentnode->first = auntSue->third;
							parentnode->first->parent = parentnode;
							auntSue->third = NULL;
							auntSue->minThird = -1;
						}
					}
					else if ((grandpa->third != NULL) && (grandpa->second == parentnode)){
						auntSue = grandpa->third;
						
						if (removenode == parentnode->first) {
							parentnode->first = parentnode->second;
							parentnode->first->parent = parentnode;
						}

						parentnode->second = auntSue->first;
						auntSue->first = auntSue->second;
						auntSue->second = auntSue->third;
						parentnode->second->parent = parentnode;
						auntSue->first->parent = auntSue;
						auntSue->second->parent = auntSue;

						auntSue->third = NULL;
						auntSue->minThird = -1;
					}
					else {
						node23* sibling;
						
						if (parentnode->first == removenode) {
							sibling = parentnode->second;
						}
						else {
							sibling = parentnode->first;
						}

						
						if (parentnode == grandpa->first) {
							auntSue = grandpa->second;

							auntSue->third = auntSue->second;
							auntSue->second = auntSue->first;
							auntSue->first = sibling;
							auntSue->third->parent = auntSue;
							auntSue->second->parent = auntSue;
							auntSue->first->parent = auntSue;

						}
						
						else if (parentnode == grandpa->second) {
							auntSue = grandpa->first;
							if (auntSue->third == NULL) {
								auntSue->third = sibling;
								auntSue->third->parent = auntSue;
							}
							else {
								auntSue = grandpa->third;

								auntSue->third = auntSue->second;
								auntSue->second = auntSue->first;
								auntSue->first = sibling;
								auntSue->third->parent = auntSue;
								auntSue->second->parent = auntSue;
								auntSue->first->parent = auntSue;
							}
						}
						else {
							auntSue = grandpa->second;
							auntSue->third = sibling;
							auntSue->third->parent = sibling;
						}

						
						delete removenode;
						remove2(-1,parentnode);
					}
				}
			}

		fixMin(head);	
	}
}
	


//may not need
void tree23::minSwitch(node23 *&L){

}

//finds node to be removed
node23* tree23::search(double x, node23 *&L){
	node23 * notHere = NULL;
	if (L == NULL){
		return L;
	}
	else{
		if (L->key == x){
			if (L->parent != NULL){
				return L->parent;
			}
			else {
				return L;
			}
		}
		else {
			if (L->tag == 0){
				if (x < L->minSecond){
					search(x, L->first);
				}
				else if (x > L->minSecond){
					if (L->third != NULL){
						if (x < L->minThird){
							search(x, L->second);
						}
						else{
							search(x, L->third);
						}
					}
					else {
						search(x, L->second);
					}
				}
				else if (x == L->minSecond){
					search(x, L->second);
				}
			}
			else{
				return notHere;
			}
		}
	}




}

//deletes minimum node23
void tree23::deletemin(node23 *&L){
	
}

//deletes maximum node23
void tree23::deletemax(node23 *&L){

}

//Prints tree in level order
void tree23::levelorder(node23 *&L){		//need to adjust for leaves and not leaves
	queue23 q;
	node23 * temp = L;
	if (L == NULL){
		cout << "Empty tree";
	}
	else{
		q.insert(temp, q.getHead());

		while (!q.isEmpty()){
			if (q.peek()->data->tag == 0){
				cout << q.peek()->data->minSecond << " " << q.peek()->data->minThird << " ";
			}
			else{
				cout << q.peek()->data->key << " ";
			}
			
			
			//(q.peek()->data-tag == 0)
			//if  ((q.peek()->data == head)||((q.peek()->data->tag == 0) && ((q.peek()->data->parent->third == q.peek()->data) || ((q.peek()->data->parent->second == q.peek()->data)&&(q.peek()->data->parent->third == NULL))))){
			if (isHeadLastNode(q.peek()->data)){
				cout << endl;
			}
						
			q.pop();
			if (temp->first != NULL){
				q.insert(temp->first, q.getHead());
			}
			if (temp->second != NULL){
				q.insert(temp->second, q.getHead());
			}
			if (temp->third != NULL){
				q.insert(temp->third, q.getHead());

			}
			if (q.peek() != NULL){
				temp = q.peek()->data;

			}
		}
	}
	
}

bool tree23::isHeadLastNode(node23 *&L){
	node23 * temp = head;
	if (head == NULL){
		return false;
	}
	else if (L == head){
		return true;
	}
	else{
		if (temp->third == NULL){
			temp = temp->second;
		}
		else{
			temp = temp->third;
		}
		while (temp->minSecond != -1){

			if ((L->tag == 0) && (L->minSecond == temp->minSecond) && (temp->minThird == -1)){
				return true;
			}
			else if ((L->tag == 0) && (L->minThird == temp->minThird)&&(L->minThird != -1)){
				return true;
			}
			else{
				if (temp->third == NULL){
					temp = temp->second;
				}
				else{
					temp = temp->third;
				}
			}
		
		}
		return false;
	}
}


//returns head
node23*& tree23::getHead(){
	return head;
}


void tree23::build(ifstream& file){
	double item;
	while (file >> item){//read from file and add each number to head
		insert1(item, head);
	}
}

