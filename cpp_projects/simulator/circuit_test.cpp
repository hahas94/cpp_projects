#include "circuit.hpp"
#include "../../test/catch.hpp"
#include <sstream>

// -------------- UNIT TESTS --------------

// --- Class Connection ---
TEST_CASE("Connection: Test getter/setter"){
	Connection p;

	// setting charge
	double c{12.5};
	p.set_charge(c);
	REQUIRE(p.get_charge() == c);

	p.set_charge(c+1);
	REQUIRE(p.get_charge() == c+1);

	p.increase_charge(0.5);
	REQUIRE(p.get_charge() == c+1+0.5);

	p.decrease_charge(0.9);
	REQUIRE(p.get_charge() == c+1+0.5-0.9);

	// test invalid charge updates: receive error message
	p.set_charge(0);
	REQUIRE_THROWS_WITH(p.increase_charge(-0.5), "Charge cannot be negative.");
	REQUIRE_THROWS_WITH(p.decrease_charge(-0.5), "Charge cannot be negative.");
	REQUIRE_THROWS_WITH(p.decrease_charge(2), "Charge too high. Will result in invalid charge.");
}

// --- Class Battery ---
TEST_CASE("Battery: Test constructor"){
	float time{0.1};
	Component::time_step = time;
	Connection a;
	Connection b;
	double voltage{12};

	Battery b1{"B1", voltage, a, b,};
	REQUIRE(b1.get_voltage() == voltage);
	REQUIRE(b1.get_current() == 0);
	REQUIRE(b1.time_step == time);
}

TEST_CASE("Battery: Test step method"){
	float time{0.2};
	Component::time_step = time;
	Connection a;
	Connection b;
	double voltage{12};

	Battery b1{"B1", voltage, a, b,};
	REQUIRE(b1.get_voltage() == voltage);

	// stepping one time changes the negative terminal connection, 
	// but voltage and current are unchanged.
	b1.step();
	REQUIRE(a.get_charge() == voltage);
	REQUIRE(b.get_charge() == 0);
	REQUIRE(b1.get_voltage() == voltage);
	REQUIRE(b1.get_current() == 0);

	// stepping several times changes the negative terminal connection to the battery voltage, 
	// but voltage and current are unchanged.
	b1.step();
	b1.step();
	b1.step();
	REQUIRE(a.get_charge() == voltage);
	REQUIRE(b.get_charge() == 0);
	REQUIRE(b1.get_voltage() == voltage);
	REQUIRE(b1.get_current() == 0);

	// time step should remain unchanged
	REQUIRE(b1.time_step == time);

	REQUIRE(b1.get_name() == "B1");
}

// --- Class Resistor ---
TEST_CASE("Resistor: Test step method"){
	float time{0.1};
	Component::time_step = time;
	double resistance{5};
	Connection a;
	Connection b;

	// Initial test
	Resistor r1{"R1", resistance, a, b};
	REQUIRE(r1.get_voltage() == 0);
	REQUIRE(r1.get_current() == 0);

	// stepping once does not make any difference due to voltage being 0
	r1.step();
	REQUIRE(a.get_charge() == 0);
	REQUIRE(b.get_charge() == 0);
	REQUIRE(r1.get_voltage() == 0);
	REQUIRE(r1.get_current() == 0);

	// adding charge to one connection and then stepping
	double voltage{10};
	a.set_charge(voltage);
	REQUIRE(a.get_charge() == voltage);
	REQUIRE(b.get_charge() == 0);

	r1.step();
	double res{voltage/resistance * time};
	REQUIRE(a.get_charge() == voltage);
	REQUIRE(b.get_charge() == 0);

	r1.step();
	REQUIRE(a.get_charge() == voltage - res);
	REQUIRE(b.get_charge() == res);
	REQUIRE(r1.get_voltage() == voltage - 2*res);
	REQUIRE(r1.get_current() == (voltage - 2*res) / resistance);

	REQUIRE(r1.get_name() == "R1");
}

// --- Class Capacitor ---
TEST_CASE("Capacitor: Test step method"){
	float time{0.1};
	Component::time_step = time;
	double capacitance{0.5};
	Connection a;
	Connection b;

	// Initial test
	Capacitor c1{"C1", capacitance, a, b};
	REQUIRE(c1.get_voltage() == 0);
	REQUIRE(c1.get_current() == 0);

	// stepping once does not make any difference due to voltage being 0
	c1.step();
	REQUIRE(a.get_charge() == 0);
	REQUIRE(b.get_charge() == 0);
	REQUIRE(c1.get_voltage() == 0);
	REQUIRE(c1.get_current() == 0);

	// adding charge to one connection and then stepping
	double voltage{10};
	a.set_charge(voltage);
	REQUIRE(a.get_charge() == voltage);
	REQUIRE(b.get_charge() == 0);

	c1.step();
	REQUIRE(a.get_charge() == voltage);
	REQUIRE(b.get_charge() == 0);
	REQUIRE(c1.get_voltage() == voltage);
	REQUIRE(c1.get_current() == capacitance * voltage);

	c1.step();
	REQUIRE(a.get_charge() - (voltage - 0.5) <= 0.0001);
	REQUIRE(b.get_charge() - 0.5 <= 0.0001);
	REQUIRE(c1.get_voltage() - 9 <= 0.0001);
	REQUIRE(c1.get_current() - (capacitance * (9 - 0.5)) <= 0.0001);

	REQUIRE(c1.get_name() == "C1");
}

TEST_CASE("Test Circuit"){
	// test that empty circuit can be initialized
	Circuit c{};

	// test getting the list of components
	std::vector<Component*> const& list{c.get_list()};
	REQUIRE(list.size() == 0);

	// test that circuit can be initialized with a number of components
	Connection a, b;
	Circuit c1{new Battery("B1", 1, a, b), new Battery("B2", 1, a, b), new Battery("B3", 1, a, b)};
	std::vector<Component*> const& list1{c1.get_list()};
	REQUIRE(list1.size() == 3);
	REQUIRE(list1.at(0)->get_name() == "B1");
	REQUIRE(list1.at(2)->get_name() == "B3");

	// testing circuit by adding elements manually
	Circuit c2{};
	c2.add_component(new Battery("B1", 1, a, b));
	c2.add_component(new Battery("B2", 1, a, b));
	std::vector<Component*> const& list2{c2.get_list()};
	REQUIRE(list2.size() == 2);
}

// ----------- INTERGATION TESTS ----------
TEST_CASE("Integration test: One battery with four resistors"){
	int steps{200000}; 
	Component::time_step = 0.01; 
	double voltage{24.0};
	
	Circuit circuit{};
		
	Connection P, N, R23, R124;

	circuit.add_component(new Battery("Bat", voltage, P, N));
	circuit.add_component(new Resistor("R1", 6, P, R124));
	circuit.add_component(new Resistor("R2", 4, R124, R23));
	circuit.add_component(new Resistor("R3", 8, R23, N));
	circuit.add_component(new Resistor("R4", 12, R124, N));

	for(int step = 0; step < steps; step++){
		circuit.step();
	}

	std::vector<Component*> const& list{circuit.get_list()};

	REQUIRE(list.at(0)->get_voltage() == Approx(24).epsilon(0.01));
	REQUIRE(list.at(0)->get_current() == Approx(0).epsilon(0.01));

	REQUIRE(list.at(1)->get_voltage() == Approx(11.97).epsilon(0.01));
	REQUIRE(list.at(1)->get_current() == Approx(2.0).epsilon(0.01));

	REQUIRE(list.at(2)->get_voltage() == Approx(3.99).epsilon(0.01));
	REQUIRE(list.at(2)->get_current() == Approx(1.0).epsilon(0.01));

	REQUIRE(list.at(3)->get_voltage() == Approx(7.97).epsilon(0.01));
	REQUIRE(list.at(3)->get_current() == Approx(1.0).epsilon(0.01));

	REQUIRE(list.at(4)->get_voltage() == Approx(11.97).epsilon(0.01));
	REQUIRE(list.at(4)->get_current() == Approx(1.0).epsilon(0.01));
}

TEST_CASE("Integration test: One battery with three resistors and two capacitors"){
	int steps{200000}; 
	Component::time_step = 0.01; 
	double voltage{24.0};
	
	Circuit circuit{};
		
	Connection P, N, R, L;

	circuit.add_component(new Battery("Bat", voltage, P, N));
	circuit.add_component(new Resistor("R1", 150, P, L));
	circuit.add_component(new Resistor("R2", 50, P, R));
	circuit.add_component(new Capacitor("C3", 1.0, L, R));
	circuit.add_component(new Resistor("R4", 300, L, N));
	circuit.add_component(new Capacitor("C5", 0.75, R, N));

	for(int step = 0; step < steps; step++){
		circuit.step();
	}


	std::vector<Component*> const& list{circuit.get_list()};

	REQUIRE(list.at(0)->get_voltage() - 24.0 <= 0.001);
	REQUIRE(list.at(0)->get_current() - 0.0 <= 0.001);

	REQUIRE(list.at(1)->get_voltage() - 8.0 <= 0.001);
	REQUIRE(list.at(1)->get_current() - 0.053 <= 0.001);

	REQUIRE(list.at(2)->get_voltage() - 0 <= 0.001);
	REQUIRE(list.at(2)->get_current() - 0 <= 0.001);

	REQUIRE(list.at(3)->get_voltage() - 8.0 <= 0.001);
	REQUIRE(list.at(3)->get_current() - 0 <= 0.001);

	REQUIRE(list.at(4)->get_voltage() - 16.0 <= 0.001);
	REQUIRE(list.at(4)->get_current() - 0.053 <= 0.001);

	REQUIRE(list.at(5)->get_voltage() - 24.0 <= 0.001);
	REQUIRE(list.at(5)->get_current() - 0 <= 0.001);
}

// ============== END OF FILE ==============
