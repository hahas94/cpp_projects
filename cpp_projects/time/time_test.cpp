#include "time.hpp"
#include "catch.hpp"

TEST_CASE("Time class, constructor", "[Time]"){
	// default time instance should have all three fields set to 0
	Time time_1;
	REQUIRE(time_1.hours == 0);
	REQUIRE(time_1.minutes == 0);
	REQUIRE(time_1.seconds == 0);


	// custom time instance should have all three fields set to predefined
	// values for hours, minutes and seconds.
	Time time_2{5, 20, 30};
	REQUIRE(time_2.hours == 5);
	REQUIRE(time_2.minutes == 20);
	REQUIRE(time_2.seconds == 30);

	// time instance should have all three fields within bound.
	Time time_3;
	REQUIRE(time_3.hours <= 23);
	REQUIRE(time_3.hours >= 0);
	REQUIRE(time_3.minutes <= 59);
	REQUIRE(time_3.minutes >= 0);
	REQUIRE(time_3.seconds <= 59);
	REQUIRE(time_3.seconds >= 0);

	// time instance should have all three fields within bound.
	Time time_4{11, 12, 13};
	REQUIRE(time_4.hours <= 23);
	REQUIRE(time_4.hours >= 0);
	REQUIRE(time_4.minutes <= 59);
	REQUIRE(time_4.minutes >= 0);
	REQUIRE(time_4.seconds <= 59);
	REQUIRE(time_4.seconds >= 0);

	// TODO:
	// time instance with invalid hours field should raise an error

	// TODO:
	// time instance with invalid minutes field should raise an error
	
	// TODO:
	// time instance with invalid seconds field should raise an error
}

TEST_CASE("Time class, is_valid()", "[is_valid]"){
	// time obj with correct fields return true
	Time t1;
	REQUIRE(is_valid(t1));

	Time t2{0, 45, 59};
	REQUIRE(is_valid(t2));

	// time obj with incorrect hours field return false
	Time t3{24, 0, 0};
	REQUIRE_FALSE(is_valid(t3));

	Time t4{-24, 0, 0};
	REQUIRE_FALSE(is_valid(t4));

	// time obj with incorrect minutes field return false
	Time t5{0, 61, 0};
	REQUIRE_FALSE(is_valid(t5));

	Time t6{0, -1, 0};
	REQUIRE_FALSE(is_valid(t6));

	// time obj with incorrect seconds field return false
	Time t7{0, 0, 70};
	REQUIRE_FALSE(is_valid(t7));

	Time t8{0, 0, -10};
	REQUIRE_FALSE(is_valid(t8));

	// time obj with incorrect hours and minutes fields return false
	Time t9{25, 61, 0};
	REQUIRE_FALSE(is_valid(t9));

	Time t10{-11, -10, 0};
	REQUIRE_FALSE(is_valid(t10));

	// time obj with incorrect hours and seconds fields return false
	Time t11{26, 0, 60};
	REQUIRE_FALSE(is_valid(t11));

	Time t12{-12, -10, -50};
	REQUIRE_FALSE(is_valid(t12));

	// time obj with incorrect minutes and seconds fields return false
	Time t13{0, 65, 60};
	REQUIRE_FALSE(is_valid(t13));

	Time t14{0, -20, -30};
	REQUIRE_FALSE(is_valid(t14));

	// time obj with incorrect hours, minutes and seconds fields return false
	Time t15{30, 65, 60};
	REQUIRE_FALSE(is_valid(t15));

	Time t16{-10, -20, -30};
	REQUIRE_FALSE(is_valid(t16));
}

TEST_CASE("Time class, to_string()", "[to_string]"){
	// return string repr with 24-hour based clock, default time
	Time t1;
	REQUIRE(to_string(t1) == "00:00:00");

	// return string repr with 24-hour based clock
	Time t2{1, 25, 0};
	REQUIRE(to_string(t2) == "01:25:00");

	Time t3{17, 30, 11};
	REQUIRE(to_string(t3) == "17:30:11");

	// return string repr with 12-hour based clock, AM
	Time t4{9, 10, 3};
	REQUIRE(to_string(t4, true) == "09:10:03 am");

	// return string repr with 12-hour based clock, PM
	Time t5{14, 21, 23};
	REQUIRE(to_string(t5, true) == "02:21:23 pm");
}

TEST_CASE("Time class, is_am()", "[is_am]"){
	// time before noon
	Time t1;
	REQUIRE(is_am(t1));

	Time t2{11, 59, 59};
	REQUIRE(is_am(t2));

	// time after noon
	Time t3{12, 0, 0};
	REQUIRE_FALSE(is_am(t3));

	Time t4{23, 59, 59};
	REQUIRE_FALSE(is_am(t4));
}