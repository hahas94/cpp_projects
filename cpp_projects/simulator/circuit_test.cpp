#include "circuit.hpp"
#include "../../test/catch.hpp"
#include <sstream>

// -------------- UNIT TESTS --------------

// --- Class Connection ---
TEST_CASE("Connection: Test getter/setter"){
	Connection p;

	// setting charge
	double c{12.5};
	p.charge(c);
	REQUIRE(p.charge() == c);

	p.charge(c+1);
	REQUIRE(p.charge() == c+1);
}

// ----------- INTERGATION TESTS ----------

// ============== END OF FILE ==============
