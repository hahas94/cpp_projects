#include "editor.hpp"
#include "../../test/catch.hpp"
#include <sstream>

// -------------- UNIT TESTS --------------

TEST_CASE("Test print_text() function"){
	// empty vector
	std::vector<std::string> empty_text{};
	std::ostringstream oss{};
	print_text(empty_text, oss);
	REQUIRE(oss.str() == "");
	REQUIRE(empty_text.size() == 0);

	// vector with one word
	std::vector<std::string> one_word_text{"one_word"};
	std::ostringstream oss1{};
	print_text(one_word_text, oss1);
	REQUIRE(oss1.str() == "one_word ");
	REQUIRE(one_word_text.size() == 1);

	// vector with three words
	std::vector<std::string> three_words_text{"first", "second", "third"};
	std::ostringstream oss2{};
	print_text(three_words_text, oss2);
	REQUIRE(oss2.str() == "first second third ");
	REQUIRE(three_words_text.size() == 3);
}
// ============== END OF FILE ==============