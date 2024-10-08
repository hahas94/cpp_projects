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

#include <iostream>
#include <iomanip> 
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
void Connection::set_charge(double c){
	_charge = c;
}

/**
 * @brief Getting the charge through a connection point.
 * 
 * @return the charge.
 * 
 */
double Connection::get_charge() const{
	return _charge;
}

/**
 * @brief Increasing the charge through a connection point by some charge.
 * 
 * @param c: charge to add.
 * @throws std::invalid_argument if the charge argument is negative.
 * 
 */
void Connection::increase_charge(double c){
	if(c < 0){
		throw std::invalid_argument("Charge cannot be negative.");
	}
	_charge += c;
}

/**
 * @brief Decreasing the charge through a connection point by some charge.
 * 
 * @param c: charge to remove.
 * @throws std::invalid_argument if the charge argument is negative or 
 *  larger than current charge.
 * 
 */
void Connection::decrease_charge(double c){
	if(c < 0){
		throw std::invalid_argument("Charge cannot be negative.");
	}

	if(c > _charge){
		throw std::invalid_argument("Charge too high. Will result in invalid charge.");
	}

	_charge -= c;
}

/**
 * Class Component:
 * 	This class represents a Component object, which is an abstract object, because 
 * 	some functionality is unique to each of its child classes. However, there are
 * 	identical functionalities as well, and they are implemented here.
 * 	
 * 	For instance, the voltage over a component is the difference between the charge
 * 	of its two terminals.
 * 
 */

float Component::time_step = 0.0;  // Static variable definition of Component class

/**
 * @brief Initializing a Component object.
 * 
 */
Component::Component(std::string name, Connection& tA, Connection& tB, double voltage)
	: _name{name}, _terminalA{tA}, _terminalB{tB}, _voltage{voltage}, _current{0}
	{}

/**
 * @brief Getting the voltage over a component.
 * 
 * @return the charge.
 * 
 */
double Component::get_voltage() const{
	return _voltage;
}

/**
 * @brief Getting the current through a component.
 * 
 * @return the current.
 * 
 */
double Component::get_current() const{
	return _current;
}

std::string Component::get_name(){
	return _name;
}

/**
 * @brief Updating the voltage over a component.
 * 
 * The voltage over a component is defined as the difference between the voltage over 
 * its two terminals. More specifically, it is the difference between the most positive
 * and the least positive terminal charges.
 * 
 */
void Component::_update_voltage(){
	if(_terminalA.get_charge() > _terminalB.get_charge()){
		_voltage = _terminalA.get_charge() - _terminalB.get_charge();
	}
	else{
		_voltage = _terminalB.get_charge() - _terminalA.get_charge();
	} 
}

/**
 * @brief Updating the charge of the connections.
 * 
 * The voltage over a component is defined as the difference between the voltage over 
 * its two terminals. More specifically, it is the difference between the most positive
 * and the least positive terminal charges.
 * 
 */
void Component::_update_connections_charges(double c){
	if(_terminalA.get_charge() > _terminalB.get_charge()){
		_terminalA.decrease_charge(c);
		_terminalB.increase_charge(c);
	}
	else{
		_terminalA.increase_charge(c);
		_terminalB.decrease_charge(c);
	}
}

/**
 * Class Battery:
 * 	This class represents a battery object, which has a voltage, and moves charge
 * 	from the negative terminal to the connection point it is conneted to on that
 * 	terminal. The positive terminal receives no charge. A battery is assumed to never
 * 	run out.
 * 	
 * 	Thus a step in the simulation makes the battery to move charge to a connection.
 * 
 */

/**
 * @brief Initializing a battery object.
 * 
 * @param name: name of the battery.
 * @param voltage: the voltage of the battery
 * @param tA, tB: references to the connection points on each of its terminals.
 * 
 */
Battery::Battery(std::string name, double voltage, Connection& tA, Connection& tB)
	: Component(name, tA, tB, voltage)
	{}

/**
 * @brief Stepping time in a battery.
 * 
 * Each step the battery moves a charge equal to its voltage through the connection
 * on its negative terminal.
 * 
 */
void Battery::step(){
	_terminalA.set_charge(get_voltage());
	_terminalB.set_charge(0.0);
}

/**
 * @brief Updating the current through a battery.
 * 
 * Since a battery doesn't get any charge from its positive terminal, its current
 * will always be zero. This method is not used in the battery component, it is only
 * there because it is a virtual function.
 * 
 */
void Battery::_update_current(){
	_current = 0;
}

/**
 * Class Resistor:
 * 	This class represents a resistor object, which has a resistance, a voltage
 * 	over it, and moves charge from one connection to the other connection point it
 * 	is conneted to. The function of a resistor is to restrict the flow of charge in
 * 	order to prevent overheat, for instance.
 * 	
 * 	Thus a step in the simulation makes the resistor to move charge from its most positively 
 * 	charged terminal to the least charged, where the moved charge is proportional to the voltage
 * 	over it, the resistance and the time step used.
 * 
 */

/**
 * @brief Initializing a resistor object.
 * 
 * @param name: name of the resistor.
 * @param resistance: the resistance of the resistor, in Ohm.
 * @param tA, tB: references to the connection points on each of its terminals.
 * 
 */
Resistor::Resistor(std::string name, double resistance, Connection& tA, Connection& tB)
	: Component(name, tA, tB), _resistance{resistance}
	{}

/**
 * @brief Stepping time in a resistor.
 * 
 * Each step the resistor moves some charge forward but by restsricting the incoming charge.
 * 
 */
void Resistor::step(){
	double charge_to_move{(_voltage / _resistance) * time_step};
	_update_connections_charges(charge_to_move);

	_update_voltage();
	_update_current();
}

// current through a resistor is the voltage over it divided by its resistance.
void Resistor::_update_current(){
	_current = _voltage / _resistance;
}

/**
 * Class Capacitor:
 * 	This class represents a capacitor object, which has a capacitance, a voltage
 * 	over it, and moves charge from one connection to the other connection point it
 * 	is conneted to. Additionally it will store some of the charge flowing through it
 * 	in order to use it temporarily if the flow is stopped.
 * 
 */

/**
 * @brief Initializing a capacitor object.
 * 
 * @param name: name of the capacitor.
 * @param capacitance: the capacitance of the resistor, in Ohm.
 * @param tA, tB: references to the connection points on each of its terminals.
 * 
 */
Capacitor::Capacitor(std::string name, double capacitance, Connection& tA, Connection& tB)
	: Component(name, tA, tB), _capacitance{capacitance}, _charge_stored{0}
	{}

/**
 * @brief Stepping time in a capacitor.
 * 
 * Each step the resistor moves some charge forward and stores some of it as well.
 * 
 */
void Capacitor::step(){
	double charge_to_store{_capacitance * (_voltage - _charge_stored) * time_step};
	_update_connections_charges(charge_to_store);
	_charge_stored += charge_to_store;
	_update_voltage();
	_update_current();
}

// current through a capacitor is C(V − L), C capacitance, V voltage, L charge.
void Capacitor::_update_current(){
	_current = _capacitance * (_voltage - _charge_stored);
}

/**
 * Class Circuit:
 * 	This class represents a circuit network, where it has a list of components 
 * 	and can step each component. 
 * 
 */

/**
 * @brief Initializing an empty circuit.
 * 
 */
Circuit::Circuit()
	: _list{}
	{}

/**
 * @brief Destructing a circuit.
 * 
 */
Circuit::~Circuit(){
	for(Component* el : _list){
		delete el;
	}
}

/**
 * @brief Initializing circuit with variable number of components.
 * 
 * @param list: a number of components objects.
 */
Circuit::Circuit(std::initializer_list<Component*> list)
	: _list{}
{
	for(Component* el : list){
		_list.push_back(el);
	}
}

/**
 * @brief Stepping a circuit network.
 * 
 * All components are stepped once.
 * 
 */
void Circuit::step(){
	for(Component* el : _list){
		el->step();
	}
}

/**
 * @brief Printing the titles and subtitles for the simulation.
 * 
 */ 
void Circuit::print_titles(){
	_print_top_titles();
	_print_sub_titles();
}

/**
 * @brief Printing all component's voltage and current at the moment.
 * 
 */
void Circuit::step_print() const{
	std::cout << std::fixed << std::setprecision(2);
	for(Component* el : _list){
		std::cout << std::setw(6) << el->get_voltage() << std::setw(6) << el->get_current();
	}
}

/**
 * @brief Adding a new component to the circuit.
 * 
 * @param comp: pointer to component to add.
 * 
 */
void Circuit::add_component(Component* comp){
	_list.push_back(comp);
}

/**
 * @brief Getting the list of components.
 * 
 * @return std::vector<Component*>
 */
const std::vector<Component*>& Circuit::get_list() const{
	return _list;
}

void Circuit::_print_top_titles() const{
	for(Component* el : _list){
		std::cout << std::setw(12) << el->get_name();
	}
	std::cout << std::endl;
}

void Circuit::_print_sub_titles() const{
	for(long unsigned int i{0}; i < _list.size(); i++){
		std::cout << std::setw(6) << "Volt" << std::setw(6) << "Curr";
	}
	std::cout << std::endl;
}
// ============== END OF FILE ==============
