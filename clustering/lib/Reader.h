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
	vector<vector<string>>data;		//ȫ����string�ݴ�
	stringstream internalSst;		//ת��ʹ��
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
	//��ֵ����:ɾ����ֵ����ɾ���к���
	void deleteRow(const int&row);
	//ɾ���ض�����
	void deleteRows(const char*TableName, const char*DataType);
};

void writeFile(double**, const char*fileName, const int&rows, const int&cols);

#endif