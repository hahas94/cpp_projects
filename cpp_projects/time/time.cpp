/**
 * time.cpp
 * ------------
 * Description: 
 * 	
 * 	----- Time Library -----
 * 
 * 	The task is to write a library that will be used by other programmers.
 * 	The library should implement an object for representing a time point,
 * 	as well as some functions to perform various operations on an instance
 * 	of a Time object. The code must be developed using TDD - Test-Driven
 * 	Development. The Catch2 library is used for the tesing part.
 * 
 * 	A time point is represented as Time, implemented with three integers
 * 	for hours, minutes and seconds respectively.
 * 	*/

#include "time.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

/**
 * @brief Check whether a time point is valid.
 * 
 * A time point is valid if hours, minutes and seconds are within
 * their corresponding bounds.
 * 
 * @return Whether the object is valid.
 */
bool is_valid(Time const& time){
	bool hour_valid{time.hours >= 0 && time.hours <= 23};
	bool minutes_valid{time.minutes >= 0 && time.minutes <= 59};
	bool seconds_valid{time.seconds >= 0 && time.seconds <= 59};

	return hour_valid && minutes_valid && seconds_valid;
}

/**
 * @brief Convert a time point to its string format.
 * 
 * The string is in the format "HH:MM:SS" by default,
 * but can be turned to a 12-hour based clock with the
 * parameter `is_12_hour_format=true`.
 * 
 * @param time: constant reference to a time object
 * @param is_12_hour_format Whether string should be 12-hour based.
 * @return The string representation.
 */
std::string to_string(Time const& time, bool use_12_hour_format){
	std::ostringstream oss;
	int h{time.hours};
	std::string trailer{""};

	if(use_12_hour_format){
		if(h > 12){
			h %= 12;
			trailer = " pm";
		}else{
			trailer = " am";
		}
	}
	
	oss << std::setw(2) << std::setfill('0') << h << ":" 
			<< std::setw(2) << std::setfill('0') << time.minutes << ":" 
			<< std::setw(2) << std::setfill('0') << time.seconds 
			<< trailer;
	
	return oss.str();
}

/**
 * @brief Check whether a time point is before or after noon.
 * 
 * @param time: constant reference to a time object
 * @return bool: true if time is AM else false
 * 
 */
bool is_am(Time const& time){
	return time.hours < 12;
}

/**
 * @brief Create a new time point a number of seconds into the future.
 * 
 * @param time: constant reference to a time object
 * @param seconds: number of seconds into the future.
 * @return bool: true if time is AM else false
 * 
 */
Time operator +(Time const& time, int const seconds){
	Time future_time{time};
	
	int sec_in_hour{3600};
	int sec_in_min{60};

	int hours{seconds / sec_in_hour};
	int minutes{(seconds - (hours * sec_in_hour)) / sec_in_min};
	int sec{seconds - (hours * sec_in_hour) - (minutes * sec_in_min)};
	
	future_time.hours += hours;
	future_time.minutes += minutes;
	future_time.seconds += sec;

	return future_time;
}

