/**
 * taxation.hpp
 * ------------
 * Description: 
 * 	Header file containing declarations for taxation program. 
 * */

#ifndef TAXATION_HPP
#define TAXATION_HPP

bool is_first_price_ok(float first_price);

bool is_last_price_ok(float first_price, float last_price);

bool is_stride_ok(float stride, float first_price, float last_price);

bool is_percent_ok(float percent);

void build_table();

#endif // TAXATION_HPP