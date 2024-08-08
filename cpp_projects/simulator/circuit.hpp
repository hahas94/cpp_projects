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

class Component{
public:
	Component(Connection& tA, Connection& tB);
	virtual ~Component() = default;

	static float time_step;

	virtual void step() = 0;

protected:
	double _voltage;
	double _current;

	Connection& _terminalA;
	Connection& _terminalB;
};


#endif // CIRCUIT_HPP

// ============== END OF FILE ==============
