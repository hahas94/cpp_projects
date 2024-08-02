#include "linked_list.hpp"
#include "../../test/catch.hpp"
#include <sstream>

TEST_CASE("Empty list"){
	List list;
}

TEST_CASE("Test empty print"){
	List list;
	std::ostringstream oss{};
	list.print(oss);
	REQUIRE(oss.str() == "[]");
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



// ============== END OF FILE ==============
