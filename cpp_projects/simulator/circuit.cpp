/**
 * circuit.cpp
 * -----------
 * Description: 
 * 	
 * 	----- Circuit Framework -----
 * 
 * 	This project is about implementing a framework for designing simple circuit
 * 	networks. Additionally, a number of different circuit networks must be
 * 	simulated. Thus this framework can be used to design any (overly simple)
 * 	circuit network.
 * 
 * 	A circuit consists of a number of components, such as energy source (battery),
 * 	wires and connection points, resistors, capacitors, inductors, transistors and 
 * 	diodes.
 * 	This framework supports single battery, connection points, resistors and 
 * 	capasitors.
 * 
 * 	Since each of these components share some functionality, the task is to design
 * 	a set of classes that inherit from each other and use polymorphism to overload
 * 	identical functionality. 
 * 	For instance, each of the components battery, resistor, capasitor have two opposite
 * 	terminals, and the charge over them is calculated uniquely, while a wire simply
 * 	passes current through these components, if assuming an ideliazed scenario where
 * 	no resistance exists in the wires, i.e. perfect conductors. Batteries are assumed
 * 	to never run out.
 * 
 * 	No memory leak is allowed to occur, and Valgrid is used as a tool to ensure this
 * 	constraint.
 * 	
 * 	The code is developed using TDD - Test-Driven Development principles. The Catch2 
 * 	library is used for the tesing part.
 * 
 * 	*/

#include "circuit.hpp"

/**
 * Class Connection:
 * 	This class represents a connection point object, which is an abstraction of wire
 * 	segments within a circuit network.
 * 	A wire has the role of moving charge from one end to the other, without having any
 * 	resistance, therefore this class supports setting the charge and getting the charge,
 * 	as its sole functionality.
 * 
 */

/**
 * @brief Initializing an connection point.
 * 
 */
Connection::Connection()
	: _charge{0} 
	{}

/**
 * @brief Setting the charge through a connection point.
 * 
 * @param c: charge in Volts
 */
void Connection::charge(double c){
	_charge = c;
}

/**
 * @brief Getting the charge through a connection point.
 * 
 * @return the charge.
 * 
 */
double Connection::charge() const{
	return _charge;
}

// ============== END OF FILE ==============
