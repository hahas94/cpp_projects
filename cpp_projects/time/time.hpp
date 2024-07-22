/**
 * time.hpp
 * ------------
 * Description: 
 * 	Header file containing declarations for the Time library. 
 * */

#ifndef TIME_HPP
#define TIME_HPP

#include <string>

struct Time{
	int hours{0};
	int minutes{0};
	int seconds{0};
};

bool is_valid(const Time& time);

std::string to_string(const Time& time, bool use_12_hour_format=false);

bool is_am(const Time& time);

#endif // TIME_HPP
