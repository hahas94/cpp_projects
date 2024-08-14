/**
 * simulate.cpp
 * --------=---
 * Description: 
 * 	
 * 	----- Simulations -----
 * This file implements a function that simulates three different circuit 
 * networks, each within its own block. The process is printed out to the 
 * console. This file can be run from the command-line with four expected 
 * arguments.
 * 
 * Example command:
 * 	`./simulate.out 200000 10 0.01 24`
 * 
 * 
 * 	*/

#include <iostream>
#include "circuit.hpp"

/**
 * @brief Simulating three different circuit networks.
 * 
 * @param steps: number of simulation steps
 * @param num_lines_to_print: number of lines to print to the console out of the total number of steps.
 * @param time_step: the step size used for time, in seconds. 
 * @param voltage: the battery voltage.
 * 
 */
void simulate(int steps, int num_lines_to_print, float time_step, double voltage){
	Component::time_step = time_step;
	int print_step{steps / num_lines_to_print};
	
	{
		Circuit circuit{};
		
		Connection P, N, R23, R124;
	
		circuit.add_component(new Battery("Bat", voltage, P, N));
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

		circuit.add_component(new Battery("Bat", voltage, P, N));
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

		circuit.add_component(new Battery("Bat", voltage, P, N));
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

int main(int argc, char** argv){
	int steps{};
	int num_lines_to_print{};
	float time_step{};
	double voltage{};

	// exactly 5 arguments
	if(argc != 5){
		std::cerr << "ERROR: Expected 4 arguments, got instead " << argc-1 << ". Program exited." << std::endl;
		std::exit(1);
	}

	// steps must be int
	try{
		steps = std::stoi(argv[1]);
	}
	catch(std::invalid_argument& e){
		std::cerr << "ERROR: Number of time steps must be an integer, got instead: " << argv[1] 
				  << ". Program exited.\nReason: " << e.what() << std::endl;
		std::exit(1);
	}

	// lines to print must be int
	try{
		num_lines_to_print = std::stoi(argv[2]);
	}
	catch(std::invalid_argument& e){
		std::cerr << "ERROR: Number of lines to print must be an integer, got instead: " << argv[2] 
				  << ". Program exited.\nReason: " << e.what() << std::endl;
		std::exit(1);
	}

	// time step must be float
	try{
		time_step = std::stof(argv[3]);
	}
	catch(std::invalid_argument& e){
		std::cerr << "ERROR: Time step must be a float, got instead: " << argv[3] 
				  << ". Program exited.\nReason: " << e.what() << std::endl;
		std::exit(1);
	}

	// voltage must be double
	try{
		voltage = std::stod(argv[4]);
	}
	catch(std::invalid_argument& e){
		std::cerr << "ERROR: Battery voltage must be a double, got instead: " << argv[4] 
				  << ". Program exited.\nReason: " << e.what() << std::endl;
		std::exit(1);
	}

	try{
		simulate(steps, num_lines_to_print, time_step, voltage);
	}
	catch(std::exception& e){
		std::cerr << "ERROR: " << e.what() << std::endl;
	}

	
	return 0;
}

// ============== END OF FILE ==============
