#include "mgraph.h"



MGraph::MGraph()
{
    //初始化2个结点
//    { Swimming, Basketball, Football, Taichi, Tennis, Reading, Gaming, Travelling }
    Elemtype p0, p1;

    p0=new Person {0,
            QString::fromStdString("张三"),
            QString::fromStdString("上海"),
            QString::fromStdString("光明小学"),
            QString::fromStdString("正直中学"),
            QString::fromStdString("诚信大学"),
            QString::fromStdString("友善公司"),
            {true, false, true, false, true, false, true, false}};
    p1=new Person {1,
               QString::fromStdString("李四"),
               QString::fromStdString("北京"),
               QString::fromStdString("爱国小学"),
               QString::fromStdString("和谐中学"),
               QString::fromStdString("敬业大学"),
               QString::fromStdString("奉献公司"),
               {false, false, false, false, true, true, true, true}};
//    p2=new Person {1,
//               QString::fromStdString("王五"),
//               QString::fromStdString("广州"),
//               QString::fromStdString("人民小学"),
//               QString::fromStdString("华夏中学"),
//               QString::fromStdString("三峡大学"),
//               QString::fromStdString("长城公司"),
//               {false, true, true, false, false, false, true, true}};


//    try { N = new BTreeNode; }
//    catch (const bad_alloc){
//        cout << "out of memory" << endl;
//        return false;
//    }






    //邻接矩阵初始化
    for (int i = 0; i < MAX_VERTEX_NUM; ++i)
        for (int j = 0; j < MAX_VERTEX_NUM; ++j)
            arcs[i][j] = 0;

    vexs[0]=p0;
    vexs[1]=p1;
//    vexs[2]=p2;
    vexnum=2;

//    初始化：2者互相认识
    arcs[0][1] = 1;
    arcs[1][0] = 1;
//    arcs[0][2] = 1;
//    arcs[1][0] = 1;
//    arcs[1][2] = 1;
//    arcs[2][0] = 1;
//    arcs[2][1] = 1;



    vnp[0].data=p0;
    vnp[1].data=p1;
    ArcNodePtr anptr;

    //设置结点0的表
    anptr = new ArcNode;
    anptr->adjvex=1;
    anptr->nextarc=nullptr;
    vnp[0].firstarc=anptr;

    //设置结点1的表
    anptr = new ArcNode;
    anptr->adjvex=0;
    anptr->nextarc=nullptr;
    vnp[1].firstarc=anptr;







}
//int ID;
//QString name;
//QString region;
//QString primarySchool;
//QString middleSchool;
//QString highSchool;
//QString workOrginization;


MGraph::~MGraph()
{
//    delete person0-10
//    delete anptr
}

int MGraph::LocateVex(Elemtype &e)
{
    int i = 0;
    for (; i < vexnum; ++i)
        if (vexs[i]->ID == e->ID)
            return i;
    return INFEASIBLE;
}

int MGraph::getVexnum()
{
    return vexnum;
}

//添加结点
bool MGraph::addNode(Elemtype e, bool *friendList)
{
    Elemtype p =new Person(*e);
    p->ID=vexnum;//设置好ID

    vexs[vexnum]=p;
    vnp[vexnum].data=p;
    vnp[vexnum].firstarc = nullptr;


    ArcNodePtr anptrP, anptrC;
    bool flagFriendList=true;

    for(int i=0; i<vexnum; i++)
    {
        if(friendList[i])
        {
            arcs[i][vexnum] = 1;
            arcs[vexnum][i] = 1;


            //在第i个结点 添加ArcNode
            anptrP=new ArcNode;
            anptrP->adjvex=vexnum;
            anptrP->nextarc=nullptr;

            ArcNodePtr anptr = vnp[i].firstarc;
            if(vnp[i].firstarc==nullptr)
                vnp[i].firstarc=anptrP;
            else{
                while(anptr->nextarc!=nullptr)
                    anptr=anptr->nextarc;
                anptr->nextarc=anptrP;
            }


            //在第vexnum个结点 添加ArcNode
            anptr=new ArcNode;
            anptr->adjvex=i;
            anptr->nextarc=nullptr;

            if(flagFriendList){
                vnp[vexnum].firstarc=anptr;
                flagFriendList=false;
            }
            else
                anptrC->nextarc=anptr;

            anptrC=anptr;

        }
    }


    vexnum+=1;
    return true;
}

QString MGraph::DisplayVextex() const
{
    QString qstr;

    for(int i=0; i<vexnum;i++)
        qstr=qstr+vexs[i]->name+" ";
    qstr=qstr+"\n";

    return qstr;
}
QString MGraph::DisplayAdjMatrix() const
{
    QString qstr;
    for (int i = 0; i < vexnum; ++i)
    {
        for (int j = 0; j < vexnum; ++j)
            qstr=qstr+QString::number(arcs[i][j])+" ";
        qstr=qstr+"\n";
    }
    return qstr;
}
QString MGraph::DisplayAdjArc() const
{
    QString qstr;

    ArcNodePtr p;
    for (int i = 0; i<vexnum; ++i)
    {
        qstr=qstr+ vnp[i].data->name + "-->";
        p = vnp[i].firstarc;
        while (p)
        {
            qstr=qstr + QString::number(p->adjvex) +" ";
            p = p->nextarc;
        }
        qstr=qstr+"\n";
    }

    return qstr;
}

int *MGraph::getAssociateExtent()
{
    return AssociateExtent;
}

Elemtype MGraph::getVexs(int id)
{
    return vexs[id];
}


void MGraph::SetAssociateExtent(int id)
{
    for(int i=0;i<vexnum;i++)
        AssociateExtent[i]=-1;

    for(int i=0;i<vexnum;i++)
    {
        if(arcs[i][id]==1 || id ==i){
            AssociateExtent[i]=-1;//相互认识
            continue;
        }
        AssociateExtent[i]=0;
        for(int j=0;j<vexnum;j++)
        {
            if(arcs[i][j]==1 && arcs[j][id]==1)
                AssociateExtent[i]+=1;
        }

    }
}
bool MGraph::isConnect(int i, int j)
{
    if(arcs[i][j]==1 || arcs[j][i]==1)
        return true;
    else
        return false;

}

