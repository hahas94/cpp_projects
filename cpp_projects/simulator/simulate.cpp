#include <iostream>
#include "circuit.hpp"

void simulate(){
	int steps{200000};
	int num_lines_to_print{10};
	int print_step{steps / num_lines_to_print};
	Component::time_step = 0.01;
	
	{
		Circuit circuit{};
		
		Connection P, N, R23, R124;
	
		circuit.add_component(new Battery("Bat", 24, P, N));
		circuit.add_component(new Resistor("R1", 6, P, R124));
		circuit.add_component(new Resistor("R2", 4, R124, R23));
		circuit.add_component(new Resistor("R3", 8, R23, N));
		circuit.add_component(new Resistor("R4", 12, R124, N));
	
		circuit.print_titles();

		for(int step = 0; step < steps; step++){
			circuit.step();

			if((step+1) % print_step == 0){
				circuit.step_print();
				std::cout << std::endl;
			}
		}
	}

	std::cout << std::endl;

	{
		Circuit circuit{};
		
		Connection P, N, L, R;

		circuit.add_component(new Battery("Bat", 24, P, N));
		circuit.add_component(new Resistor("R1", 150, P, L));
		circuit.add_component(new Resistor("R2", 50, P, R));
		circuit.add_component(new Resistor("R3", 100, L, R));
		circuit.add_component(new Resistor("R4", 300, L, N));
		circuit.add_component(new Resistor("R5", 250, R, N));
	
		circuit.print_titles();

		for(int step = 0; step < steps; step++){
			circuit.step();

			if((step+1) % print_step == 0){
				circuit.step_print();
				std::cout << std::endl;
			}
		}
	}

	std::cout << std::endl;

	{
		Circuit circuit{};
		
		Connection P, N, L, R;

		circuit.add_component(new Battery("Bat", 24, P, N));
		circuit.add_component(new Resistor("R1", 150, P, L));
		circuit.add_component(new Resistor("R2", 50, P, R));
		circuit.add_component(new Capacitor("C3", 1.0, L, R));
		circuit.add_component(new Resistor("R4", 300, L, N));
		circuit.add_component(new Capacitor("C5", 0.75, R, N));
	
		circuit.print_titles();

		for(int step = 0; step < steps; step++){
			circuit.step();

			if((step+1) % print_step == 0){
				circuit.step_print();
				std::cout << std::endl;
			}
		}
	}
}