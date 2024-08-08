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

	void set_charge(double c);
	double get_charge() const;

private:
	double _charge;
};

class Component{
public:
	Component(Connection& tA, Connection& tB, double voltage = 0);
	
	virtual ~Component() = default;

	static float time_step;

	virtual void step() = 0;

	double get_voltage() const;
	
	double get_current() const;

protected:
	Connection& _terminalA;
	Connection& _terminalB;

	double _voltage;
	double _current;

	Connection& _get_smaller_connection() const;

	void _update_voltage();

	virtual void _update_current() = 0;
};

class Battery : public Component{
public:
	Battery(std::string name, double voltage, Connection& tA, Connection& tB);

	void step() override;

protected:
	void _update_current() override;

private:
	std::string _name;	
};


#endif // CIRCUIT_HPP

// ============== END OF FILE ==============
