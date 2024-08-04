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
 * @brief Initializing a linked list with default values of any length.
 * 
 * @param list: a number of default values to initialize list with.
 */
List::List(std::initializer_list<int> list)
	: first{nullptr}, _size{0}
	{
		for(int el : list){
			insert(el);
		}
	}


/**
 * @brief Copy constructor.
 * 
 * A new list is created by making a deep copy of an existing list. 
 * The copy and original are unrelated, that's change in one of them 
 * does not affect the other.
 * 
 * @param other: Constant reference to the existing list.
 * 
 */
List::List(List const& other)
	: first{nullptr}, _size{0}
	{	
		if(other.first != nullptr){
			_constructor_helper(other.first);
		}
	}

/**
 * @brief Move constructor.
 * 
 * Creating a list by moving memory from another list to it. The 
 * other list is temporary and will be removed.
 * 
 * @param other: Reference to reference to the temporary list.
 * 
 */
List::List(List&& other)
	: first{other.first}, _size{other.size()}
	{
		other.first = nullptr;
		other._set_size(0);
	}

/**
 * @brief Destructing the list, i.e. removing all nodes.
 * 
 */
List::~List(){
	_destructor_helper();
	delete first;
}

/**
 * @brief Copy assignment.
 * 
 * An existing list is set equal to another list by making a deep copy of it. 
 * The copy and original are unrelated, that's change in one of them 
 * does not affect the other.
 * 
 * @param other: Constant reference to the list to be copied.
 * @return *this: the list itself. 
 * 
 */
List& List::operator=(List const& other){
	// first remove all nodes in current list
	_destructor_helper();

	// then for each node in other, make a deep copy
	if(other.first != nullptr){
		_constructor_helper(other.first);
	}
	return *this;
}

/**
 * @brief Move assignment.
 * 
 * An existing list is set equal to a temporary list by moving the 
 * temporary list memory to the current list. 
 * 
 * @param other: Reference to reference to the temporary list.
 * @return *this: the list itself. 
 * 
 */
List& List::operator=(List&& other){
	// remove old content
	_destructor_helper();

	// move content from other
	first = other.first;
	_set_size(other.size());

	// prepare other for destruction
	other.first = nullptr;
	other._set_size(0);

	return *this;
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

		while(curr != nullptr){
			if(curr->next == nullptr){
				// reaching end, insert as last element
				curr->next = tmp;
				break;
			}
			else if(v <= (curr->next)->value){
				// insert between current and next node
				tmp->next = curr->next;
				curr->next = tmp;
				break;
			}
			else{
				// continue searching for correct position
				curr = curr->next;
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

/**
 * @brief Retrieve element at position `idx`.
 * 
 * If the index is out of range, throws std::out_of_range exception.
 * 
 * @param idx: index to value to be retrieved.
 * @throws: std::out_of_range exception
 * @return: element at index
 */
int List::at(int idx) const{
	if(idx > _size-1 || idx < 0 || (idx == _size)){
		throw std::out_of_range("Index out of range.");
	}
	else {
		int i{0};
		Node* node{first};
		while(i < idx){
			i++;
			node = node->next;
		}
		return node->value;
	}
}

// ---------- PRIVATE METHODS ----------
// Recursively remove all nodes of the list.
void List::_destructor_helper(){
	if(_size > 0){
		remove(0);
		_destructor_helper();
	}
}

// Recursively insert all nodes of a list.
void List::_constructor_helper(Node* const& node){
	insert(node->value);
	if (node->next != nullptr){
		_constructor_helper(node->next);
	}
}

// update size of list
void List::_set_size(int s){
	_size = s;
}

// ============== END OF FILE ==============
