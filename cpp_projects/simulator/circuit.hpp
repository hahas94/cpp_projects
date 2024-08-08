/**
 * circuit.hpp
 * -----------
 * Description: 
 * 	Header file containing declarations for the Circuit framework. 
 * */

#ifndef CIRCUIT_HPP
#define CIRCUIT_HPP

#include <string>
#include <iostream>
#include <initializer_list>

class Connection{
public:
	Connection();

	void charge(double c);
	double charge() const;

private:
	double _charge;
};


#endif // CIRCUIT_HPP

// ============== END OF FILE ==============
