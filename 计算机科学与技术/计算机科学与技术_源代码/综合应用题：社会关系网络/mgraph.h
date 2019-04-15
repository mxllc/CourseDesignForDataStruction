#ifndef MGRAPH_H
#define MGRAPH_H


#include <QString>
//#include <vector>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define MAX_VERTEX_NUM 10
#define HobbyNum 8
typedef enum { Swimming, Basketball, Football, Taichi, Tennis, Reading, Gaming, Travelling }HobbyCommunity;

typedef struct Person{
    int ID;
    QString name;
    QString region;
    QString primarySchool;
    QString middleSchool;
    QString highSchool;
    QString workOrginization;
//    vector<bool> Hobby;
    bool Hobby[HobbyNum];
}Person, *Elemtype;


typedef struct ArcNode
{
    int adjvex;
    ArcNode *nextarc;
//    int weight;
}ArcNode, *ArcNodePtr;


typedef struct VNode
{
    Elemtype data;
    ArcNode *firstarc;
}VNode, *VNodePtr;

typedef  int AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];



class MGraph
{
private:
    int vexnum;//结点数目
    Elemtype vexs[MAX_VERTEX_NUM];//存放每个节点
    AdjMatrix arcs;//邻接矩阵
    VNode vnp[MAX_VERTEX_NUM];//邻接表
    int AssociateExtent[MAX_VERTEX_NUM];//某人的关联度

public:
    MGraph();
    ~MGraph();
    int LocateVex(Elemtype &e);
    bool addNode(Elemtype, bool *);
    int getVexnum();
    QString DisplayVextex() const;
    QString DisplayAdjMatrix() const;
    QString DisplayAdjArc() const;
    void SetAssociateExtent(int id);
    int *getAssociateExtent();
    Elemtype getVexs(int );
    bool isConnect(int i, int j);


};

#endif // MGRAPH_H
