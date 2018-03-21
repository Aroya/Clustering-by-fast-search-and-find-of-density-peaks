#include"Cluster.h"
#include<algorithm>
using namespace std;

static struct Link {
	double dis;
	int index;
	Link*next;
	Link() {
		dis = DBL_MAX;
		index = -1;
		next = nullptr;
	}
};
static void LinkOrderedInsert(Link*Base, Link*New) {
	Link*now = Base;
	while (now->next) {
		if (now->next->dis < New->dis) {
			now = now->next;
		}
		else {
			New->next = now->next;
			now->next = New;
			break;
		}
	}
	if (!now->next) {
		now->next = New;
	}
}

Cluster::Cluster() {
	rows = 0;
	columns = 0;
	data = nullptr;
	distance_maximum = 10;
	clusters = 0;
}

void Cluster::input(double ** Data, const int & Rows, const int & Columns){
	rows = Rows;
	columns = Columns;
	data = Data;
}
void Cluster::setMaximumDistance(const double&t) {
	distance_maximum = t;
}

void Cluster::writeFile(const string & fileName)
{
	ofstream fout;
	fout.open(fileName);
	if (fout.is_open()) {
		int i;
		for (i = 0; i < rows; i++) {
			fout << cluster[i] << endl;
		}
	}
	else {
		printf("writeFile()cannot write %s\n", fileName);
	}
}

void Cluster::clustering() {
	int i, j, k;
	double temp;
	//define data
	if (cluster) {
		delete[]cluster;
	}
	int *density;
	Link*distance;				//link list; ordered insert
	Link*linkPointerBase;		//save all pointer, easy to delete
	int links = 0;				//counter
	//init space
	distance = new Link[rows];
	linkPointerBase = new Link[rows*(rows - 1)];//最坏情况的元素数量
	density = new int[rows];
	cluster = new int[rows];
	//init data
	for (i = 0; i < rows; i++) {
		density[i] = 0;
		cluster[i] = -1;
	}
	clusters = 0;

	//先计算所有点之间的距离
	for (i = 0; i < rows; i++) {
		for (j = i + 1; j < rows; j++) {
			temp = 0;
			for (k = 0; k < columns; k++) {
				temp += pow(data[i][k] - data[j][k], 2);
			}
			temp = sqrt(temp);
			//距离足够近时，插入排序
			if (temp < distance_maximum) {
				linkPointerBase[links].index = j;
				linkPointerBase[links].dis = temp;
				LinkOrderedInsert(distance + i, linkPointerBase + links);
				links++;

				linkPointerBase[links].index = i;
				linkPointerBase[links].dis = temp;
				LinkOrderedInsert(distance + j, linkPointerBase + links);
				links++;
			}
		}
	}
	
	//统计截取的链表长度为Density
	for (i = 0; i < rows; i++) {
		j = 0;
		Link*pt = distance + i;
		pt = pt->next;
		while (pt) {
			j++;
			pt = pt->next;
		}
		density[i] = j;
	}

	//为-1为未分类
	//-2为噪音点
	//查找范围内有没有更高密度点，找到最近的高密度点，若更高密度点未标记，迭代
	//for (i = 0; i < rows; i++) {
	//	Link*pt = (distance + i)->next;
	//	while (pt&&!density[pt->index]>density[i]) {
	//		pt = pt->next;
	//	}
	//	//situation1:找到的点为更大密度点
	//	if (pt) {
	//		if (cluster[pt->index] < 0) {
	//			cluster[pt->index] = clusters++;
	//		}
	//		//迭代
	//		//return cluster[pt->index];
	//	}
	//	//situation2:未找到:当前点为最大密度点
	//	else {
	//		cluster[i] = clusters++;
	//		//迭代
	//		//return cluster[i];
	//	}
	//}
	//改写为非递归算法
	stack<int>waitingIndex;
	for (i = 0; i < rows; i++) {
		waitingIndex.push(i);
		k = -1;
		while (!waitingIndex.empty() && k == -1) {
			//加载当前栈顶元素
			j = waitingIndex.top();
			//判断当前点是否已分类
			if (!(cluster[j] < 0)) {
				k = cluster[j];
				continue;
			}
			//判断当前是否为最大密度点
			//向后查找加载
			Link*pt = (distance + j)->next;
			//找最近的更大密度点
			while (pt && !(density[pt->index] > density[j])) {
				pt = pt->next;
			}
			//situation1:找到的点为更大密度点
			if (pt) {
				//迭代
				waitingIndex.push(pt->index);
			}
			//situation2:未找到:当前点为最大密度点
			else {
				if (cluster[j] == -1) {
					cluster[j] = clusters++;
				}
				k = cluster[j];
			}
		}
		//已分类，逐个标记
		while (!waitingIndex.empty()) {
			cluster[waitingIndex.top()] = k;
			waitingIndex.pop();
		}
	}
	//否则继承更高密度点的分类，跳出
	//考虑迭代过程返回/保留分类信息，跳出后使用分类信息标记
	//若到最高，最高密度点无标记，分配一个标记


	//clear data
	delete[]distance;
	delete[]linkPointerBase;
	if (data) {
		for (int i = 0; i < rows; i++) {
			delete[]data[i];
		}
		delete[]data;
	}
	if (density) {
		delete[]density;
	}
}