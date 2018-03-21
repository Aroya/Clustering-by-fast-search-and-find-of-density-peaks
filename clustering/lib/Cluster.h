#ifndef AROYA_CLUSTER
#define AROYA_CLUSTER

#include<stack>
#include<string>
#include<fstream>
#include"Reader.h"
using namespace std;



class Cluster {
public:
	Cluster();
	//one row per tuple
	void input(double**Data, const int&Rows, const int&Columns);
	void setMaximumDistance(const double&Distance);
	void writeFile(const string&filename);
	void clustering();
private:
	int rows, columns;
	double **data;

	//聚类结果
	int *cluster;
	//最小距离
	double distance_maximum;
	int clusters;
};

#endif