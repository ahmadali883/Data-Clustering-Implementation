#pragma once
#include <iostream>
using namespace std;
//segmented_customers-1
class Customers {
private:
	int* id = NULL;
	int* spending_p=NULL;
	string* gender = NULL;
	int* age = NULL;
	int* annual_income= NULL;
	int counter = 0;
	int* cluster;
public:

	Customers(int size) {
		id = new int[size];
		gender = new string[size];
		age = new int[size];
		annual_income = new int[size];
		spending_p = new int[size];
		cluster = new int[size];
		counter = 0;
	}



	void readFile(string path) {


		fstream CustomersFile;
		CustomersFile.open(path);

		if (CustomersFile.fail()) {
			cout << "Unable to open File";
			return;
		}

		string line = "", temp;
		getline(CustomersFile, line);
		line = "";

		
		//cout << "PATH :" << path;
		while (getline(CustomersFile, line)) {
			
			stringstream data(line);

			getline(data, temp, ',');
			id[counter] = atoi(temp.c_str());
			//cout << "Id :" << id[counter] << " : " << temp<<endl;
			getline(data, temp, ',');
			gender[counter] = temp;

			
			getline(data, temp, ',');
			age[counter] = atoi(temp.c_str());

			getline(data, temp, ',');
			annual_income[counter] = atoi(temp.c_str());

			getline(data, temp, ',');
			
			spending_p[counter] = atoi(temp.c_str());
			//cout << "File Opend and counter is :" << counter << endl;
			//cout << id[counter] << " : " << gender[counter] << " : " << age[counter]<<" : "<<annual_income[counter]<<" : "<<spending_p[counter] << endl;
			//cout << "Counter: " << counter << endl;
			counter++;

			line = "";
		}
	}

	void write_file() {
		ofstream file;
		file.open("customers.csv");
		if (file.fail()) {
			cout << "Unable to open File";
			return;
		}
		file << "customer" << ',' << "Gender" << ',' << "Age" << ','<<"Annual Income" << ',' << "Sending Power" <<',' << "Cluster" << endl;

		for (int i = 0; i < counter; i++)
		{
			file << id[i] << ',' << gender[i] << ',' << age[i] << ','<<annual_income[i] << ',' << spending_p[i]<<',' << cluster[i] << endl;
		}


		file.close();
	}
	  
//
//
//	bool search(string id) {
//		for (int i = 0; i <= counter; i++) {
//			if (this->id[i] == id) {
//				cout << "Found\n";
//				return true;
//			}
//		}
//		cout << "Not fount\n";
//		return false;
//	}
//	void remove(string id) {
//		for (int i = 0; i <= counter; i++) {
//			if (this->id[i] == id) {
//				for (int j = i; j < counter; j++) {
//					this->id[j] = this->id[j + 1];
//				}
//				for (int j = i; j < counter; j++) {
//					this->m_dist[j] = this->m_dist[j + 1];
//				}
//				for (int j = i; j < counter; j++) {
//					this->m_over_speed[j] = this->m_over_speed[j + 1];
//				}
//
//				counter--;
//				cout << "Done";
//
//				break;
//			}
//
//		}
//		cout << "Didn't found.";
//
//	}
//
//
	void print() {
		for (int i = 0; i < counter; i++) {
			cout << "\n\n\nCustomer id: " << id[i] << "\nCustomer gernder: " << gender[i] << "\nCustomer Age: " << age[i] << "\nCustomer annual income : "<<annual_income[i]<<"\nCusomer spending Power:"<<spending_p[i] << endl;
		}
	}
//

	void find_centroid(int annual_income_min, int annual_income_max, int age_min, int age_max, int spending_p_min, int spending_p_max) {

		const int k = 4;	// num_of_culster
		double min_dist;	//min distance between the points.
		double age_centroid[k];	
		double annual_income_centroid[k];
		double spending_p_centroid[k];
		double distance[k];		//distance between the points.
		double sum_age_centroid[k] = { 0 };		//sum of ages in a particular clusters
		double sum_spendng_p[k] = { 0 };	//summing all the spending power then divide to find centroid
		double sum_annual_income[k] = { 0 };	//summing all the annual incomes then divide to find centroid
		double no_clusters[k] = { 0 };	//number of points in cluster
		bool flag = false;	//Flag to check if the the centroid is changed or not 

		srand(time(NULL));
		for (int i = 0; i < k; i++) {
			age_centroid[i] = (rand() % age_max-age_min+1) + age_min;
			annual_income_centroid[i] = (rand() % annual_income_max-annual_income_min+1) + annual_income_min;
			spending_p_centroid[i] = (rand() % spending_p_max-spending_p_min+1) + spending_p_min;
			// 11 + rand() % (34 - 11 + 1);
		}

		double temp_age_centroid[k];	//to check weither the centroid is  changed or not
		double temp_income_centroid[k];
		double temp_spending_centroid[k];


		do {
			for (int i = 0; i < k; i++)
			{
				temp_age_centroid[i] = age_centroid[i];	//to check weither the centroid is  changed or not
				temp_income_centroid[i]= annual_income_centroid[i];
				temp_spending_centroid[i]= spending_p_centroid[i];

			}

			for (int i = 0; i < k; i++)
			{

				cout << "Age cluster is: " << age_centroid[i] << " annual income cluster is : " << annual_income_centroid[i]<<" Spending power cluster :"<<spending_p_centroid[i] << endl;
			}
			cout << "\n";

			for (int i = 0; i < counter; i++) {
				for (int j = 0; j < k; j++) {
					distance[j] = sqrt(pow((age[i] - age_centroid[j]), 2) + pow((annual_income[i] - annual_income_centroid[j]), 2) + pow((spending_p[i] - spending_p_centroid[j]), 2));
					
				}

				min_dist = distance[0];
				
				cluster[i] = 0;
				for (int l = 1; l < k; l++) {
					if (min_dist > distance[l]) {
						min_dist = distance[l];
						cluster[i] = l;

					}

				}
				for (int o = 0; o < k; o++)
				{

					//cout << "Distance :" << distance[o] << endl;
				}

				//cout << "\nmin distance is :" << min_dist << "\nWith cluster : " << cluster[i] << endl;
			}


			for (int i = 0; i < counter; i++) {

				for (int j = 0; j < k; j++) {
					if (cluster[i] == j) {
						sum_age_centroid[j] += age[i];
						sum_annual_income[j] += annual_income[i];
						sum_spendng_p[j] += spending_p[i];
						no_clusters[j]++;
					}
				}

			}

			for (int i = 0; i < k; i++)
			{
				age_centroid[i] = sum_age_centroid[i] / no_clusters[i];
				//cout << "the age cluster changed to : "<<age_cluster[i]<<endl;
				annual_income_centroid[i] = sum_annual_income[i] / no_clusters[i];

				
				//cout << "the income cluster changed to : " << annual_income_cluster[i] << endl;
				spending_p_centroid[i] = sum_spendng_p[i] / no_clusters[i];


				//cout << "the spending cluster changed to : " << spending_p_cluster[i] << endl;
			}



			for (int i = 0; i < k; i++)		//set all 0 to set for another centroid
			{
				sum_age_centroid[i] = 0;
				no_clusters[i] = 0;
				sum_annual_income[i] = 0;
				sum_spendng_p[i] = 0;
				/*cout << "sum_dist and speed :" << sum_dist[i] << " : " << sum_over_speed[i] << endl;
				cout<<"no of clusters "<<no_clusters[i]<<endl;*/
			}
			flag = false;
			for (int i = 0; i < k; i++)
			{
				if (temp_age_centroid[i] != age_centroid[i] || temp_income_centroid[i] != annual_income_centroid[i] || temp_spending_centroid[i] != spending_p_centroid[i]) {
					flag = true;
				}
			}
			//cout << "\nflag : " << flag << endl;
		} while (flag);

	}



	void find_min_max(int &annual_income_min, int& annual_income_max, int& age_min, int& age_max) {


		annual_income_max = annual_income[0];
		annual_income_min = annual_income[0];
		age_min = age[0];
		age_max = age[0];
		
		for (int i = 1; i < counter; i++) {
			if (annual_income[i] > annual_income_max) {
				annual_income_max = annual_income[i];
			}if (annual_income[i] < annual_income_min) {
				annual_income_min = annual_income[i];
			}
		
			if (age_max > age[i]) {
				age_max = age[i];
			}
			if (age_min < age[i]) {
				age_min = age[i];
			}

		}

	}
};



int calculateSize_customers(string path) {

	fstream CustomersFile;
	CustomersFile.open(path);

	if (CustomersFile.fail()) {
		cout << "Unable to open File";
		return 0;
	}
	int size = 0;
	string line = "";
	getline(CustomersFile, line);
	line = "";
	while (getline(CustomersFile, line)) {
		size++;
		line = "";
	}
	CustomersFile.close();

	return size;

}

