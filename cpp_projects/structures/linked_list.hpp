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
#include <initializer_list>

class List{
	public:
		List();

		List(std::initializer_list<int> list);

		List(List const& other);

		List(List&& other);

		~List();

		List& operator=(List const& other);

		List& operator=(List&& other);

		void print(std::ostream& os) const;

		void insert(int v);

		void remove(int idx);

		int size() const;

		bool is_empty() const;

		int at(int idx) const;

	private:
		class Node{
			public:
				int value;
				Node* next;
			};

		// ----- instance variables -----
		Node* first{};
		int _size;

		void _destructor_helper();
		void _constructor_helper(Node* const& node);
		void _set_size(int s);
};


#endif // LINKED_LIST_HPP

// ============== END OF FILE ==============
