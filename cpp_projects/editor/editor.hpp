/**
 * editor.hpp
 * ----------
 * Description: 
 * 	Header file containing declarations for the Text Editor program. 
 * */

#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

std::unordered_map<std::string, int> create_frequency_table(std::vector<std::string> const& text_vector);

std::vector<std::pair<std::string, int>> sort_table_by_keys(std::unordered_map<std::string, int> const& table);

std::vector<std::pair<std::string, int>> sort_table_by_values(std::unordered_map<std::string, int> const& table);

void print_text(std::vector<std::string> const& text_vector, std::ostream& os = std::cout);

void print_table(std::unordered_map<std::string, int> const& table, std::ostream& os = std::cout);

void print_frequency(std::unordered_map<std::string, int> const& table, std::ostream& os = std::cout);

std::pair<std::string, std::string> split_string(std::string const& str, char split_char);

std::vector<std::string> parse_argument(std::string const& arg);

bool is_argument_valid(std::string const& arg);

std::vector<std::string> remove_word(std::vector<std::string> const& text, std::string const& word);

std::vector<std::string> substitute_word(std::vector<std::string> const& text, std::string const& old_word, std::string const& new_word);

#endif // EDITOR_HPP

// ============== END OF FILE ==============
