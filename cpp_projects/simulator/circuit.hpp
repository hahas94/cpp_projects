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
	void increase_charge(double c);
	void decrease_charge(double c);

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

	void _update_voltage();

	virtual void _update_current() = 0;

	void _update_connections_charges(double c);
};

class Battery : public Component{
public:
	Battery(std::string name, double voltage, Connection& tA, Connection& tB);

	void step() override;

private:
	std::string _name;	
	void _update_current() override;
};

class Resistor : public Component{
public:
	Resistor(std::string name, double resistance, Connection& tA, Connection& tB);

	void step() override;

private:
	std::string _name;
	double _resistance;

	void _update_current() override;
};

void simulate();

#endif // CIRCUIT_HPP

// ============== END OF FILE ==============
