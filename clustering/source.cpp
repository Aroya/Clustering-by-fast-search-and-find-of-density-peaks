#include<iostream>
#include"lib\Reader.h"
#include"lib\ReaderHelper.h"
#include"lib\Cluster.h"
using namespace std;
int main() {
	AroyaReader reader;
	reader.read("examples/example0.csv");
	AroyaReaderHelper helper;
	helper.insert(reader, "x");
	helper.insert(reader, "y");

	Cluster cluster;
	cluster.setMaximumDistance(0.6);

	cluster.input(helper.getDataPointer(), helper.getRows(), helper.getColumns());
	cluster.clustering();
	cluster.writeFile("output/example0.csv");
	return 0;
}