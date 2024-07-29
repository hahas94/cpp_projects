/**
 * linked_list.hpp
 * ---------------
 * Description: 
 * 	Header file containing declarations for the Linked List library. 
 * */

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

class List{
	public:
		List();

	private:
		class Node{
			int value;
			Node* next;
		};

		Node* first{};
};


#endif // LINKED_LIST_HPP

// ============== END OF FILE ==============
