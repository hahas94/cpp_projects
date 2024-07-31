/**
 * linked_list.hpp
 * ---------------
 * Description: 
 * 	Header file containing declarations for the Linked List library. 
 * */

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <string>
#include <iostream>

class List{
	public:
		List();

		void print(std::ostream& os);

		void insert(int v);

	private:
		class Node{
			public:
				int value;
				Node* next;
			};

		Node* first{};
};


#endif // LINKED_LIST_HPP

// ============== END OF FILE ==============
