/**
 * edit.cpp
 * --------
 * Description: 
 *
 *     ----- Edit Text -----
 *  This file implements the main function that will process arguments and
 *  perform the desired operations on a text file.
 * 
 *  When running from the command line, a number of arguments are expected,
 *  such as:
 * -- name of file to read
 *   followed by any of these arguments, in any order:
 *   --helper
 *   --print: will print the text on the console.
 *   --frequency: will print each word and their count in descending order.
 *   --table: similar as `--frequency`, but sorted in lexicographic order.
 *   --substitute=<old>+<new>: replace all occurrences of `old` with `new`.
 *   --remove=<word>: remove all occurrences of `word` in the text.
 * 
 * Example command:
 *   `$ ./edit.out some_file.txt --substitute=the+WORD --print`
 * 
 **/

#include <fstream>
#include <iterator>
#include <algorithm>
#include "editor.hpp"

int main(int argc, char** argv){
    // parse arguments into a vector for easier management

    if(argc < 2){
        std::cerr << "ERROR: Not enough arguments given. Program terminated." << std::endl;
        editor::print_help();
        std::terminate();
    }

    std::vector<std::string> arguments{argv, argv + argc};

    // all arguments that will be run has to be valid
    std::ranges::for_each(arguments.begin() + 2, arguments.end(), [](const std::string &arg) {
      if (!editor::is_argument_valid(arg)) {
          std::cerr << "ERROR: Argument `" << arg << "` is invalid. Program exited." << std::endl;
          editor::print_help();
          std::terminate();
      }
    });

    if(argc == 2 && arguments.at(1) == "--help") {
        editor::print_help();
    }
    else {
        // must stop execution for file not found errors.
        std::ifstream file(arguments.at(1));
        if (!file.is_open()) {
            std::cerr << "ERROR: File `" << arguments.at(1) << "` not found." << std::endl;
            std::terminate();
        }
        std::istream_iterator<std::string> begin{file};
        std::istream_iterator<std::string> end;
        std::vector<std::string> text{begin, end};

        std::unordered_map<std::string, int> table{editor::create_frequency_table(text)};

        std::ranges::for_each(arguments, [&](const std::string& arg) {
        // parse the argument to get the parts
        const std::vector<std::string> arg_parts{editor::parse_argument(arg)};
        const std::string& flag{arg_parts.at(0)};

        if (flag == "--help") {
            editor::print_help();
        } else if (flag == "--print") {
            editor::print_text(text);
        } else if (flag == "--table") {
            editor::print_table(table);
        } else if (flag == "--frequency") {
            editor::print_frequency(table);
        } else if (flag == "--remove") {
            const std::string& word{arg_parts.at(1)};
            text = editor::remove_word(text, word);
            table = editor::create_frequency_table(text);
        } else if (flag == "--substitute") {
            const std::string& old_word{arg_parts.at(1)};
            const std::string& new_word{arg_parts.at(2)};
            text = editor::substitute_word(text, old_word, new_word);
            table = editor::create_frequency_table(text);
        } else{}
        });
    }

    return 0;
}

// ============== END OF FILE ==============
