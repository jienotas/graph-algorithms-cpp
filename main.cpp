#include <iostream>
#include<stdlib.h>
#include"Graph.h"
#include"Tour.h"
using namespace std;
CGraph m_Graph;
int main()
{
	int choice ;
	while (true)
	{
		cout << "= = = =景区信息管理系统= = = =" << endl;
		cout << "1.创建景区景点图" << endl;
		cout << "2.查询景区信息" << endl;
		cout << "3.旅游景点导航" << endl;
		cout << "4.搜索最短路径" << endl;
		cout << "5.铺设电路规划" << endl;
		cout << "0.退出" << endl;

		cout << "请输入操作编号<1-5>:" << endl;
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1: CreatGraph(); break;
		case 2:	GetSpotInfo(); break;
		case 3: TravelPath(); break;
		case 4: FindShortPath(); break;
		case 5:DesignPath(); break;
		default:
			break;
		}

		if (choice == 0) 
		{
			break;
		}
	}
	return 0;
}