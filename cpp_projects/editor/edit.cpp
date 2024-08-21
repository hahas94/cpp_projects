/**
 * edit.cpp
 * --------
 * Description: 
 * 	
 * 	----- Edit Text -----
 * This file implements the main function that will process arguments and
 * perform the desired operations on a text file. 
 * 
 * When running from the command line, a number of argumnets are expected,
 * such as:
 * - name of file to read
 * followed by any of these arguments, in any order:
 * 		--print: will print the text on the console.
 * 		--frequency: will print each word and their count in decending order.
 * 		--table: similar as `--frequency`, but sorted in lexicographic order.
 * 		--substitute=<old>+<new>: replace all occurrences of `old` with `new`.
 * 		--remove=<word>: remove all occurrences of `word` in the text.
 * 
 * Example command:
 * 		`$ ./edit.out some_file.txt --substitute=the+WORD --print`
 * 
 * 	*/

#include <iostream>
#include <fstream>  
#include <string>  
#include <vector>
#include <iterator>
#include <algorithm>
#include "editor.hpp"

int main(int argc, char** argv){
	// parse arguments into a vector for easier management
	if(argc < 2){
		std::cerr << "ERROR: Not enough arguments given. Program exited." << std::endl;
		print_help();
		std::exit(1);
	}
	std::vector<std::string> arguments{argv, argv + argc};

	// all arguments that will be run has to be valid
	std::for_each(arguments.begin()+2, arguments.end(), [](std::string const& arg){
		if(!is_argument_valid(arg)){
			std::cerr << "ERROR: Argument `" << arg << "` is invalid. Program exited." << std::endl;
			print_help();
			std::exit(1);
		}
	});

	// must stop execution for file not found errors.
	std::ifstream file(arguments.at(1));
    if (!file.is_open()) {
    	std::cerr << "ERROR: File `"<< arguments.at(1) << "` not found." << std::endl;
        std::exit(1);
    }
    std::istream_iterator<std::string> begin{file}, end;
    std::vector<std::string> text{begin, end};

    std::unordered_map<std::string, int> table{create_frequency_table(text)};

    std::for_each(arguments.begin(), arguments.end(), [&](std::string const& arg){
    	// parse the argument to get the parts
    	std::vector<std::string> arg_parts{parse_argument(arg)};
    	std::string& flag{arg_parts.at(0)};

    	if(flag == "--help"){
    		std::cout << "\nDescription: \n";
    		std::cout << "  This program can be used to edit text files through the command-line.\n\n";
    		print_help();
    	}
    	else if(flag == "--print"){
    		print_text(text);
    	}
    	else if(flag == "--table"){
    		print_table(table);
    	}
    	else if(flag == "--frequency"){
    		print_frequency(table);
    	}
    	else if(flag == "--remove"){
    		std::string& word{arg_parts.at(1)};
    		text = remove_word(text, word);
    		table = create_frequency_table(text);
    	}
    	else if(flag == "--substitute"){
    		std::string const& old_word{arg_parts.at(1)};
    		std::string const& new_word{arg_parts.at(2)};
    		text = substitute_word(text, old_word, new_word);
    		table = create_frequency_table(text);
    	}
    });


	return 0;
}
// ============== END OF FILE ==============
