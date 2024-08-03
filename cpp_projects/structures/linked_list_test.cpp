#include "linked_list.hpp"
#include "../../test/catch.hpp"
#include <sstream>

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
// ============== END OF FILE ==============
