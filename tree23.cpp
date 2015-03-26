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
		if (L->third == NULL){		//is 2node
			if (x < L->minSecond){
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
			}
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
					L->third = NULL;
					L->second = L->first;
					L->first = newLeaf;
					newLeaf->parent = L;

					parentNew->minSecond = findMin(parentNew->second);
					L->minSecond = findMin(L->second);
					L->minThird = findMin(L->third);


					/*
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
					//head = parentNew;
					//head->parent = NULL;

					*/
				}
				else if ((x > L->first->key) && (x < L->second->key)){


					parentNew->second = L->third;
					parentNew->first = L->second;
					L->third = NULL;
					L->second = newLeaf;
					newLeaf->parent = L;

					parentNew->minSecond = findMin(parentNew->second);
					L->minSecond = findMin(L->second);
					L->minThird = findMin(L->third);

					/*
					parentNew->first->parent = parentNew;
					parentNew->first->tag = 0;
					parentNew->first->key = -1;
					parentNew->first->first = L->first;
					parentNew->first->second = newLeaf;
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
					//head = parentNew;
					//head->parent = NULL;

					*/

				}
				else if ((x > L->second->key) && (x < L->third->key)){

					parentNew->second = L->third;
					parentNew->first = newLeaf;
					L->third = NULL;
					newLeaf->parent = parentNew;

					parentNew->minSecond = findMin(parentNew->second);
					L->minSecond = findMin(L->second);
					L->minThird = findMin(L->third);

					/*
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
					parentNew->second->first = newLeaf;
					parentNew->second->second = L->third;
					parentNew->second->third = NULL;
					parentNew->second->minSecond = findMin(parentNew->second->second);
					parentNew->second->minThird = -1;

					parentNew->minSecond = findMin(parentNew->second);
					//head = parentNew;
					//head->parent = NULL;

					*/

				}

				else if (x > L->third->key){

					parentNew->second = newLeaf;
					parentNew->first = L->third;
					L->third = NULL;
					newLeaf->parent = parentNew;

					parentNew->minSecond = findMin(parentNew->second);
					L->minSecond = findMin(L->second);
					L->minThird = findMin(L->third);

					/*
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
					//head = parentNew;
					//head->parent = NULL;

					*/
				}


				insert3(L, parentNew );

			}
		}
	}
}



//putting everything together
void tree23::insert3(node23 *& oldParent, node23 *&newParent){
	if (oldParent->parent == NULL){		//is root
		node23 * newRoot = new node23;
		newRoot->tag = 0;
		newRoot->first = oldParent;
		newRoot->second = newParent;
		newRoot->minThird = -1;
		newRoot->minSecond = findMin(newRoot->second);		//breaks here at 20
		newRoot->key = -1;
		newRoot->third = NULL;
		newRoot->parent = NULL;
		
		newParent->parent = newRoot;
		head = newRoot;
	
	}
	else{ 
		node23 * conParent = oldParent->parent;
		if (conParent->third == NULL){		//is 2node
			if (conParent->first == oldParent){
				conParent->third = conParent->second;
				conParent->second = newParent;
				newParent->parent = conParent;
				conParent->minSecond = findMin(conParent->second);
				conParent->minThird = findMin(conParent->third);
			}
			else{//is second child
				conParent->third = newParent;
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
				conParent->second = newParent;
				conParent->third = NULL;
				newconParent->minSecond = findMin(newconParent->second);
				newconParent->minThird = findMin(newconParent->third);
				conParent->minSecond = findMin(conParent->second);
				conParent->minThird = findMin(conParent->third);
			}

			else if (conParent->second == oldParent){
				newconParent->second = conParent->third;
				newconParent->first = newParent;
				//conParent->second = newParent;
				conParent->third = NULL;
				newconParent->minSecond = findMin(newconParent->second);
				newconParent->minThird = findMin(newconParent->third);
				conParent->minSecond = findMin(conParent->second);
				conParent->minThird = findMin(conParent->third);
			}

			else if (conParent->third == oldParent){
				newconParent->second = newParent;
				newconParent->first = conParent->third;
				//conParent->second = newParent;
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



void tree23::remove(double x){
	
	/*
	node23 * check = search(x, head);
	
	if (check == NULL){
		cout << "Error number not in tree";
	}
	else{
		if ((check->parent == NULL) && (check->tag == 1)){
			delete head;
			head = NULL;
		}
		else if (check->tag == 0){
			if (check->third != NULL){		//is 3node
				if (check->first->key == x){
					delete check->first;
					check->first = check->second;
					check->second = check->third;
					check->third = NULL;
					check->minSecond = findMin(check->second);
					check->minThird = findMin(check->third);
				}
				else if (check->second->key == x){
					delete check->second;
					check->second = check->third;
					check->third = NULL;
					check->minSecond = findMin(check->second);
					check->minThird = findMin(check->third);
				}
				else if (check->third->key == x){
					delete check->third;
					check->third = NULL;
					check->minSecond = findMin(check->second);
					check->minThird = findMin(check->third);
				}
			}
			else{		//is 2node interior
				if (check->parent == NULL){	//is root
					node23 * temp = check;

					if (check->first->key == x){
						head = check->second;
						delete check->first;
						delete temp;
					}
					else if (check->first->key == x){
						head = check->first;
						delete check->second;
						delete temp;
					}

				}
				else{			//not root
					node23 * auntSue;
					node23 * grandpa = check->parent;
					if ((grandpa->first->third != NULL) && (check == grandpa->second)){
						auntSue = grandpa->first;
						if (check->second->key == x){
							check->second = check->first;
						}

						check->first = auntSue->third;

						auntSue->minSecond = findMin(auntSue->second);
						auntSue->minThird = findMin(auntSue->third);
					}
					else if ((grandpa->second->third != NULL) && ((check == grandpa->first)||(check == grandpa->third))){
						auntSue = grandpa->second;
						if (check == grandpa->first){
							if (check->first->key == x){
								check->first = check->second;
							}
							check->second = auntSue->first;
							auntSue->first = auntSue->second;
							auntSue->second = auntSue->third;
							auntSue->third == NULL;
							auntSue->minThird = findMin(auntSue->third);
						}
						else{
							if (check->second->key == x){
								check->second = check->first;
							}

							check->first = auntSue->third;
							auntSue->third = NULL;
							auntSue->minThird = findMin(auntSue->third);
						}
					}
					else if ((grandpa->third->third != NULL) && (check == grandpa->second)){
						auntSue = grandpa->third;
						if (check->first->key == x){
							check->first = check->second;
						}
						check->second = auntSue->first;
						auntSue->first = auntSue->second;
						auntSue->second = auntSue->third;
						auntSue->third = NULL;
						auntSue->minThird = -1;
					} /// -----------------------------------------------------------------------------------------------------------------------------------------
					else{
						node23 * sibling;
						// sibling is the last surviving child of the parent
						if (check->first->key == x) {
							sibling = check->second;
						}
						else {
							sibling = check->first;
						}

						// uncle is to the right
						if (check == grandpa->first) {
							auntSue = grandpa->second;

							auntSue->third = auntSue->second;
							auntSue->second = auntSue->first;
							auntSue->first = sibling;
						}
						// uncle is to the right or left
						else if (check == grandpa->second) {
							auntSue = grandpa->first;		
							if (auntSue->third == NULL) {
								auntSue->third = sibling;
							}
							else {
								auntSue = grandpa->third;

								auntSue->third = auntSue->second;
								auntSue->second = auntSue->first;
								auntSue->first = sibling;
							}
						}
						// uncle is to the left
						else {
							auntSue = grandpa->second;
							auntSue->third = sibling;
						}

						// delete the node, remove the childless parent
						delete nodeToDeletePtr;
						remove(check);

					}
				}
			}

			// updateminst(head)
			
		}



	}
	
	
	*/
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
	//node23 *temp[800000];	// RISK DIDN'T DO CHECKS TO MAKE SURE IT DOESN'T EXCEED ARRAY SIZE
	//int i = 0;
	//int curr = 0;
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
			q.pop();
			if (temp->first != NULL){
				q.insert(temp->first, q.getHead());
				//q.insert(L->first->minThird, q.getHead());
				//temp[i] = L->first;
				//i++;
			}
			if (temp->second != NULL){
				q.insert(temp->second, q.getHead());
				//q.insert(L->second->minThird, q.getHead());
				//temp[i] = L->second;
				//i++;
			}
			if (temp->third != NULL){
				q.insert(temp->third, q.getHead());
				//q.insert(L->third->minThird, q.getHead());
				//temp[i] = L->third;
				//i++;
			}
			if (q.peek() != NULL){
				temp = q.peek()->data;
				//L = temp[curr]; //q.peek()->data;
				//curr++;
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

