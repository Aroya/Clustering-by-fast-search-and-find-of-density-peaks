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
	linkPointerBase = new Link[rows*(rows - 1)];//������Ԫ������
	density = new int[rows];
	cluster = new int[rows];
	//init data
	for (i = 0; i < rows; i++) {
		density[i] = 0;
		cluster[i] = -1;
	}
	clusters = 0;

	//�ȼ������е�֮��ľ���
	for (i = 0; i < rows; i++) {
		for (j = i + 1; j < rows; j++) {
			temp = 0;
			for (k = 0; k < columns; k++) {
				temp += pow(data[i][k] - data[j][k], 2);
			}
			temp = sqrt(temp);
			//�����㹻��ʱ����������
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
	
	//ͳ�ƽ�ȡ��������ΪDensity
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

	//Ϊ-1Ϊδ����
	//-2Ϊ������
	//���ҷ�Χ����û�и����ܶȵ㣬�ҵ�����ĸ��ܶȵ㣬�������ܶȵ�δ��ǣ�����
	//for (i = 0; i < rows; i++) {
	//	Link*pt = (distance + i)->next;
	//	while (pt&&!density[pt->index]>density[i]) {
	//		pt = pt->next;
	//	}
	//	//situation1:�ҵ��ĵ�Ϊ�����ܶȵ�
	//	if (pt) {
	//		if (cluster[pt->index] < 0) {
	//			cluster[pt->index] = clusters++;
	//		}
	//		//����
	//		//return cluster[pt->index];
	//	}
	//	//situation2:δ�ҵ�:��ǰ��Ϊ����ܶȵ�
	//	else {
	//		cluster[i] = clusters++;
	//		//����
	//		//return cluster[i];
	//	}
	//}
	//��дΪ�ǵݹ��㷨
	stack<int>waitingIndex;
	for (i = 0; i < rows; i++) {
		waitingIndex.push(i);
		k = -1;
		while (!waitingIndex.empty() && k == -1) {
			//���ص�ǰջ��Ԫ��
			j = waitingIndex.top();
			//�жϵ�ǰ���Ƿ��ѷ���
			if (!(cluster[j] < 0)) {
				k = cluster[j];
				continue;
			}
			//�жϵ�ǰ�Ƿ�Ϊ����ܶȵ�
			//�����Ҽ���
			Link*pt = (distance + j)->next;
			//������ĸ����ܶȵ�
			while (pt && !(density[pt->index] > density[j])) {
				pt = pt->next;
			}
			//situation1:�ҵ��ĵ�Ϊ�����ܶȵ�
			if (pt) {
				//����
				waitingIndex.push(pt->index);
			}
			//situation2:δ�ҵ�:��ǰ��Ϊ����ܶȵ�
			else {
				if (cluster[j] == -1) {
					cluster[j] = clusters++;
				}
				k = cluster[j];
			}
		}
		//�ѷ��࣬������
		while (!waitingIndex.empty()) {
			cluster[waitingIndex.top()] = k;
			waitingIndex.pop();
		}
	}
	//����̳и����ܶȵ�ķ��࣬����
	//���ǵ������̷���/����������Ϣ��������ʹ�÷�����Ϣ���
	//������ߣ�����ܶȵ��ޱ�ǣ�����һ�����


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