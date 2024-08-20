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

TEST_CASE("Test create_frequency_table() function"){
	// empty vector
	std::vector<std::string> empty_text{};
	std::unordered_map<std::string, int> empty_text_frequency{create_frequency_table(empty_text)};
	REQUIRE(empty_text_frequency.size() == 0);

	// onve-word vector
	std::vector<std::string> one_word_text{"one_word"};
	std::unordered_map<std::string, int> one_word_text_frequency{create_frequency_table(one_word_text)};
	REQUIRE(one_word_text_frequency.size() == 1);
	REQUIRE(one_word_text_frequency.at("one_word") == 1);

	// three unique words vector
	std::vector<std::string> three_words_text{"first", "second", "third"};
	std::unordered_map<std::string, int> three_words_text_frequency{create_frequency_table(three_words_text)};
	REQUIRE(three_words_text_frequency.size() == 3);
	REQUIRE(three_words_text_frequency.at("first") == 1);
	REQUIRE(three_words_text_frequency.at("third") == 1);

	// repeating words vector
	std::vector<std::string> five_words_text{"first","third", "second", "first", "third"};
	std::unordered_map<std::string, int> five_words_text_frequency{create_frequency_table(five_words_text)};
	REQUIRE(five_words_text_frequency.size() == 3);
	REQUIRE(five_words_text_frequency.at("first") == 2);
	REQUIRE(five_words_text_frequency.at("third") == 2);
	REQUIRE(five_words_text_frequency.at("second") == 1);
}
// ============== END OF FILE ==============