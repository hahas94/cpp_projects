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

TEST_CASE("Test sort_table_by_keys() function"){
	// empty vector
	std::vector<std::string> empty_text{};
	std::unordered_map<std::string, int> empty_text_frequency{create_frequency_table(empty_text)};
	std::vector<std::pair<std::string, int>> sorted_vector{sort_table_by_keys(empty_text_frequency)};
	REQUIRE(sorted_vector.size() == 0);

	// onve-word vector
	std::vector<std::string> one_word_text{"one_word"};
	std::unordered_map<std::string, int> one_word_text_frequency{create_frequency_table(one_word_text)};
	std::vector<std::pair<std::string, int>> sorted_vector1{sort_table_by_keys(one_word_text_frequency)};
	REQUIRE(sorted_vector1.size() == 1);
	REQUIRE(sorted_vector1.at(0).first == "one_word");
	REQUIRE(sorted_vector1.at(0).second == 1);
	REQUIRE(one_word_text_frequency.size() == 1);
	REQUIRE(one_word_text_frequency.at("one_word") == 1);

	// // three unique words vector
	std::vector<std::string> three_words_text{"first", "second", "third"};
	std::unordered_map<std::string, int> three_words_text_frequency{create_frequency_table(three_words_text)};
	std::vector<std::pair<std::string, int>> sorted_vector3{sort_table_by_keys(three_words_text_frequency)};
	REQUIRE(sorted_vector3.size() == 3);
	REQUIRE(sorted_vector3.at(0).first == "first");
	REQUIRE(sorted_vector3.at(2).second == 1);

	// // repeating words vector
	std::vector<std::string> five_words_text{"first","third", "second", "first", "third"};
	std::unordered_map<std::string, int> five_words_text_frequency{create_frequency_table(five_words_text)};
	std::vector<std::pair<std::string, int>> sorted_vector5{sort_table_by_keys(five_words_text_frequency)};
	REQUIRE(sorted_vector5.size() == 3);
	REQUIRE(sorted_vector5.at(0).first == "first");
	REQUIRE(sorted_vector5.at(0).second == 2);
	REQUIRE(sorted_vector5.at(1).first == "second");
	REQUIRE(sorted_vector5.at(1).second == 1);
	REQUIRE(sorted_vector5.at(2).first == "third");
	REQUIRE(sorted_vector5.at(2).second == 2);
}

TEST_CASE("Test sort_table_by_values() function"){
	// empty vector
	std::vector<std::string> empty_text{};
	std::unordered_map<std::string, int> empty_text_frequency{create_frequency_table(empty_text)};
	std::vector<std::pair<std::string, int>> sorted_vector{sort_table_by_values(empty_text_frequency)};
	REQUIRE(sorted_vector.size() == 0);

	// onve-word vector
	std::vector<std::string> one_word_text{"one_word"};
	std::unordered_map<std::string, int> one_word_text_frequency{create_frequency_table(one_word_text)};
	std::vector<std::pair<std::string, int>> sorted_vector1{sort_table_by_values(one_word_text_frequency)};
	REQUIRE(sorted_vector1.size() == 1);
	REQUIRE(sorted_vector1.at(0).first == "one_word");
	REQUIRE(sorted_vector1.at(0).second == 1);
	REQUIRE(one_word_text_frequency.size() == 1);
	REQUIRE(one_word_text_frequency.at("one_word") == 1);

	// // three unique words vector
	std::vector<std::string> three_words_text{"first", "second", "third"};
	std::unordered_map<std::string, int> three_words_text_frequency{create_frequency_table(three_words_text)};
	std::vector<std::pair<std::string, int>> sorted_vector3{sort_table_by_values(three_words_text_frequency)};
	REQUIRE(sorted_vector3.size() == 3);
	REQUIRE(sorted_vector3.at(0).first == "third");
	REQUIRE(sorted_vector3.at(2).second == 1);

	// // repeating words vector
	std::vector<std::string> five_words_text{"first","third", "second", "first", "third"};
	std::unordered_map<std::string, int> five_words_text_frequency{create_frequency_table(five_words_text)};
	std::vector<std::pair<std::string, int>> sorted_vector5{sort_table_by_values(five_words_text_frequency)};
	REQUIRE(sorted_vector5.size() == 3);
	REQUIRE(sorted_vector5.at(0).first == "third");
	REQUIRE(sorted_vector5.at(0).second == 2);
	REQUIRE(sorted_vector5.at(1).first == "first");
	REQUIRE(sorted_vector5.at(1).second == 2);
	REQUIRE(sorted_vector5.at(2).first == "second");
	REQUIRE(sorted_vector5.at(2).second == 1);
}

// ============== END OF FILE ==============