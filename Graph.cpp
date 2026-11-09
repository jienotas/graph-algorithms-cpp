#include"Graph.h"
#include <iostream>
#define INF 0x7FFFFFFF
using namespace std;
extern CGraph m_Graph;
void CGraph :: Init()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			AdjMatrix[i][j] = 0;
		}
	}
	VexNum = 0;
}

bool CGraph::InsertVex(Vex V)
{
	if (VexNum == 20)
	{
		return false;
	}
	Vexs[VexNum++] = V;
	return true;
}

bool CGraph::InsertEdge(Edge E)
{
	if (E.vex1 < 0 || E.vex1 >= 20 || E.vex2 < 0 || E.vex2 >= 20)
	{
		return false;
	}

	AdjMatrix[E.vex1][E.vex2] = E.weight;
	AdjMatrix[E.vex2][E.vex1] = E.weight;
}

Vex CGraph::GetVex(int v)
{
	return Vexs[v];
}

int CGraph::FindEdge(int v)
{
	int cnt = 0;
	for (int i = 0; i < VexNum; i++)
	{
		if (AdjMatrix[v][i] != 0)
		{
			cout << Vexs[v].name << "->" << Vexs[i].name  << " " << AdjMatrix[v][i] << "米" << endl;
			cnt++;
		}
	}
	return cnt;
}

void CGraph::DFS(int nVex, bool bVisted[], int& nIndex, PathList& pList)
{
	bVisted[nVex] = true;
	pList->vexs[nIndex++] = nVex;

	if (nIndex == VexNum)
	{
		PathList newPath = new Path;
		for (int i = 0; i < VexNum; i++)
		{
			newPath->vexs[i] = pList->vexs[i];
		}
		newPath->next = pList->next;
		pList->next = newPath;
	}

	for (int i = 0; i < VexNum; i++)
	{
		if (AdjMatrix[nVex][i] != 0 && !bVisted[i])
		{
			DFS(i, bVisted, nIndex, pList);
		}
	}

	bVisted[nVex] = false;
	nIndex--;
}

void CGraph::DFSTraverse(int nVex, PathList& pList)
{
	bool bVisted[20] = { false };
	int nIndex = 0;
	PathList head = new Path;
	head->next = nullptr;
	DFS(nVex, bVisted, nIndex, head);

	pList = head->next;
}

int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
	int nShortPath[20][20]; // 最短路径，行表示终点，列表示从起点到终点的最短路径的每一步
	int nShortDistance[20]; // 保存从起点到任一顶点的最短距离
	bool aVisited[20];		// 判断某点是否已在最短路径中
	int v;					// 每一次找到的可以加入集合的顶点

	// 初始化
	for (v = 0; v < m_Graph.VexNum; v++)
	{
		aVisited[v] = false;

		if (m_Graph.AdjMatrix[nVexStart][v] != 0)
		{
			// 如果顶点v和nVexStart相连，则最短距离设置为两顶点间的距离
			nShortDistance[v] = m_Graph.AdjMatrix[nVexStart][v];
		}
		else
		{
			// 如果不相连，则最短距离设置为最大值
			nShortDistance[v] = 0x7FFFFFFF;
		}

		nShortPath[v][0] = nVexStart; // 起始点为nVexStart
		// 初始化最短路径
		for (int w = 1; w < m_Graph.VexNum; w++)
		{
			nShortPath[v][w] = -1;
		}
	}
	// 初始化，将nVexStart顶点加入到集合中
	aVisited[nVexStart] = true;

	int min; // 暂存路径的最小值
	for (int i = 1; i < m_Graph.VexNum; i++)
	{
		min = 0x7FFFFFFF;
		bool bAdd = false; // 判断是否还有顶点可以加入集合

		for (int w = 0; w < m_Graph.VexNum; w++)
		{
			if (!aVisited[w] && nShortDistance[w] < min)
			{
				v = w;					 // w顶点距离nVexStart顶点最近
				min = nShortDistance[w]; // w到nVexStart的最短距离为min
				bAdd = true;
			}
		}
		// 如果没有顶点可以加入到集合，则跳出循环
		if (!bAdd)
		{
			break;
		}

		aVisited[v] = true;	  // 将w顶点加入到集合
		nShortPath[v][i] = v; // 每次找到最短路径后，就相当于从源点出发到了终点，所以nShortPath[v][i]=v

		for (int w = 0; w < m_Graph.VexNum; w++)
		{
			// 将w作为中间点计算nVexStart到所有顶点的最短距离
			if (!aVisited[w] && (min + m_Graph.AdjMatrix[v][w] < nShortDistance[w]) && (m_Graph.AdjMatrix[v][w] > 0))
			{
				// 如果有新的最短距离,则更新最短路径及距离
				nShortDistance[w] = min + m_Graph.AdjMatrix[v][w];
				for (int i = 0; i < m_Graph.VexNum; i++)
				{
					// 如果通过w到达顶点i的距离比较短，则将w的最短路径赋值给i
					nShortPath[w][i] = nShortPath[v][i];
				}
			}
		}
	}

	int nIndex = 0;
	int nVex1 = nVexStart;

	// 将最短路径保存到边的结构体数组中
	for (int i = 1; i < m_Graph.VexNum; i++)
	{
		if (nShortPath[nVexEnd][i] != -1)
		{
			aPath[nIndex].vex1 = nVex1;
			aPath[nIndex].vex2 = nShortPath[nVexEnd][i];
			aPath[nIndex].weight = m_Graph.AdjMatrix[nVex1][aPath[nIndex].vex2];
			nVex1 = nShortPath[nVexEnd][i];
			nIndex++;
		}
	}
	return nIndex;
}


void FindMinTree(Edge aPath[])
{
	bool aVisited[20] = { false }; // 判断某顶点是否在最小生成树中
	aVisited[0] = true;			 // 从0号顶点开始，加入到集合中
	int min;
	int nVex1, nVex2;

	for (int k = 0; k < m_Graph.VexNum - 1; k++)
	{
		min = 0X7FFFFFFF;

		for (int i = 0; i < m_Graph.VexNum; i++)
		{
			// 从集合中取一个顶点
			if (aVisited[i])
			{
				for (int j = 0; j < m_Graph.VexNum; j++)
				{
					// 从不在集合的顶点中取出一个顶点
					if (!aVisited[j])
					{
						if ((m_Graph.AdjMatrix[i][j] < min) && (m_Graph.AdjMatrix[i][j] != 0))
						{
							nVex1 = i;
							nVex2 = j;
							// 找出最短边
							min = m_Graph.AdjMatrix[i][j];
						}
					}
				}
			}
		}

		// 保存最短边的两个顶点
		aPath[k].vex1 = nVex1;
		aPath[k].vex2 = nVex2;
		aPath[k].weight = m_Graph.AdjMatrix[nVex1][nVex2];

		// 将两个顶点加入集合
		aVisited[nVex1] = true;
		aVisited[nVex2] = true;
	}
}
