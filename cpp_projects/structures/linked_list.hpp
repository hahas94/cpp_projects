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

		void print(std::ostream& os) const;

		void insert(int v);

		void remove_index(int idx);

		int size() const;

		bool is_empty() const;

	private:
		class Node{
			public:
				int value;
				Node* next;
			};

		// ----- instance variables -----
		Node* first{};
		int _size;
};


#endif // LINKED_LIST_HPP

// ============== END OF FILE ==============
