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

// ------------ HELPER FUNCTIONS ------------

// Return number of seconds in a minute.
int sec_in_min(){
	return 60;
}

// Return number of seconds in an hour.
int sec_in_hour(){
	return 60 * sec_in_min();
}

// Return number of seconds in a minute.
int sec_in_day(){
	return 24 * sec_in_hour();
}

// Return number of seconds in a time.
int time_in_sec(int const h, int const m, int const s){
	int secs{h * sec_in_hour() + m * sec_in_min() + s};
	secs %= sec_in_day();
	
	// if time is negative, then map it to the corresponding actual time
	if(secs < 0){
		secs += sec_in_day();
	} 
	return secs;
}

// Partition given number of seconds and return number of hours (0 =< h <= 23).
int get_hour(int const sec){
	return sec / sec_in_hour();
}

// Partition given number of seconds and return number of minutes (0 =< m <= 59) 
int get_min(int const sec){
	return (sec % sec_in_hour()) / sec_in_min();
}

// Partition given number of seconds and return number of seconds (0 =< s <= 59) 
int get_sec(int const sec){
	return (sec % sec_in_hour()) % sec_in_min();
}

// ------------ PUBLIC FUNCTIONS ------------

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
 * @brief Addition between time point a number of seconds.
 * 
 * A new time point with a number of seconds into the future
 * is created and returned.
 * 
 * @param time: constant reference to a time object
 * @param seconds: number of seconds into the future.
 * @return Time: new Time point
 * 
 */
Time operator +(Time const& time, int const seconds){
	int future_time_in_sec{time_in_sec(time.hours, 
									   time.minutes, 
									   time.seconds + seconds)};

	Time future_time{get_hour(future_time_in_sec), 
					 get_min(future_time_in_sec), 
					 get_sec(future_time_in_sec)};

	return future_time;
}

/**
 * @brief Subtraction between time point a number of seconds.
 * 
 * A new time point with a number of seconds in the past
 * is created and returned.
 * 
 * @param time: constant reference to a time object
 * @param seconds: number of seconds in the past.
 * @return Time: new Time point
 * 
 */
Time operator-(Time const& time, int const seconds){
	return time + (-seconds);
}

/**
 * @brief ++time.
 * 
 * Prefix-increment operator overloading for a time point.
 * 
 * @param time: reference to a time object
 * @return Time: the time point changed
 * 
 */
Time& operator++(Time& time){
	int future_time_in_sec{time_in_sec(time.hours, 
									   time.minutes, 
									   time.seconds + 1)};
	
	time.hours = get_hour(future_time_in_sec);
	time.minutes = get_min(future_time_in_sec);
	time.seconds = get_sec(future_time_in_sec);

	return time;
}
