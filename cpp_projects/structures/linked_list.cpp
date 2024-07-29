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
	while(tmp){
		os << tmp->value;
		if(tmp->next){
			os << ", ";
		}
		tmp = tmp->next;
	} 

	os << "]";
}

// ============== END OF FILE ==============
