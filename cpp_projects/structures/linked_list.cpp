/**
 * linked_list.cpp
 * ---------------
 * Description: 
 * 	
 * 	----- Linked List Library -----
 * 
 * 	The task is to write a library that will be used by other programmers.
 * 	The library should implement an object for representing a singly linked  
 * 	list data structure, where the list is always sorted. Functionality such
 * 	as insert, remove, iterations, deep-copy constructor, copy assignment,
 * 	move constructor, move assignment and destructors are included. 
 * 	Part of the task is to handle dynamic memory and pointers, without 
 * 	any memory leak.
 * 
 * 	A linked list data structure consists of a number of nodes, where each
 * 	node holds some data and a pointer to the next node in the list. As such
 * 	the list only keeps track of the first node.
 * 	
 * 	The code must be developed using TDD - Test-Driven Development. The Catch2 
 * 	library is used for the tesing part.
 * 
 * 	*/

#include "linked_list.hpp"

List::List()
	: first{nullptr}
	{}

void List::print(std::ostream& os){
	os << "[";
	Node* tmp{first};
	while(tmp != nullptr){
		os << tmp->value;
		if(tmp->next != nullptr){
			os << ", ";
		}
		tmp = tmp->next;
	} 

	os << "]";
}

void List::insert(int v){
	Node* tmp{new Node{v, nullptr}};

	// first node
	if(first == nullptr || v <= first->value){
		tmp->next = first;
		first = tmp;
	}
	else{
		Node* curr{first};

		while(curr->next != nullptr){
			if(v <= (curr->next)->value){
				tmp->next = curr->next;
				curr->next = tmp;
				break;
			}

			curr = curr->next;

			if(curr->next == nullptr){
				// reaching last element
				curr->next = tmp;
				break;
			}
		}
	}
}

// ============== END OF FILE ==============
