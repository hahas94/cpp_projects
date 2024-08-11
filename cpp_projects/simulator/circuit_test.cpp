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

// ----------- INTERGATION TESTS ----------

// ------------ SIMULATION TESTS ----------
TEST_CASE("Test simulate function"){
	//simulate();
}

// ============== END OF FILE ==============
