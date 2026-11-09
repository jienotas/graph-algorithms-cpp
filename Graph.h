#ifndef GPAPH_H
#define GRAPH_H
struct Vex
{
	int num;     //编号
	char name[20];	//名称
	char des[1024];	//描述
};

struct Edge
{
	int vex1;
	int vex2;
	int weight;
};

typedef struct Path
{
	int vexs[20];
	Path* next;
} *PathList;

class CGraph
{
public:
	int AdjMatrix[20][20];   //邻接矩阵
	Vex Vexs[20];	//顶点数组
	int VexNum;		//顶点个数

	void Init();
	bool InsertVex(Vex V);
	bool InsertEdge(Edge E);
	Vex GetVex(int v);
	int FindEdge(int v);
	void DFS(int nVex, bool bVisted[], int& nIndex, PathList& pList);
	void DFSTraverse(int nVex, PathList& pList);
	
};
int FindShortPath(int Start, int End, Edge aPath[]);
void FindMinTree(Edge aPath[]);

#endif GRAPH_H