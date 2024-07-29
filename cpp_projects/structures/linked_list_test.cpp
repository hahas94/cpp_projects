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



// ============== END OF FILE ==============
