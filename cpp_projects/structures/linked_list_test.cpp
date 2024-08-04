#include "linked_list.hpp"
#include "../../test/catch.hpp"
#include <sstream>

// helper function to test move constructor/assignment
List get_list(int mode = 0){
		List list;
		if(mode == 0){
			list.insert(1);
			list.insert(2);
		}
		return list;
}

TEST_CASE("Test insert method"){
	List list;
	std::ostringstream oss{};
	
	// first node
	list.insert(2);
	
	// new first node
	list.insert(0);

	// between two nodes
	list.insert(1);

	// last nodes
	list.insert(3);

	// equal nodes
	list.insert(0);
	list.insert(1);
	list.insert(3);

	list.print(oss);
	REQUIRE(oss.str() == "[0, 0, 1, 1, 2, 3, 3]");

	// insert in sorted order
	List list2;
	std::ostringstream oss2{};
	list2.insert(0);
	list2.insert(1);
	list2.insert(2);
	list2.print(oss2);
	REQUIRE(oss2.str() == "[0, 1, 2]");

	// insert in reverse sorted order
	List list3;
	std::ostringstream oss3{};
	list3.insert(2);
	list3.insert(1);
	list3.insert(0);
	list3.print(oss3);
	REQUIRE(oss3.str() == "[0, 1, 2]");
}

TEST_CASE("Test size method"){
	List list;
	std::ostringstream oss{};

	REQUIRE(list.size() == 0);
	
	// first node
	list.insert(7);
	REQUIRE(list.size() == 1);
	
	// new first node
	list.insert(6);
	REQUIRE(list.size() == 2);

	// between two nodes
	list.insert(6);
	REQUIRE(list.size() == 3);

	// last nodes
	list.insert(5);
	REQUIRE(list.size() == 4);

	list.print(oss);
	REQUIRE(oss.str() == "[5, 6, 6, 7]");
}

TEST_CASE("Test is_empty method"){
	List list;

	REQUIRE(list.is_empty());
	
	// first node
	list.insert(7);
	REQUIRE(list.size() == 1);
	REQUIRE_FALSE(list.is_empty());
}

TEST_CASE("Test remove method"){
	List list;
	std::ostringstream oss{};
	
	list.insert(2);
	list.insert(0);
	list.insert(1);
	list.insert(3);
	list.insert(4);

	// try remove node at illegal index
	list.remove(-1);
	REQUIRE(list.size() == 5);

	// try remove node at illegal index
	list.remove(11);
	REQUIRE(list.size() == 5);

	// remove first node
	list.remove(0);
	REQUIRE(list.size() == 4);

	// remove node between two nodes
	list.remove(1);
	REQUIRE(list.size() == 3);

	// remove last node
	list.remove(2);
	
	// make list empty
	list.remove(0);
	list.remove(0);
	REQUIRE(list.size() == 0);
	REQUIRE(list.is_empty());

	// try remove from empty list
	list.remove(0);
	list.print(oss);
	REQUIRE(oss.str() == "[]");
	REQUIRE(list.size() == 0);	
	REQUIRE(list.is_empty());
}

TEST_CASE("Test at method"){
	List list;

	// test invalid indices
	REQUIRE_THROWS_AS(list.at(0), std::out_of_range);
	REQUIRE_THROWS_AS(list.at(-1), std::out_of_range);
	REQUIRE_THROWS_AS(list.at(10), std::out_of_range);
	
	// first node
	list.insert(5);
	list.insert(3);
	list.insert(9);
	list.insert(7);

	// test all existing positions
	REQUIRE(list.at(0) == 3);
	REQUIRE(list.at(1) == 5);
	REQUIRE(list.at(2) == 7);
	REQUIRE(list.at(3) == 9);

	// test error message
	REQUIRE_THROWS_WITH(list.at(11), "Index out of range.");
}

TEST_CASE("Test copy construcor"){
	std::ostringstream oss1{};
	std::ostringstream oss2{};

	// test copying empty list 
	List list1;
	List copy1{list1};
	REQUIRE(list1.size() == copy1.size());

	// changing copy does not affect original
	copy1.insert(1);
	REQUIRE(copy1.size() == 1);
	REQUIRE(list1.size() == 0);

	// changing original does not affect copy
	list1.insert(2);
	list1.insert(0);
	REQUIRE(list1.size() == 2);
	REQUIRE(copy1.size() == 1);
	REQUIRE(list1.at(0) == 0);
	REQUIRE(copy1.at(0) == 1);

	// test copying from filled list
	List list2;
	list2.insert(3);
	list2.insert(4);
	List copy2{list2};

	// initially both lists are identical
	REQUIRE(list2.size() == copy2.size());
	REQUIRE(list2.at(0) + list2.at(1) == copy2.at(0) + copy2.at(1));

	// changing them does not affect each other
	list2.remove(0);
	copy2.insert(7);
	list2.print(oss1);
	copy2.print(oss2);
	REQUIRE(oss1.str() == "[4]");
	REQUIRE(oss2.str() == "[3, 4, 7]");
}

TEST_CASE("Test copy assignment"){
	// test copy of empty lists
	// ** create two empty lists, copy one to the other, add/remove elements to the 
	// copy and other, they should be different
	std::ostringstream oss1{};
	std::ostringstream oss_copy1{};
	List list1;
	List copy1;
	copy1 = list1;
	REQUIRE(list1.size() == copy1.size());
	copy1.insert(1);
	copy1.insert(1);
	copy1.insert(2);
	list1.insert(3);
	REQUIRE(list1.size() == 1);
	REQUIRE(copy1.size() == 3);
	list1.print(oss1);
	copy1.print(oss_copy1);
	REQUIRE(oss1.str() == "[3]");
	REQUIRE(oss_copy1.str() == "[1, 1, 2]");

	// test copy of filled to empty list
	// the copy must become empty
	List list2;
	List copy2;
	copy2.insert(2);
	copy2.insert(3);
	copy2 = list2;
	REQUIRE(list2.size() == copy2.size());
	REQUIRE(list2.size() == 0);
	
	// test copy of empty to filled list
	// the copy must become filled
	List list3;
	List copy3;
	list3.insert(2);
	list3.insert(3);
	copy3 = list3;
	REQUIRE(list3.size() == copy3.size());
	REQUIRE(list3.at(0) + list3.at(1) ==  copy3.at(0) + copy3.at(1));

	// test copy of filled lists
	// the content of the copy and other must be identical
	std::ostringstream oss4{};
	std::ostringstream oss_copy4{};
	List list4;
	List copy4;
	list4.insert(2);
	list4.insert(7);
	list4.insert(3);
	list4.insert(5);
	copy4.insert(9);
	copy4 = list4;
	REQUIRE(list4.size() == copy4.size());
	list4.print(oss4);
	copy4.print(oss_copy4);
	REQUIRE(oss4.str() == "[2, 3, 5, 7]");
	REQUIRE(oss_copy4.str() == "[2, 3, 5, 7]");
	list4.insert(0);
	copy4.insert(9);
	REQUIRE_FALSE(list4.at(4) == copy4.at(4));
}

TEST_CASE("Test move constructor and assignment"){
	// test constructing by moving empty list
	List list1{get_list(1)};
	REQUIRE(list1.size() == 0);
	
	// test constructing by moving filled list
	List list2{get_list()};
	REQUIRE(list2.size() == 2);

	// test assigning empty list by moving empty list
	List list3;
	list3 = get_list(1);
	REQUIRE(list3.size() == 0);

	// test assigning empty list by moving filled list
	List list4;
	list4 = get_list();
	REQUIRE(list4.size() == 2);

	// test assigning filled list by moving empty list
	List list5;
	list5.insert(0);
	list5 = get_list(1);
	REQUIRE(list5.size() == 0);

	// test assigning filled list by moving filled list
	List list6;
	list6.insert(0);
	list6 = get_list();
	REQUIRE(list6.size() == 2);
}
// ============== END OF FILE ==============
