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

void print_text(std::vector<std::string> const& text_vector, std::ostream& os = std::cout);

std::unordered_map<std::string, int> create_frequency_table(std::vector<std::string> const& text_vector);

#endif // EDITOR_HPP

// ============== END OF FILE ==============
