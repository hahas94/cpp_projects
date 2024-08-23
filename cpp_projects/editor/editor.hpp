/**
 * editor.hpp
 * ----------
 * Description:
 *   Header file containing declarations for the Text Editor program. 
 * */

#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

namespace editor {
    std::unordered_map<std::string, int> create_frequency_table(const std::vector<std::string>& text_vector);

    std::vector<std::pair<std::string, int>> sort_table_by_keys(const std::unordered_map<std::string, int>& table);

    std::vector<std::pair<std::string, int>> sort_table_by_values(const std::unordered_map<std::string, int>& table);

    void print_text(const std::vector<std::string>& text_vector, std::ostream& os = std::cout);

    void print_table(const std::unordered_map<std::string, int>& table, std::ostream& os = std::cout);

    void print_frequency(const std::unordered_map<std::string, int>& table, std::ostream& os = std::cout);

    void print_help();

    std::pair<std::string, std::string> split_string(const std::string& str, char split_char);

    std::vector<std::string> parse_argument(const std::string& arg);

    bool is_argument_valid(const std::string& arg);

    std::vector<std::string> remove_word(const std::vector<std::string>& text, const std::string& word);

    std::vector<std::string> substitute_word(const std::vector<std::string>& text, const std::string& old_word,
                                             const std::string& new_word);

}

namespace helper {
    int max_word_length(const std::vector<std::pair<std::string, int>>& pairs_vector);
}

#endif // EDITOR_HPP

// ============== END OF FILE ==============
