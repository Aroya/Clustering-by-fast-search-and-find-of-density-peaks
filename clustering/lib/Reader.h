#ifndef	Aroya_READER
#define Aroya_READER

#include<string>
#include<vector>
#include<fstream>
#include<iostream>
#include<sstream>
using namespace std;

class AroyaReader {
private:
	vector<vector<string>>data;		//全部以string暂存
	stringstream internalSst;		//转换使用
public:
	AroyaReader();
	void read(const char*fileName);
	string getStringData(const int&rows, const int&columns);
	double getDoubleData(const int&rows, const int&columns);
	int findTable(const char*tableName);
	int getRows();
	int getColumns();
	void setTableName(const char*origin, const char*new_);
	void deleteColumn(const int&col);
	//空值处理:删除空值行用删除行函数
	void deleteRow(const int&row);
	//删除特定数据
	void deleteRows(const char*TableName, const char*DataType);
};

void writeFile(double**, const char*fileName, const int&rows, const int&cols);

#endif