/**
 * files.cpp
 * ---------
 * Description: 
 * 	Handling files, opening a file and reading any text inside of it, 
 * 	counting statistics about the text. 
 * */

#include <iostream>
#include <fstream>  
#include <sstream>
#include <string>

void print_stats(std::string path);

int main(){
	std::string file_path = "../../data/poem.txt";
	print_stats(file_path);
	return 0;
}

/**
 * @brief Opens a file and prints some stats about its text. 
 */
void print_stats(std::string path){
	std::ifstream file{path};

	if(file.is_open()){
		// a word is considered any combination of non-whitespace characters
		std::string word{}; 
		std::string shortest_word{};
		int shortest_word_length{100000};
		std::string longest_word{};
		int longest_word_length{0};
		int num_words{0};
		int total_length{0};  // sum of all words lengths
		
		while(file >> word){
			// count words
			num_words++;

			// find word length
			int word_length = word.length();

			// find shortest word
			if(word_length < shortest_word_length){
				shortest_word_length = word_length;
				shortest_word = word;
			}

			// find longest word
			if(word_length > longest_word_length){
				longest_word_length = word_length;
				longest_word = word;
			}

			// find total length
			total_length += word_length;
		}

		if(total_length == 0){
			std::cerr << "WARNING: File at the path `" 
				  << path << "` is empty." << std::endl;
		}else{
			std::cout << "There are " << num_words << " words in the file.\n";
		
			std::cout << "The shortest word was " << '"' << shortest_word << '"' 
					  << " with " << shortest_word_length << " character(s)\n";
		  	
		  	std::cout << "The longest word was " << '"' << longest_word << '"' 
					  << " with " << longest_word_length << " character(s)\n";
		  	
			std::cout << "The average length was " << total_length / num_words 
					  << " character(s)\n";
		}
	}
	else{
		std::cerr << "ERROR: Cannot open file at the path `" 
				  << path << "`." << std::endl;
	}
}

// ================== END OF FILE ==================
