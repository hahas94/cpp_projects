/**
 * editor.cpp
 * ----------
 * Description: 
 * 	
 * 	----- Text Editor Program -----
 * 
 * 	This project is about implementing a text editor program that can be used from
 * 	the command-line to perform various operations on a text file.
 * 
 * 	Given a text file, these operations are among others printing the text on the console,
 * 	printing word frequency in two different formats, removing or replacing all occurrences
 * 	of a word, etc.
 * 
 * 	The program should be developed with two things in mind: readability and scalability.
 * 	The source code should be readable, easily understandable and adher to best practices.
 * 	It must be written DRY, and must be modular, so that when adding new features no or very few
 * 	changes should be made to the existing code.
 * 
 * 	Another expectation from the project is to use the algorithms, containers and iterators
 * 	from the standard library extensively.
 * 
 * 	No memory leak is allowed to occur, and Valgrid is used as a tool to ensure this
 * 	constraint.
 * 	
 * 	The code is developed using TDD - Test-Driven Development principles. The Catch2 
 * 	library is used for the tesing part.
 * 
 * 	*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>

/**
 * @brief Print all words in a vector, separated by space.
 * 
 * @param text_vector: constant referense to a vector of words.
 * @param os: an output stream, by default std::cout is used.
 */
void print_text(std::vector<std::string> const& text_vector, std::ostream& os){
	std::copy(text_vector.begin(), text_vector.end(), std::ostream_iterator<std::string>{os, " "});
}


// ============== END OF FILE ==============
