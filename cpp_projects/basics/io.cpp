/**
 * io.cpp
 * ------
 * Description: 
 * 	This file demonstrates exercising I/O operations, where the 
 * 	program receives input from a user and prints out what the 
 *  user inputed.		
 * */

#include <iostream>  
#include <string>
#include <iomanip> 

int main(){
	std::cout << std::fixed; // fixing number of decimal points

	int integer_1{};
	int integer_2{};
	int integer_3{};
	int integer_4{};

	std::cout << "Enter one integer: ";
	std::cin >> integer_1;
	std::cout << "You entered the number: " << integer_1 << "\n";

	std::cout << "\n";

	std::cout << "Enter four integers: ";
	std::cin >> integer_1 >> integer_2 >> integer_3 >> integer_4;
	std::cout << "You entered the numbers: " << integer_1 << " " << integer_2 << \
				 " " << integer_3  << " " << integer_4 << "\n";

	std::cout << "\n";

	double real{};
	std::cout << "Enter one integer and one real number: ";
	std::cin >> integer_1 >> real;
	std::cout << "The real is: " << std::setw(11) << std::setprecision(3) << real << "\n";
	std::cout << "The integer is: " << std::setw(8) << integer_1 << "\n";

	std::cout << "\n";

	std::cout << "Enter one real and one integer number: ";
	std::cin >> real >> integer_1;
	std::cout << "The real is: " << std::setfill('.') << std::setw(11) << std::setprecision(3) << real << "\n";
	std::cout << "The integer is: " << std::setfill('.') << std::setw(8) << integer_1 << "\n";

	std::cout << "\n";

	char letter{};
	std::cout << "Enter a character: ";
	std::cin >> letter;
	std::cout << "You entered: " << letter << "\n";

	std::cout << "\n";

	std::string str{};
	std::cout << "Enter a word: ";
	std::cin >> str;
	std::cout << "The word '" << str << "' has " << str.length() << " character(s).\n";

	std::cout << "\n";

	std::cout << "Enter an integer and a word: ";
	std::cin >> integer_1 >> str;
	std::cout << "You entered '" << integer_1 << "' and '" << str << "'.\n";

	std::cout << "\n";

	std::cout << "Enter a character and a word: ";
	std::cin >> letter >> str;
	std::cout << "You entered the string " << '"' << str << '"' << " and the character '" << letter << "'.\n";

	std::cout << "\n";

	std::cout << "Enter a word and real number: ";
	std::cin >> str >> real;
	std::cout << "You entered " << '"' << str << '"' << " and " << '"' << std::setprecision(3) << real << '"' << ".\n";

	std::cout << "\n";

	std::cout << "Enter a text-line: ";
	std::getline(std::cin >> std::ws, str);
	std::cout << "You entered: " << '"' << str << '"' << ".\n";

	std::cout << "\n";

	return 0;
}

// ================== END OF FILE ==================