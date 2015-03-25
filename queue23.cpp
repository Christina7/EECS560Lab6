#include <iostream>
#include "queue23.h"
using namespace std;

queue::queue(){
	head = NULL;
	flag = false;
}

queue::~queue(){
	nodeQ *temp = head;
	while (temp != NULL){
		nodeQ *temp2 = temp->next;
		delete temp;
		temp = temp2;
	}
	head = NULL;
	temp = NULL;
}

//adds nodeQ to end of queue if it is not already in the queue
void queue::insert(double x, nodeQ *&L){
	if (L == NULL){	//if current nodeQ is NULL adds new nodeQ with data
		L = new nodeQ;
		L->data = x;
		L->next = NULL;
	}
	else{
		
		if (L->data == x){	//if current nodeQ is not null and is the number being inserted 
			cout << "Number already in queue \n";
		}
		else{	//if current nodeQ is not null, last nodeQ with data, and not number being inserted, then adds new nodeQ with data
			if (L->next == NULL){
				L->next = new nodeQ;
				L->next->next = NULL;
				L->next->data = x;
			}
			else{	// current nodeQ is not last nodeQ and does not contain the number being inserted, then move on to next nodeQ recursively
				insert(x, L->next);
			}
		}
	}
}

//checks if queue is empty
bool queue::isEmpty(){
	if (head == NULL){
		return true;
	}
	else{
		return false;
	}
}

//removes nodeQ from queue if there
void queue::pop(){
	if (head == NULL){
		//cout << "Number not in queue \n";
	}
	else{
		nodeQ *temp = head->next;
		delete head;
		head = temp;

	}

}

//prints current head
nodeQ *& queue::peek(){
	if (head == NULL){
		//cout << "Empty queue \n";
		return head;
	}
	else{
		return head;
	}
}

//returns head
nodeQ*& queue::getHead(){
	return head;
}