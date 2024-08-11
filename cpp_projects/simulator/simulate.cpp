#include <iostream>
#include <string>
#include <vector>
#include <iomanip> 
#include "circuit.hpp"

void simulate(){
	int steps{200000};
	int lines{10};
	Component::time_step = 0.01;
	
	std::vector<Component*> circuit;
	
	Connection P, N, R23, R124;

	circuit.push_back(new Battery("B1", 24, P, N));
	circuit.push_back(new Resistor("R1", 6, P, R124));
	circuit.push_back(new Resistor("R2", 4, R124, R23));
	circuit.push_back(new Resistor("R3", 8, R23, N));
	circuit.push_back(new Resistor("R4", 12, R124, N));

	int lines_to_print{steps / lines};

	
	
	

	std::cout << std::fixed << std::setprecision(2);

	for(int step = 0; step < steps; step++){
		for(Component* comp : circuit){
			comp->step();
			if(step % lines_to_print == 0){
				std::cout << std::setw(6) << comp->get_voltage() << std::setw(6) << comp->get_current(); 
			}
		}
		if(step % lines_to_print == 0){
			std::cout << std::endl;
		}
	}
}