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

TEST_CASE("Time class, operator+()", "[operator+]"){
	// increase time with 0 seconds
	Time t1{};
	Time t1_future{t1 + 0};
	REQUIRE(to_string(t1_future) == "00:00:00");
	REQUIRE(is_valid(t1_future));

	// increase time with seconds
	Time t2{10, 30, 12};
	int seconds = 15;
	Time t2_future{t2 + seconds};
	REQUIRE(to_string(t2_future) == "10:30:27");
	REQUIRE(is_valid(t2_future));

	// increase time with seconds and minutes 
	Time t3{11, 17, 4};
	seconds = 65;
	Time t3_future{t3 + seconds};
	REQUIRE(to_string(t3_future) == "11:18:09");
	REQUIRE(is_valid(t3_future));

	// increase time with seconds, minutes and hours
	Time t4{13, 21, 0};
	seconds = 3663;
	Time t4_future{t4 + seconds};
	REQUIRE(to_string(t4_future) == "14:22:03");
	REQUIRE(is_valid(t4_future));

	// increase time with 10 seconds and ensure old time is unchanged
	Time t5{};
	t5 + 10;
	REQUIRE(to_string(t5) == "00:00:00");
	REQUIRE(is_valid(t5));

	// increase time with seconds and hours 
	Time t6{14, 20, 1};
	seconds = 7205;
	Time t6_future{t6 + seconds};
	REQUIRE(to_string(t6_future) == "16:20:06");
	REQUIRE(is_valid(t6_future));

	// increase time with minutes and hours 
	Time t7{22, 11, 10};
	seconds = 10920;
	Time t7_future{t7 + seconds};
	REQUIRE(to_string(t7_future) == "01:13:10");
	REQUIRE(is_valid(t7_future));

	// increase time with seconds, that will change minutes too
	Time t8{23, 50, 50};
	seconds = 11;
	Time t8_future{t8 + seconds};
	REQUIRE(to_string(t8_future) == "23:51:01");
	REQUIRE(is_valid(t8_future));

	// increase time with seconds, that will change minutes and hours too
	Time t9{23, 59, 59};
	seconds = 1;
	Time t9_future{t9 + seconds};
	REQUIRE(to_string(t9_future) == "00:00:00");
	REQUIRE(is_valid(t9_future));

	// increase time with seconds and minutes, 
	// which in turn changes hours too
	Time t10{22, 58, 55};
	seconds = 65;
	Time t10_future{t10 + seconds};
	REQUIRE(to_string(t10_future) == "23:00:00");
	REQUIRE(is_valid(t10_future));

	// increase time to change day
	Time t11{23, 0, 0};
	seconds = 7200;
	Time t11_future{t11 + seconds};
	REQUIRE(to_string(t11_future) == "01:00:00");
	REQUIRE(is_valid(t11_future));
}

TEST_CASE("Time class, operator-()", "[operator-]"){
	// decrease time with 0 seconds
	Time t1{};
	Time t1_past{t1 - 0};
	REQUIRE(to_string(t1_past) == "00:00:00");
	REQUIRE(is_valid(t1_past));

	// decrease time with seconds
	Time t2{10, 30, 12};
	int seconds = 10;
	Time t2_past{t2 - seconds};
	REQUIRE(to_string(t2_past) == "10:30:02");
	REQUIRE(is_valid(t2_past));

	// decrease time with seconds and minutes 
	Time t3{11, 17, 4};
	seconds = 63;
	Time t3_past{t3 - seconds};
	REQUIRE(to_string(t3_past) == "11:16:01");
	REQUIRE(is_valid(t3_past));

	// decrease time with seconds, minutes and hours
	Time t4{13, 21, 4};
	seconds = 3663;
	Time t4_past{t4 - seconds};
	REQUIRE(to_string(t4_past) == "12:20:01");
	REQUIRE(is_valid(t4_past));

	// decrease time with 10 seconds and ensure old time is unchanged
	Time t5{};
	t5 - 10;
	REQUIRE(to_string(t5) == "00:00:00");
	REQUIRE(is_valid(t5));

	// decrease time with seconds and hours 
	Time t6{14, 20, 40};
	seconds = 7205;
	Time t6_past{t6 - seconds};
	REQUIRE(to_string(t6_past) == "12:20:35");
	REQUIRE(is_valid(t6_past));

	// decrease time with minutes and hours 
	Time t7{22, 11, 10};
	seconds = 10920;
	Time t7_past{t7 - seconds};
	REQUIRE(to_string(t7_past) == "19:09:10");
	REQUIRE(is_valid(t7_past));

	// decrease time with seconds, that will change minutes too
	Time t8{23, 50, 1};
	seconds = 11;
	Time t8_past{t8 - seconds};
	REQUIRE(to_string(t8_past) == "23:49:50");
	REQUIRE(is_valid(t8_past));

	// decrease time with seconds, that will change minutes and hours too
	Time t9{};
	seconds = 1;
	Time t9_past{t9 - seconds};
	REQUIRE(to_string(t9_past) == "23:59:59");
	REQUIRE(is_valid(t9_past));

	// decrease time with seconds and minutes, 
	// which in turn changes hours too
	Time t10{0, 5, 1};
	seconds = 303;
	Time t10_past{t10 - seconds};
	REQUIRE(to_string(t10_past) == "23:59:58");
	REQUIRE(is_valid(t10_past));

	// decrease time a more than a day
	Time t11{23, 0, 0};
	seconds = 25*3600;
	Time t11_past{t11 - seconds};
	REQUIRE(to_string(t11_past) == "22:00:00");
	REQUIRE(is_valid(t11_past));
}

TEST_CASE("Time class, prefix-increment operator++()", "[operator++]"){
	// increment regular time
	Time t1{};
	++t1;
	REQUIRE(to_string(t1) == "00:00:01");
	REQUIRE(is_valid(t1));

	// increment time that will change minute
	Time t2{0, 0, 59};
	++t2;
	REQUIRE(to_string(t2) == "00:01:00");
	REQUIRE(is_valid(t2));

	// increment time that will change hour
	Time t3{0, 59, 59};
	++t3;
	REQUIRE(to_string(t3) == "01:00:00");
	REQUIRE(is_valid(t3));

	// increment time that will change day
	Time t4{23, 59, 59};
	++t4;
	REQUIRE(to_string(t4) == "00:00:00");
	REQUIRE(is_valid(t4));

	// test that incremented time changed
	Time t5{23, 59, 59};
	REQUIRE(to_string(++t5) == "00:00:00");
}

TEST_CASE("Time class, prefix-decrement operator--()", "[operator--]"){
	// decrement regular time
	Time t1{0, 0, 1};
	--t1;
	REQUIRE(to_string(t1) == "00:00:00");
	REQUIRE(is_valid(t1));

	// decrement time that will change minute
	Time t2{0, 59, 0};
	--t2;
	REQUIRE(to_string(t2) == "00:58:59");
	REQUIRE(is_valid(t2));

	// decrement time that will change hour
	Time t3{22, 0, 0};
	--t3;
	REQUIRE(to_string(t3) == "21:59:59");
	REQUIRE(is_valid(t3));

	// decrement time that will change day
	Time t4{};
	--t4;
	REQUIRE(to_string(t4) == "23:59:59");
	REQUIRE(is_valid(t4));

	// test that decremented time changed
	Time t5{23, 59, 59};
	REQUIRE(to_string(--t5) == "23:59:58");
}

TEST_CASE("Time class, postfix-increment operator++()", "[operator++]"){
	// increment regular time
	Time t1{};
	t1++;
	REQUIRE(to_string(t1) == "00:00:01");
	REQUIRE(is_valid(t1));

	// increment time that will change minute
	Time t2{0, 0, 59};
	t2++;
	REQUIRE(to_string(t2) == "00:01:00");
	REQUIRE(is_valid(t2));

	// increment time that will change hour
	Time t3{0, 59, 59};
	t3++;
	REQUIRE(to_string(t3) == "01:00:00");
	REQUIRE(is_valid(t3));

	// increment time that will change day
	Time t4{23, 59, 59};
	t4++;
	REQUIRE(to_string(t4) == "00:00:00");
	REQUIRE(is_valid(t4));

	// test that incremented time is not changed
	Time t5{23, 59, 59};
	REQUIRE(to_string(t5++) == "23:59:59");
	REQUIRE(to_string(t5) == "00:00:00");
}

TEST_CASE("Time class, postfix-decrement operator--()", "[operator--]"){
	// decrement regular time
	Time t1{0, 0, 1};
	t1--;
	REQUIRE(to_string(t1) == "00:00:00");
	REQUIRE(is_valid(t1));

	// decrement time that will change minute
	Time t2{0, 59, 0};
	t2--;
	REQUIRE(to_string(t2) == "00:58:59");
	REQUIRE(is_valid(t2));

	// decrement time that will change hour
	Time t3{22, 0, 0};
	t3--;
	REQUIRE(to_string(t3) == "21:59:59");
	REQUIRE(is_valid(t3));

	// decrement time that will change day
	Time t4{};
	t4--;
	REQUIRE(to_string(t4) == "23:59:59");
	REQUIRE(is_valid(t4));

	// test that decremented time is not changed
	Time t5{23, 59, 59};
	REQUIRE(to_string(t5--) == "23:59:59");
}

TEST_CASE("Time class, less-than operator<()", "[operator<]"){
	// both cases, second
	Time t1{0, 0, 1};
	Time t2;
	REQUIRE_FALSE(t1 < t2);
	REQUIRE(t2 < t1);

	// both cases, minute
	Time t3{0, 1, 0};
	Time t4;
	REQUIRE_FALSE(t3 < t4);
	REQUIRE(t4 < t3);

	// both cases, hour
	Time t5{1, 0, 0};
	Time t6;
	REQUIRE_FALSE(t5 < t6);
	REQUIRE(t6 < t5);

	// both cases, second and minute
	Time t7{0, 2, 1};
	Time t8;
	REQUIRE_FALSE(t7 < t8);
	REQUIRE(t8 < t7);

	// both cases, second and hour
	Time t9{1, 0, 1};
	Time t10;
	REQUIRE_FALSE(t9 < t10);
	REQUIRE(t10 < t9);

	// both cases, minute and hour
	Time t11{1, 1, 0};
	Time t12;
	REQUIRE_FALSE(t11 < t12);
	REQUIRE(t12 < t11);

	// both cases, second, minute and hour
	Time t13{1, 1, 1};
	Time t14;
	REQUIRE_FALSE(t13 < t14);
	REQUIRE(t14 < t13);
}

TEST_CASE("Time class, equality operator==()", "[operator==]"){
	// both cases, second
	Time t1{0, 0, 1};
	Time t2{0, 0, 1};
	REQUIRE(t1 == t2);
	REQUIRE(t2 == t1);

	// both cases, minute
	Time t3{0, 1, 0};
	Time t4{0, 1, 0};
	REQUIRE(t3 == t4);
	REQUIRE(t4 == t3);

	// both cases, hour
	Time t5{1, 0, 0};
	Time t6{1, 0, 0};
	REQUIRE(t5 == t6);
	REQUIRE(t6 == t5);

	// both cases, second and minute
	Time t7{0, 2, 1};
	Time t8{0, 2, 1};
	REQUIRE(t7 == t8);
	REQUIRE(t8 == t7);

	// both cases, second and hour
	Time t9{1, 0, 1};
	Time t10{1, 0, 1};
	REQUIRE(t9 == t10);
	REQUIRE(t10 == t9);

	// both cases, minute and hour
	Time t11{1, 1, 0};
	Time t12{1, 1, 0};
	REQUIRE(t11 == t12);
	REQUIRE(t12 == t11);

	// both cases, second, minute and hour
	Time t13{1, 1, 1};
	Time t14{1, 1, 1};
	REQUIRE(t13 == t14);
	REQUIRE(t14 == t13);

	// both cases, second, false
	Time t15{0, 0, 1};
	Time t16{0, 0, 2};
	REQUIRE_FALSE(t15 == t16);
	REQUIRE_FALSE(t16 == t15);

	// both cases, minute, false
	Time t17{0, 1, 0};
	Time t18{0, 2, 0};
	REQUIRE_FALSE(t17 == t18);
	REQUIRE_FALSE(t18 == t17);

	// both cases, hour, false
	Time t19{1, 0, 0};
	Time t20{2, 0, 0};
	REQUIRE_FALSE(t19 == t20);
	REQUIRE_FALSE(t20 == t19);

	// both cases, second, minute and hour, false
	Time t21{1, 1, 1};
	Time t22{2, 2, 2};
	REQUIRE_FALSE(t21 == t22);
	REQUIRE_FALSE(t22 == t21);
}