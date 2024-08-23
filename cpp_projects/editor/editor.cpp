/**
 * editor.cpp
 * ----------
 * Description: 
 *
 *     ----- Text Editor Program -----
 *
 *  This project is about implementing a text editor program that can be used from
 *  the command-line to perform various operations on a text file.
 *
 *  Given a text file, these operations are among others printing the text on the console,
 *  printing word frequency in two different formats, removing or replacing all occurrences
 *  of a word, etc.
 *
 *  The program should be developed with two things in mind: readability and scalability.
 *  The source code should be readable, easily understandable and adhere to best practices.
 *  It must be written DRY, and must be modular, so that when adding new features no or very few
 *  changes should be made to the existing code.
 *
 *  Another expectation from the project is to use the algorithms, containers and iterators
 *  from the standard library extensively.
 *
 *  No memory leak is allowed to occur, and Valgrid is used as a tool to ensure this
 *  constraint.
 *
 *  The code is developed using TDD - Test-Driven Development principles. The Catch2
 *  library is used for the testing part.
 *
 **/

#include <iomanip>
#include <iterator>
#include <algorithm>
#include "editor.hpp"

// ------------------- PRIVATE FUNCTIONS -------------------

namespace helper{
    // get the length of the longest string in list of pairs of <strings, int>
    int max_word_length(const std::vector<std::pair<std::string, int>>& pairs_vector){
        const auto it{std::ranges::max_element(pairs_vector, [](const auto& a, const auto& b){
            return a.first.length() < b.first.length();
        })};

        int max_length{0};

        if(it != pairs_vector.end()){
            max_length = (it->first).length();
        }

        return max_length;
    }
}

// ------------------- PUBLIC FUNCTIONS -------------------

namespace editor {
    /**
     * @brief Create and return an unordered frequency dictionary of all words in a vector.
     *
     * @param text_vector: constant reference to a vector of words.
     * @return table: a table of `word`:`frequency` pairs.
     */
    std::unordered_map<std::string, int> create_frequency_table(const std::vector<std::string>& text_vector){
        std::unordered_map<std::string, int> table{};
        std::ranges::for_each(text_vector, [&table](const std::string& word){table[word]++;});

        return table;
    }

    /**
     * @brief Create and return a sorted vector of pairs, sorted by first element.
     *
     * @param table: A table of words as keys and their frequencies as value.
     * @return a vector of (word, frequency) pairs, sorted by word.
     */
    std::vector<std::pair<std::string, int>> sort_table_by_keys(const std::unordered_map<std::string, int>& table){
        std::vector<std::pair<std::string, int>> key_sorted_vector(table.begin(), table.end());
        std::ranges::sort(key_sorted_vector);
        return key_sorted_vector;
    }

    /**
     * @brief Create and return a sorted vector of pairs, sorted by second element.
     *
     * @param table: A table of words as keys and their frequencies as value.
     * @return a vector of (word, frequency) pairs, sorted by frequency.
     */
    std::vector<std::pair<std::string, int>> sort_table_by_values(const std::unordered_map<std::string, int>& table){
        std::vector<std::pair<std::string, int>> value_sorted_vector(table.begin(), table.end());
        std::ranges::sort(value_sorted_vector, [](const auto& pair1, const auto& pair2){
            return pair1.second > pair2.second;
        });

        return value_sorted_vector;
    }

    /**
     * @brief Print all words in a vector, separated by space.
     *
     * @param text_vector: constant reference to a vector of words.
     * @param os: an output stream, by default std::cout is used.
     */
    void print_text(const std::vector<std::string>& text_vector, std::ostream& os){
        std::ranges::copy(text_vector, std::ostream_iterator<std::string>{os, " "});
        os << std::endl;
    }

    /**
     * @brief Print a frequency table, sorted by key.
     *
     * First the table is sorted, then printed. The keys are left-aligned
     * and sorted in descending order.
     *
     * @param table: an unordered map of words and their frequencies.
     * @param os: an output stream, by default std::cout is used.
     */
    void print_table(const std::unordered_map<std::string, int>& table, std::ostream& os){
        std::vector<std::pair<std::string, int>> sorted_vector{sort_table_by_keys(table)};
        int max_length{helper::max_word_length(sorted_vector)};

        std::ranges::for_each(sorted_vector, [&os, &max_length](const auto& pair)
        {os << std::left << std::setw(max_length + 1) << pair.first << pair.second << "\n";
        });
    }

    /**
     * @brief Print a frequency table, sorted by value.
     *
     * First the table is sorted, then printed. The keys are right-aligned
     * and sorted in descending order.
     *
     * @param table: an unordered map of words and their frequencies.
     * @param os: an output stream, by default std::cout is used.
     */
    void print_frequency(const std::unordered_map<std::string, int>& table, std::ostream& os){
        std::vector<std::pair<std::string, int>> sorted_vector{sort_table_by_values(table)};
        int max_length{helper::max_word_length(sorted_vector)};

        std::ranges::for_each(sorted_vector, [&os, &max_length](const auto& pair)
        {os << std::right << std::setw(max_length) << pair.first << " " << pair.second << "\n";
        });
    }

    /**
     * @brief Print help message.
     *
     * Describe the correct way to run the program, and the possible arguments.
     *
     */
    void print_help(){
        std::cout << "\nDescription: \n";
        std::cout << "  This program can be used to edit text files through the command-line.\n\n";
        const std::string longest_string{"--substitute=<old>+<new>"};
        const int len{static_cast<int>(longest_string.length()) + 4};

        std::cout << "Usage: \n";
        std::cout << "  <a.out> <path/to/text_file> [--help] [--print] [--table] [--frequency] [--remove=<word>] "
                     "[--substitute=<old>+<new>]\n\n";
        std::cout << "Required Arguments: \n";
        std::cout << "  <a.out>" << std::setw(5) << "An executable file.\n";
        std::cout << "  <path/to/text_file>" << std::setw(5) << "Path to a text file.\n\n";

        std::cout << "Optional Arguments: \n";
        std::cout << std::left << std::setw(len) << "  --help" << "Print this message.\n";
        std::cout << std::left << std::setw(len) << "  --print" << "Print the content of the provided text file.\n";
        std::cout << std::left << std::setw(len) << "  --table" << "Print the frequency of the words sorted by the "
                                                                   "words.\n";
        std::cout << std::left << std::setw(len) << "  --frequency" << "Print the frequency of the words sorted by the "
                                                                       "frequencies.\n";
        std::cout << std::left << std::setw(len) << "  --remove=<word>" << "Remove all occurrences of <word>.\n";
        std::cout << std::left << std::setw(len) << "  --substitute=<old>+<new>" << "Substitutes all occurrences of "
                                                                                    "<old> with <new>.\n\n";

        std::cout << "Example Usages: \n";
        std::cout << "  ./a.out text_file.txt --print\n";
        std::cout << "  ./a.out text_file.txt --remove=word --table\n";
        std::cout << "  ./a.out text_file.txt --substitute=word+WORD --frequency\n\n";
    }

    /**
     * @brief Split a string into two pieces by some character, return both pieces.
     *
     * @param str: a string.
     * @param split_char: the character to split the string by.
     * @return pair of strings resulted from splitting.
     */
    std::pair<std::string, std::string> split_string(const std::string& str, const char split_char){
        std::string left{};
        std::string right{};

        if(str.contains(split_char)){
            const int pos{static_cast<int>(str.find(split_char))};
            left = str.substr(0, pos);
            right = str.substr(pos+1, str.size());
        }
        else{
            left = str;
            right = "";
        }

        std::pair<std::string, std::string> pair{left, right};

        return pair;
    }

    /**
     * @brief Partition an argument into three pieces and return them in a vector.
     *
     * The parts are the flag, and possibly one or two non-empty parameters.
     * If some parameter don't exist, then it is represented as an empty string.
     *
     * @param arg: a command-line argument.
     * @return vector of strings resulted from partitioning.
     */
    std::vector<std::string> parse_argument(const std::string& arg){
        std::vector<std::string> parts(3);
        std::pair<std::string, std::string> pair1{};
        std::pair<std::string, std::string> pair2{};

        pair1 = split_string(arg, '=');

        if(pair1.first == "--substitute"){
            pair2 = split_string(pair1.second, '+');
            parts = {pair1.first, pair2.first, pair2.second};
        }
        else{
            parts = {pair1.first, pair1.second, ""};
        }

        return parts;
    }

    /**
     * @brief Check whether an argument is valid.
     *
     * @param arg: a command-line argument.
     * @return true for valid argument else false.
     */
    bool is_argument_valid(const std::string& arg){
        bool is_valid{false};

        if(arg == "--help" || arg == "--print" || arg == "--table" || arg == "--frequency" || arg == "--help"){
            is_valid = true;
        }

        const std::vector<std::string> parts{parse_argument(arg)};

        if (parts.at(0) == "--remove"){
            is_valid = (parts.at(0) + "=" + parts.at(1) == arg) &&
                       (!parts.at(1).empty()) && (parts.at(2).empty());
        }

        if (parts.at(0) == "--substitute"){
            is_valid = (parts.at(0) + "=" + parts.at(1) + "+" + parts.at(2) == arg) &&
                                                       (!parts.at(1).empty()) &&
                                                       (!parts.at(2).empty());
        }

        return is_valid;
    }

    /**
     * @brief Remove all occurrences of a word in a list of words.
     *
     * A new vector is created and returned, leaving the original one unmodified.
     *
     * @param text: A vector of words.
     * @param word: The string word to be removed.
     * @return new vector of words.
     */
    std::vector<std::string> remove_word(const std::vector<std::string>& text, const std::string& word){
        std::vector<std::string> new_text(text.size());
        std::ranges::copy(text, new_text.begin());

        if(const auto it{std::ranges::remove(new_text, word).begin()}; it != new_text.end()){
            new_text.erase(it, new_text.end());
        }

        return new_text;
    }

    /**
     * @brief Substitutes all occurrences of a word with another word.
     *
     * A new vector is created and returned, leaving the original one unmodified.
     *
     * @param text: A vector of words.
     * @param old_word: The string word to be replaced.
     * @param new_word: The string word to replace old word with.
     * @return new vector of words.
     */
    std::vector<std::string> substitute_word(const std::vector<std::string>& text,
                                             const std::string& old_word,
                                             const std::string& new_word){
        std::vector<std::string> new_text(text.size());
        std::ranges::copy(text, new_text.begin());
        std::ranges::replace(new_text, old_word, new_word);

        return new_text;
    }
}
// ============== END OF FILE ==============
