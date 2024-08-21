#include "editor.hpp"
#include "../../test/catch.hpp"
#include <sstream>

// -------------- UNIT TESTS --------------

TEST_CASE("Test print_text() function"){
	// empty vector
	std::vector<std::string> empty_text{};
	std::ostringstream oss{};
	print_text(empty_text, oss);
	REQUIRE(oss.str() == "\n");
	REQUIRE(empty_text.size() == 0);

	// vector with one word
	std::vector<std::string> one_word_text{"one_word"};
	std::ostringstream oss1{};
	print_text(one_word_text, oss1);
	REQUIRE(oss1.str() == "one_word \n");
	REQUIRE(one_word_text.size() == 1);

	// vector with three words
	std::vector<std::string> three_words_text{"first", "second", "third"};
	std::ostringstream oss2{};
	print_text(three_words_text, oss2);
	REQUIRE(oss2.str() == "first second third \n");
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

TEST_CASE("Test print_table() function"){
	// empty vector
	std::vector<std::string> empty_text{};
	std::unordered_map<std::string, int> empty_text_frequency{create_frequency_table(empty_text)};
	std::ostringstream oss{};
	print_table(empty_text_frequency, oss);
	REQUIRE(oss.str() == "");

	// onve-word vector
	std::vector<std::string> one_word_text{"one_word"};
	std::unordered_map<std::string, int> one_word_text_frequency{create_frequency_table(one_word_text)};
	std::ostringstream oss1{};
	print_table(one_word_text_frequency, oss1);
	REQUIRE(oss1.str() == "one_word 1\n");

	// // three unique words vector
	std::vector<std::string> three_words_text{"first", "second", "third"};
	std::unordered_map<std::string, int> three_words_text_frequency{create_frequency_table(three_words_text)};
	std::ostringstream oss3{};
	print_table(three_words_text_frequency, oss3);
	REQUIRE(oss3.str() == "first  1\nsecond 1\nthird  1\n");	
}

TEST_CASE("Test print_frequency() function"){
	// empty vector
	std::vector<std::string> empty_text{};
	std::unordered_map<std::string, int> empty_text_frequency{create_frequency_table(empty_text)};
	std::ostringstream oss{};
	print_frequency(empty_text_frequency, oss);
	REQUIRE(oss.str() == "");

	// onve-word vector
	std::vector<std::string> one_word_text{"one_word"};
	std::unordered_map<std::string, int> one_word_text_frequency{create_frequency_table(one_word_text)};
	std::ostringstream oss1{};
	print_frequency(one_word_text_frequency, oss1);
	REQUIRE(oss1.str() == "one_word 1\n");

	// // three unique words vector
	std::vector<std::string> three_words_text{"first", "second", "third"};
	std::unordered_map<std::string, int> three_words_text_frequency{create_frequency_table(three_words_text)};
	std::ostringstream oss3{};
	print_frequency(three_words_text_frequency, oss3);
	REQUIRE(oss3.str() == " third 1\nsecond 1\n first 1\n");	
}

TEST_CASE("Test split_string() function"){
	// empty string, should return two empty strings
	std::string s1{""};
	std::pair<std::string, std::string> empty_res1{split_string(s1, '=')};
	std::pair<std::string, std::string> empty_res2{split_string(s1, '+')};
	REQUIRE(empty_res1.first == "");
	REQUIRE(empty_res1.second == "");
	REQUIRE(empty_res2.first == "");
	REQUIRE(empty_res2.second == "");

	// only right part available
	std::string s2{"--print"};
	std::pair<std::string, std::string> res2{split_string(s2, '=')};
	REQUIRE(res2.first == "--print");
	REQUIRE(res2.second == "");

	// only left part available
	std::string s3{"--=print"};
	std::pair<std::string, std::string> res3{split_string(s3, '=')};
	REQUIRE(res3.first == "--");
	REQUIRE(res3.second == "print");

	// both left and right parts are available
	std::string s4{"--remove=word"};
	std::pair<std::string, std::string> res4{split_string(s4, '=')};
	REQUIRE(res4.first == "--remove");
	REQUIRE(res4.second == "word");

	// get both flag and parameters
	std::string s5{"--substitute=word+WORD"};
	std::pair<std::string, std::string> res5{split_string(s5, '=')};
	std::pair<std::string, std::string> res5_params{split_string(res5.second, '+')};
	REQUIRE(res5.first == "--substitute");
	REQUIRE(res5.second == "word+WORD");
	REQUIRE(res5_params.first == "word");
	REQUIRE(res5_params.second == "WORD");
}

TEST_CASE("Test is_argument_valid() function"){
	// --print
	std::string s1{"--print"};
	REQUIRE(is_argument_valid(s1));
	s1 = "--print=";
	REQUIRE_FALSE(is_argument_valid(s1));
	s1 = "--print+";
	REQUIRE_FALSE(is_argument_valid(s1));
	s1 = "--print=w1+w2";
	REQUIRE_FALSE(is_argument_valid(s1));	

	// --table
	std::string s2{"--table"};
	REQUIRE(is_argument_valid(s2));
	s2 = "--table=";
	REQUIRE_FALSE(is_argument_valid(s2));
	s2 = "--table+";
	REQUIRE_FALSE(is_argument_valid(s2));
	s2 = "--table=w1+w2";
	REQUIRE_FALSE(is_argument_valid(s2));	

	// --frequency
	std::string s3{"--frequency"};
	REQUIRE(is_argument_valid(s3));
	s3 = "--frequency=";
	REQUIRE_FALSE(is_argument_valid(s3));
	s3 = "--frequency+";
	REQUIRE_FALSE(is_argument_valid(s3));
	s3 = "--frequency=w1+w2";
	REQUIRE_FALSE(is_argument_valid(s3));	

	// --remove
	std::string s4{"--remove=w"};
	REQUIRE(is_argument_valid(s4));
	s4 = "--remove=C++";
	REQUIRE(is_argument_valid(s4));
	s4 = "--remove=";
	REQUIRE_FALSE(is_argument_valid(s4));
	s4 = "--remove";
	REQUIRE_FALSE(is_argument_valid(s4));
	s4 = "--remove=w1+w2";
	REQUIRE(is_argument_valid(s4));
	s4 = "--remove=+";
	REQUIRE(is_argument_valid(s4));

	// --sustitute
	std::string s5{"--substitute=w1+w2"};
	REQUIRE(is_argument_valid(s5));
	s5 = "--substitute";
	REQUIRE_FALSE(is_argument_valid(s5));
	s5 = "--substitute=";
	REQUIRE_FALSE(is_argument_valid(s5));
	s5 = "--substitute=w1";
	REQUIRE_FALSE(is_argument_valid(s5));
	s5 = "--substitute=w1+";
	REQUIRE_FALSE(is_argument_valid(s5));
	s5 = "--substitute=+";
	REQUIRE_FALSE(is_argument_valid(s5));

	// non-existing flags
	std::string s6{""};
	REQUIRE_FALSE(is_argument_valid(s6));
	s6 = "-";
	REQUIRE_FALSE(is_argument_valid(s6));
	s6 = "--";
	REQUIRE_FALSE(is_argument_valid(s6));
	s6 = "--printt";
	REQUIRE_FALSE(is_argument_valid(s6));
}

TEST_CASE("Test remove_word() function"){
	std::vector<std::string> original{};
	std::vector<std::string> result{};

	// empty vector, should return empty vector too
	result = remove_word(original, "word");
	REQUIRE(original.size() == 0);
	REQUIRE(result.size() == 0);

	// non-existing word, result should be identical to original
	original = {"w1", "w2", "w3"};
	result = remove_word(original, "word");
	REQUIRE(original.size() == 3);
	REQUIRE(result.size() == 3);
	REQUIRE(original.at(0) == result.at(0));
	REQUIRE(original.at(1) == result.at(1));
	REQUIRE(original.at(2) == result.at(2));

	// one occurrence, result should be of size one less than original
	original = {"w1", "w2", "w3"};
	result = remove_word(original, "w1");
	REQUIRE(original.size() == 3);
	REQUIRE(result.size() == 2);
	REQUIRE(original.at(1) == result.at(0));
	REQUIRE(original.at(2) == result.at(1));

	// two occurrences, result should be of size two less than original
	original = {"w1", "w2", "w1"};
	result = remove_word(original, "w1");
	REQUIRE(original.size() == 3);
	REQUIRE(result.size() == 1);
	REQUIRE(original.at(1) == result.at(0));
}

TEST_CASE("Test substitute_word() function"){
	std::vector<std::string> original{};
	std::vector<std::string> result{};

	// empty vector, should return empty vector too
	result = substitute_word(original, "word", "w");
	REQUIRE(original.size() == 0);
	REQUIRE(result.size() == 0);

	// non-existing word, result should be identical to original
	original = {"w1", "w2", "w3"};
	result = substitute_word(original, "word", "w");
	REQUIRE(original.size() == 3);
	REQUIRE(result.size() == 3);
	REQUIRE(original.at(0) == result.at(0));
	REQUIRE(original.at(1) == result.at(1));
	REQUIRE(original.at(2) == result.at(2));

	// one occurrence, result should be different than original at exactly one position.
	original = {"w1", "w2", "w3"};
	result = substitute_word(original, "w1", "word");
	REQUIRE(original.size() == 3);
	REQUIRE(result.size() == 3);
	REQUIRE(result.at(0) == "word");
	REQUIRE(original.at(1) == result.at(1));
	REQUIRE(original.at(2) == result.at(2));

	// two occurrences, result should be different than original at exactly two positions.
	original = {"w1", "w2", "w1"};
	result = substitute_word(original, "w1", "word");
	REQUIRE(original.size() == 3);
	REQUIRE(result.size() == 3);
	REQUIRE(result.at(0) == "word");
	REQUIRE(result.at(2) == "word");
	REQUIRE(original.at(1) == result.at(1));
}
// ============== END OF FILE ==============