#pragma once
#include <iostream>
using namespace std;

class Driver {
private:
	string* id = NULL;
	int* m_over_speed = NULL;
	double* m_dist = NULL;
	int counter = 0;
	int *cluster;
public:

	Driver(int size) {
		id = new string[size];
		m_dist = new double[size];
		m_over_speed = new int[size];
		cluster = new int[size];
		counter = 0;
	}



	void readFile(string path) {


		fstream DriverFile;
		DriverFile.open(path);

		if (DriverFile.fail()) {
			cout << "Unable to open File";
			return;
		}


		string line = "", temp;
		getline(DriverFile, line);
		line = "";


		while (getline(DriverFile, line)) {

			stringstream data(line);

			getline(data, temp, ',');
			id[counter] = temp;

			getline(data, temp, ',');
			m_dist[counter] = atof(temp.c_str());


			getline(data, temp, ',');
			m_over_speed[counter] = atoi(temp.c_str());

			//cout << id[counter] << " : " << m_dist[counter] << " : " << m_over_speed[counter] << endl;

			counter++;

			line = "";
		}
	}


	void write_file() {
		ofstream file;
		file.open("Driver.csv");
		if (file.fail()) {
			cout << "Unable to open File";
			return;
		}
		file << "id" << ',' << "mean_dist_day"<<','<<"mean_over_speed_perc"<<','<<"cluster" << endl;

		for (int i = 0; i < counter; i++)
		{
			file << id[i] << ',' << m_dist[i] << ',' <<m_over_speed[i] << ',' <<cluster[i] << endl;
		}
		

		file.close();
	}


	bool search(string id) {
		for (int i = 0; i <= counter; i++) {
			if (this->id[i] == id) {
				cout << "Found\n";
				return true;
			}
		}
		cout << "Not fount\n";
		return false;
	}
	void remove(string id) {
		for (int i = 0; i <= counter; i++) {
			if (this->id[i] == id) {
				for (int j = i; j < counter; j++) {
					this->id[j] = this->id[j + 1];
				}
				for (int j = i; j < counter; j++) {
					this->m_dist[j] = this->m_dist[j + 1];
				}
				for (int j = i; j < counter; j++) {
					this->m_over_speed[j] = this->m_over_speed[j + 1];
				}

				counter--;
				cout << "Done";

				break;
			}

		}
		cout << "Didn't found.";

	}


	void print() {
		for (int i = 0; i < counter; i++) {
			cout << "\n\n\nDriver id: " << id[i] << "\nDriver's mean distant: " << m_dist[i] << "\nDriver's mean over Speed: " << m_over_speed[i] << "\n\nCluster: " << cluster[i]<<endl;
		}
	}


	void find_centroid(double dist_min, double dist_max, int speed_min, int speed_max) {

		const int k=4;	// num_of_culster
		double min_dist;
		double dist_centroid[k];
		double speed_centroid[k];
		double distance[k];
		double sum_dist[k] = {0};
		double sum_over_speed[k] = {0};	//summing all the over speed then divide to find centroid
		int no_clusters[k]={0};	//number of points in cluster
		bool flag = false;	//Flag to check if the the centroid is changed or not 

		srand(time(NULL));
		for (int i = 0; i < k; i++) {
			dist_centroid[i] = (rand() % int(dist_max-dist_min+1)) + dist_min;
			
			speed_centroid[i] = (rand() % speed_max-speed_min+1) + speed_min;
		}
		double temp_dist_centroid[k];
		double temp_speed_centroid[k];
		

		do{
			for (int i = 0; i < k; i++)
			{
				temp_dist_centroid[i] = dist_centroid[i];
				temp_speed_centroid[i] = speed_centroid[i];
			}

			for (int i = 0; i < k; i++)
			{

				cout << "Distance cluster is: " << dist_centroid[i] << " over speed cluster is : " << speed_centroid[i]<<endl;
			}
			cout << "\n";

			for (int i = 0; i < counter; i++) {
				for (int j = 0; j < k; j++) {
					distance[j] = sqrt(pow((m_dist[i] - dist_centroid[j]), 2) + pow((m_over_speed[i] - speed_centroid[j]), 2));
				}

				min_dist = distance[0];
				cluster[i] = 0;
				for (int l = 1; l < k; l++) {
					if (min_dist > distance[l]) {
						min_dist = distance[l];
						cluster[i] = l;

					}

				}

				//cout << "\nmin distance is :" << min_dist << "\nWith cluster : " << cluster[i] << endl;
			}


			for (int i = 0; i < counter; i++) {

				for (int j = 0; j < k; j++) {
					if (cluster[i] == j) {
						sum_dist[j] += m_dist[i];
						sum_over_speed[j] += m_over_speed[i];
						no_clusters[j]++;
					}
				}

			}

			for (int i = 0; i < k; i++)
			{
				dist_centroid[i] = sum_dist[i] / no_clusters[i];
				speed_centroid[i] = sum_over_speed[i] / no_clusters[i];
			}



			for (int i = 0; i < k; i++)		//set all 0 to set for another centroid
			{
				sum_dist[i] = 0;
				no_clusters[i] = 0;
				sum_over_speed[i] = 0;
				/*cout << "sum_dist and speed :" << sum_dist[i] << " : " << sum_over_speed[i] << endl;
				cout<<"no of clusters "<<no_clusters[i]<<endl;*/
			}
			flag = false;
			for (int i = 0; i < k; i++)
			{
				if (temp_dist_centroid[i] != dist_centroid[i] || temp_speed_centroid[i] != speed_centroid[i]) {
					flag = true;
				}
			}
			//cout << "\nflag : " << flag << endl;
		} while (flag);

	}



	void find_min_max(double& dist_min, double& dist_max, int& speed_min, int& speed_max) {


		 dist_max = m_dist[0];
		 dist_min = m_dist[0];
		 speed_min = m_over_speed[0];
		 speed_max = m_over_speed[0];
		for (int i = 1; i < counter; i++) {
			if (m_dist[i] > dist_max) {
				dist_max = m_dist[i];
			}
			if (m_dist[i] < dist_min) {
				dist_min= m_dist[i];
			}
			if (m_over_speed[i] > speed_max) {
				speed_max = m_over_speed[i];
			}
			if (m_over_speed[i] < speed_min) {
				speed_min = m_over_speed[i];
			}

		}

	}
};



int calculateSize(string path) {

	fstream DriverFile;
	DriverFile.open(path);

	if (DriverFile.fail()) {
		cout << "Unable to open File";
		return 0;
	}
	int size = 0;
	string line = "";
	getline(DriverFile, line);
	line = "";
	while (getline(DriverFile, line)) {
		size++;
		line = "";
	}
	DriverFile.close();

	return size;

}

