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

/**
 * @brief Initializing an empty linked list.
 * 
 */
List::List()
	: first{nullptr}, _size{0}
	{}

/**
 * @brief Destructing the list, i.e. removing all nodes.
 * 
 */
List::~List(){
	_destructor_helper();
}

/**
 * @brief Printing the linked list.
 * 
 * Example: [1, 2, 3]
 * 
 * @param os: An output stream to write to, typically std::cout.
 */
void List::print(std::ostream& os) const{
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

/**
 * @brief Inserting a new value while keeping the list sorted.
 * 
 * @param v: integer value to be inserted.
 */
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

	_size++;
}

/**
 * @brief Returning number of elements in the list.
 * 
 */
int List::size() const{
	return _size;
}

/**
 * @brief Checking whether the list is empty.
 * 
 */
bool List::is_empty() const{
	return _size == 0;
}

/**
 * @brief Remove an element by index while keeping the list sorted.
 * 
 * If the index is out of range, then nothing happens.
 * 
 * @param idx: index to value to be removed.
 */
void List::remove(int idx){
	if(idx <= _size-1 && idx >= 0 && _size > 0){
		if(idx == 0){
			Node* tmp{first};
			first = tmp->next;
			delete tmp;
			_size--;
		}
		else{
			int i{0};
			Node* prev{first};
			while(i < idx-1){
				i++;
				prev = prev->next;
			}
			Node* tmp{prev->next};
			prev->next = tmp->next;
			delete tmp;
			_size--;
		}
	}
}

void List::_destructor_helper(){
	if(_size > 0){
		remove(0);
		_destructor_helper();
	}
	else{
		delete first;
	}
}

// ============== END OF FILE ==============
