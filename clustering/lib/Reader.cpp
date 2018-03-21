#include"Reader.h"

//仅依据不包含数字、小数点来判断
bool static NotPureNumber(const string&);
bool static PureNumber(const char&);

AroyaReader::AroyaReader() {
	//nothing to do yet
}

void AroyaReader::read(const char*fileName) {
	ifstream fin;
	fin.open(fileName);
	if (!fin.is_open()) {
		cout << "AroyaReader:read() cannot open file!\n";
		system("pause");
	}
	char reading;
	string buffer;
	bool didntInit = true;
	vector<string>emptyVector;
	int nowPoint = 0;
	while (fin.good() && (reading = fin.get()) != -1) {
		//数据结束 处理数据
		if (reading == ',' || reading == '\n') {
			if (didntInit) {					//init this row
				data.push_back(emptyVector);
				didntInit = false;
			}
			data[nowPoint].push_back(buffer);	//put data to this row

			buffer.clear();						//clear buffer
			if (reading == '\n') {				//next row
				nowPoint++;
				didntInit = true;
			}
		}
		//无分隔符 记录数据
		else {
			buffer.push_back(reading);
		}
	}
	fin.close();
}

string AroyaReader::getStringData(const int&rows, const int&columns) {
	return data[rows][columns];
}

double AroyaReader::getDoubleData(const int&rows, const int&columns) {
	internalSst.str("");
	internalSst.clear();
	internalSst << data[rows][columns];
	double temp;
	internalSst >> temp;
	return temp;
}

int AroyaReader::findTable(const char*tableName) {
	int tables = data[0].size();
	for (int i = 0; i < tables; i++) {
		if (data[0][i] == tableName)return i;
	}
	cout << "Cannot find " << tableName << endl;
	return -1;
}
int AroyaReader::getRows() { return data.size(); }
int AroyaReader::getColumns() { return data[0].size(); }
static bool NotPureNumber(const string&str) {
	int i, l = str.length();
	char left = '0' - 1, right = '9' + 1;
	bool point = true;
	for (i = 0; i < l; i++) {
		if (point&& str[i] > left &&str[i] < right) {
			if (str[i] == ',')point = false;
		}
		else return true;
	}
	return false;
}
bool static PureNumber(const char&t) {
	return t >= '0'&&t <= '9';
}

void AroyaReader::setTableName(const char*origin, const char*new_) {
	data[0][findTable(origin)] = new_;
}
void AroyaReader::deleteColumn(const int&col) {
	int rows = getRows();
	for (int i = 0; i < rows; i++) {
		data[i].erase(data[i].begin() + col);
	}
}
void AroyaReader::deleteRow(const int&row) {
	data.erase(data.begin() + row);
}

void AroyaReader::deleteRows(const char*TableName, const char*DataType) {
	int column = findTable(TableName);
	int i, j = getRows();
	for (i = 1; i < j; i++) {
		if (data[i][column] == DataType) {
			deleteRow(i);
			i--;
			j = getRows();
		}
	}
}

void writeFile(double**data, const char*fileName, const int&rows, const int&cols) {

	ofstream fout;
	fout.open(fileName);
	if (fout.is_open()) {
		int i, j;
		bool notFirst;
		for (i = 0; i < rows; i++) {
			notFirst = false;
			for (j = 0; j < cols; j++) {
				if (notFirst) {
					fout << ',' << data[i][j];
				}
				else {
					fout << data[i][j];
					notFirst = true;
				}
			}
			fout << endl;
		}
	}
	else {
		printf("writeFile()cannot write %s\n", fileName);
	}
}