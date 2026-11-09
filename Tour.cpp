#include"Tour.h"
#include<iostream>
#include"Graph.h"
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;
extern  CGraph m_Graph;

void CreatGraph()
{
    ifstream vexFile("Vex.txt");
    ifstream edgeFile("Edge.txt");

    if (!vexFile.is_open() || !edgeFile.is_open())
    {
        cout << "文件打开失败" << endl;
    }

    Vex vex;
    Edge edge;
    int number;
   
    m_Graph.Init();
    vexFile >> number;
    /*cout << "景点信息：" << endl;
    cout << "景点个数:" << number << endl;*/
    while (vexFile >> vex.num >> vex.name >> vex.des)
    {
       /* cout <<"景点编号: " << vex.num << ", 名字 : " << vex.name << ", 介绍 : " << vex.des << endl;*/
        m_Graph.InsertVex(vex);
    }

    cout << endl;

   /* cout << "道路信息：" << endl;*/
    while (edgeFile >> edge.vex1 >> edge.vex2 >> edge.weight)
    {
        /*cout << "边的第一个顶点: " << edge.vex1 << ", 第二个顶点: " << edge.vex2 << ", 权值: " << edge.weight << endl;*/
        m_Graph.InsertEdge(edge);
    }

    vexFile.close();
    edgeFile.close();
    
    cout << "= = = =创建景区景点图= = = =" << endl;
    cout << "顶点数目" << m_Graph.VexNum<<endl;
    cout << "-----顶点-----" << endl;
    for (int i = 0; i < m_Graph.VexNum; i++)
    {
        cout << m_Graph.Vexs[i].num << "-" << m_Graph.Vexs[i].name << endl;
    }

    cout << "----边----" << endl;
    for (int i = 0; i < m_Graph.VexNum; i++)
    {
        for (int j = i+1; j < m_Graph.VexNum; j++)
        {
            if (m_Graph.AdjMatrix[i][j] != 0)
            {
                cout << "<v" << i << ",v" << j << ">"<<" " << m_Graph.AdjMatrix[i][j] << endl;
            }
        }
    }
    cout << endl;
}

void GetSpotInfo()
{
    system("cls");
    cout << "= = = =查询景点信息= = = =" << endl;
    for (int i = 0; i < m_Graph.VexNum; i++)
    {
        cout << m_Graph.Vexs[i].num << "-" << m_Graph.Vexs[i].name << endl;
    }
    int order;
    cout << "请输入想要查询的景点编号:" << endl;
    cin >> order;
    if (order < 0 || order >= m_Graph.VexNum)
    {
        cout << "未查询到该景点信息，请检查您输入的编号" << endl;
    }
    cout << m_Graph.GetVex(order).name << endl;
    cout << m_Graph.GetVex(order).des << "."<<endl;

    cout << "----- 周边景区 -----" << endl;
    int a = 0;
    a = m_Graph.FindEdge(order);
    cout << "周边共有" << a << "个相邻景区可供游玩" << endl;
}

void TravelPath()
{
    int nVex = 0;
    PathList pList = nullptr;



    cout << "= = = = = 旅游景点导航 = = = = =" << endl;
    for (int i = 0; i < m_Graph.VexNum; i++)
    {
        cout << m_Graph.Vexs[i].num << "-" << m_Graph.Vexs[i].name << endl;
    }
    cout << "请输入起始编号:";
    cin >> nVex;

    m_Graph.DFSTraverse(nVex, pList);

    PathList p = pList;
    cout << "导游路线为:"<<endl;
    while (p!=nullptr)
    {
        for (int i = 0; i < m_Graph.VexNum; i++)
        {
            cout << m_Graph.Vexs[p->vexs[i]].name;
            if (i < m_Graph.VexNum - 1)
                cout << "->";
        }
        cout << endl;
        p = p->next;
    }
}

void FindShortPath()
{
    int Start, End,result;
    cout << "= = = = 搜索最短路径 = = = =" << endl;
    for (int i = 0; i < m_Graph.VexNum; i++)
    {
        cout << m_Graph.Vexs[i].num << "-" << m_Graph.Vexs[i].name << endl;
    }
    cout << "请输入起始点编号:";
    cin >> Start;
    cout << endl;
    cout << "请输入目的点编号:";
    cin >> End;
    cout << endl;

    Edge aPath[20];

    for (int i = 0; i < m_Graph.VexNum; i++)
    {
        aPath[i].vex1 = 0;
        aPath[i].vex2 = 0;
        aPath[i].weight = 0;
    }

    int index = FindShortPath(Start, End, aPath);
    int length = 0;
    Vex nVex = m_Graph.GetVex(aPath[0].vex1);

    cout << endl;
    cout << "最短路径为：" << nVex.name;

    for (int i = 0; i < m_Graph.VexNum; i++)
    {
        nVex = m_Graph.GetVex(aPath[i].vex2);
        if(aPath[i].vex2!=0)
        cout << "->" << nVex.name;
        length += aPath[i].weight;
    }

    cout << endl;
    cout << "最短距离为:" << length << "米" << endl;

}

void DesignPath()
{
    cout << "在以下两个景点之间铺设电路";
    cout << "\n=======铺设电路规划=======" << endl;

    Edge aPath[20];

    FindMinTree(aPath); // 构建最小树

    int nVexNum = m_Graph.VexNum;

    if (nVexNum == 0)
    {
        cout << "请先创建图！" << endl;
        return;
    }
 
    // 输出铺设线路图
    int nAllLength = 0;

    for (int i = 0; i < m_Graph.VexNum - 1; i++)
    {
        Vex nVex1 = m_Graph.GetVex(aPath[i].vex1);
        Vex nVex2 = m_Graph.GetVex(aPath[i].vex2);

        cout << "\t" << nVex1.name << "-" << nVex2.name << ":" << aPath[i].weight << "m" << endl;
        nAllLength += aPath[i].weight;
    }
    cout << "==========================\n";
    cout << "铺设电路的总长度是：" << nAllLength << "m" << endl
        << endl;
}

