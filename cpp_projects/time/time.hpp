/**
 * time.hpp
 * ------------
 * Description: 
 * 	Header file containing declarations for the Time library. 
 * */

#ifndef TIME_HPP
#define TIME_HPP

#include <string>
#include <iostream>

struct Time{
	int hours{0};
	int minutes{0};
	int seconds{0};
};

bool is_valid(Time const& time);

std::string to_string(Time const& time, bool use_12_hour_format=false);

bool is_am(Time const& time);

Time operator+(Time const& time, int const seconds);

Time operator-(Time const& time, int const seconds);

Time& operator++(Time& time);

Time operator++(Time& time, int);

Time& operator--(Time& time);

Time operator--(Time& time, int);

bool operator<(Time const& t1, Time const& t2);

bool operator==(Time const& t1, Time const& t2);

bool operator<=(Time const& t1, Time const& t2);

bool operator>=(Time const& t1, Time const& t2);

bool operator>(Time const& t1, Time const& t2);

bool operator!=(Time const& t1, Time const& t2);

std::ostream& operator<<(std::ostream& os, Time const& time);

#endif // TIME_HPP
