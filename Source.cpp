#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
//#include <amp_graphics.h>
#include "Task_1.h"
#include "Task_2.h"

using namespace std;




int main() {

	string path_driver = "driver-data.csv",path_customers="segmented_customers-1.csv";
	double dist_min, dist_max;
	int speed_min, speed_max;
	
	int size= calculateSize(path_driver);

	Driver driver(size);
	driver.readFile(path_driver);
	driver.find_min_max(dist_min,  dist_max,  speed_min, speed_max);
	
	driver.find_centroid(dist_min, dist_max, speed_min, speed_max);
	driver.write_file();

	////driver.print();

	///////////////----------Task-2---------------\\\\\\\\\\\\\\\\\


	 
	int annual_income_min, annual_income_max, age_min, age_max,spending_p_min=0,spending_p_max=100;

	int size1 = calculateSize_customers(path_customers);
	Customers customer(size1);
	customer.readFile(path_customers);
	customer.find_min_max(annual_income_min, annual_income_max, age_min, age_max);
	customer.find_centroid(annual_income_min, annual_income_max, age_min, age_max, spending_p_min, spending_p_max);
	customer.write_file();
	//customer.print();


		cout << "\nENDED";

	return 0;

}
