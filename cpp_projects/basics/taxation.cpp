/**
 * taxation.cpp
 * ------------
 * Description: 
 * 	This file prints a taxation VAT table given some information 
 * 	from a user. There is one row for each stride between start price
 * 	and end price, where it contains the price, the taxed amount and 
 * 	the total. 
 * 	One assumption is that the values entered are in the range  
 * 	[-100.00, +100000.00] and with at most two decimal points.
 * 
 * 	Example:
 * 		INPUT PART
 *		==========
 *		Enter first price: 10.00
 *		Enter last price : 15.00
 *		Enter stride : 0.5
 *		Enter tax percent: 10.00
 *		
 * 		TAX TABLE
 *		=========
 *			   Price 			   Tax 	   Price with tax
 *		-------------------------------------------------
 *				10.00 			   1.00 			11.00
 *				10.50 			   1.05 			11.55
 *				11.00 		       1.10 			12.10
 *					. 	              . 		        .
 *					. 	              . 				.
 *				15.00 			   1.50 			16.50
 * 		
 * */

#include "taxation.hpp"
#include <iostream>  
#include <string>
#include <iomanip> 

void test_functions();

int main(){
	// test_functions();
	build_table();
	return 0;
}

bool is_first_price_ok(float first_price){
	float minimum{0.00};
	float maximum{100000.00};
	return first_price >= minimum && first_price <= maximum;
}

bool is_last_price_ok(float first_price, float last_price){
	float maximum{100000.00};
	return first_price < last_price && last_price <= maximum;
}

bool is_stride_ok(float stride, float first_price, float last_price){
	float price_diff{last_price - first_price};
	float minimum {0.01};
	return stride >= minimum && stride <= price_diff;
}

bool is_percent_ok(float percent){
	float minimum{0.00};
	float maximum{100.00};

	return percent >= minimum && percent <= maximum;
}

void test_functions(){
	// testing function `is_first_price_ok`:
	if(is_first_price_ok(-1)){
		std::cerr << "Error: is_first_price_ok(-1)=true\n";
	}

	if(is_first_price_ok(1000001)){
		std::cerr << "Error: is_first_price_ok(1000001)=true\n";
	}

	if(!is_first_price_ok(0)){
		std::cerr << "Error: is_first_price_ok(0)=false\n";
	}

	if(!is_first_price_ok(10)){
		std::cerr << "Error: is_first_price_ok(10)=false\n";
	}

	if(!is_first_price_ok(100000)){
		std::cerr << "Error: is_first_price_ok(100000)=false\n";
	}

	// testing function `is_last_price_ok`:

	if(is_last_price_ok(0, -1)){
		std::cerr << "Error: is_last_price_ok(0, -1)=true\n";
	}

	if(is_last_price_ok(0, 0)){
		std::cerr << "Error: is_last_price_ok(0, 0)=true\n";
	}

	if(is_last_price_ok(0, 100001)){
		std::cerr << "Error: is_last_price_ok(0, 100001)=true\n";
	}

	if(!is_last_price_ok(0, 1)){
		std::cerr << "Error: is_last_price_ok(0, 1)=false\n";
	}

	if(!is_last_price_ok(10, 20)){
		std::cerr << "Error: is_last_price_ok(10, 20)=false\n";
	}

	if(!is_last_price_ok(1, 100000)){
		std::cerr << "Error: is_last_price_ok(1, 100000)=false\n";
	}
	
	// testing function `stride`:
	if(is_stride_ok(-1, 0, 1)){
		std::cerr << "Error: is_stride_ok(-1, 0, 1)=true\n";
	}

	if(is_stride_ok(0, 0, 1)){
		std::cerr << "Error: is_stride_ok(0, 0, 1)=true\n";
	}

	if(is_stride_ok(10, 0, 1)){
		std::cerr << "Error: is_stride_ok(10, 0, 1)=true\n";
	}

	if(!is_stride_ok(0.01, 0, 1)){
		std::cerr << "Error: is_stride_ok(0.01, 0, 1)=false\n";
	}

	if(!is_stride_ok(0.5, 0, 10)){
		std::cerr << "Error: is_stride_ok(0.5, 0, 10)=false\n";
	}

	if(!is_stride_ok(5, 0, 5)){
		std::cerr << "Error: is_stride_ok(5, 0, 5)=false\n";
	}

	// testing function `is_percent_ok`:

	if(is_percent_ok(-1)){
		std::cerr << "Error: is_percent_ok(-1)=true\n";
	}

	if(is_percent_ok(-0.5)){
		std::cerr << "Error: is_percent_ok(-0.5)=true\n";
	}

	if(is_percent_ok(101)){
		std::cerr << "Error: is_percent_ok(101)=true\n";
	}

	if(is_percent_ok(100.001)){
		std::cerr << "Error: is_percent_ok(100.001)=true\n";
	}

	if(!is_percent_ok(0)){
		std::cerr << "Error: is_percent_ok(0)=false\n";
	}

	if(!is_percent_ok(0.00)){
		std::cerr << "Error: is_percent_ok(0.00)=false\n";
	}

	if(!is_percent_ok(10)){
		std::cerr << "Error: is_percent_ok(10)=false\n";
	}

	if(!is_percent_ok(100)){
		std::cerr << "Error: is_percent_ok(100)=false\n";
	}

	if(!is_percent_ok(100.00)){
		std::cerr << "Error: is_percent_ok(100.00)=false\n";
	}

}
/**
 * @brief A function that prints out a taxation table. 
 */
void build_table(){
	std::cout << "INPUT PART" << std::endl;
	std::cout << "==========" << std::endl;

	bool input_ok{false};

	float first_price{};
	do{
		std::cout << "Enter first price: ";
		std::cin >> first_price;
		input_ok = is_first_price_ok(first_price);
		
		if(!input_ok){
			std::cerr << "ERROR: First price must be between 0 " 
					  << "and 100,000.00 SEK\n";
		}
	}while(!input_ok);

	input_ok = false;

	float last_price{};
	do{
		std::cout << "Enter last price : ";
		std::cin >> last_price;
		input_ok = is_last_price_ok(first_price, last_price);
		
		if(!input_ok){
			std::cerr << "ERROR: Last price must be greater than " 
					  << first_price
					  << " and at most 100,000.00 SEK\n";
		}
	}while(!input_ok);

	input_ok = false;

	float stride{};
	do{
		std::cout << "Enter stride     : ";
		std::cin >> stride;
		input_ok = is_stride_ok(stride, first_price, last_price);

		if(!input_ok){
			std::cerr << "ERROR: Stride must be between 0.01 and " 
					  << last_price - first_price << "\n";
		}
	}while(!input_ok);

	input_ok = false;
	
	float percent{};
	do{
		std::cout << "Enter tax percent: ";
		std::cin >> percent;
		input_ok = is_percent_ok(percent);

		if(!input_ok){
			std::cerr << "ERROR: Percent must be between 0 and 100\n";
		}
	}while(!input_ok);

	int i{0};
	float price{first_price};
	float p{percent / 100};

	std::cout << "\nTAX TABLE\n";
	std::cout << "=========\n";
	std::cout << std::setw(12) << "Price" 
			  << std::setw(16) << "Tax" 
			  << std::setw(21) << "Price with tax\n";
	std::cout << std::setfill('-') << std::setw(49) << "\n";
	std::cout << std::fixed;


	while(price <= last_price){
		std::cout << std::setfill(' ')
				  << std::setw(12) << std::setprecision(2) << price
				  << std::setw(16) << std::setprecision(2) << p * price 
				  << std::setw(20) << std::setprecision(2) << (p + 1) * price
				  << "\n";

		i++;
		price = first_price + i * stride;
	}

}

// ================== END OF FILE ==================
