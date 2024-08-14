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
#include <vector>

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
	Component(std::string name, Connection& tA, Connection& tB, double voltage = 0);
	
	virtual ~Component() = default;

	static float time_step;

	virtual void step() = 0;

	double get_voltage() const;
	
	double get_current() const;

	std::string get_name();

protected:
	std::string _name;
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
	~Battery();

	void step() override;

private:
	void _update_current() override;
};

class Resistor : public Component{
public:
	Resistor(std::string name, double resistance, Connection& tA, Connection& tB);
	~Resistor();

	void step() override;

private:
	double _resistance;

	void _update_current() override;
};

class Capacitor : public Component{
public:
	Capacitor(std::string name, double capacitance, Connection& tA, Connection& tB);
	~Capacitor();

	void step() override;

private:
	double _capacitance;
	double _charge_stored;

	void _update_current() override;
};

class Circuit{
public:
	Circuit();

	Circuit(std::initializer_list<Component*> list);

	~Circuit();

	void step();

	void print_titles();

	void step_print() const;

	void add_component(Component* comp);

	const std::vector<Component*>& get_list() const;

private:
	std::vector<Component*> _list;

	void _print_top_titles() const;
	void _print_sub_titles() const;
};

void simulate();

#endif // CIRCUIT_HPP

// ============== END OF FILE ==============
