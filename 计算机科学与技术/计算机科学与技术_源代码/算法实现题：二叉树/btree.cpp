#include "btree.h"

#include <iostream>
using namespace std;

BTree::BTree()
{
    root=nullptr;
    PreRoot=nullptr;
    InRoot=nullptr;
    PostRoot=nullptr;
}

BTree::~BTree()
{
    InternalDestroyTree(root);
    InternalDestroyThreadTree(PreRoot);
    InternalDestroyThreadTree(PostRoot);
    InternalDestroyThreadTree(InRoot);
}

Status BTree::InternalDestroyTree(BTreeNode *&N)
{
    if(N!=nullptr)
    {
        InternalDestroyTree(N->lchild);
        InternalDestroyTree(N->rchild);
        delete N;
    }
    return OK;
}

Status BTree::InternalDestroyThreadTree(BTreeNode *&N)
{
    //后序遍历实现删除
    if(N!=nullptr)
    {
        if(N->LTag == Link)//有左孩子
            InternalDestroyThreadTree(N->lchild);
        if(N->RTag == Link)//有右孩子
            InternalDestroyThreadTree(N->rchild);
        delete N;
    }
    return OK;
}

Status BTree::DestroyAllTree()
{
    InternalDestroyTree(root);
    InternalDestroyThreadTree(PreRoot);
    InternalDestroyThreadTree(PostRoot);
    InternalDestroyThreadTree(InRoot);
    return OK;
}

//string和QString之间的转换
//str = qstr.toStdString();
//qstr = QString::fromStdString(str);





//#define rootCenterX 250
//#define rootCenterY 50
//#define MyRadius 50
//#define MyDistanceX 120
//#define MyDistanceY 80
//#define MyReductionX 20

//struct Position{
//    int px;
//    int py;
//    int layer;
//    int factor;//-1, 0, 1   左,  root, 右
//};

//struct BTreeNode
//{
//    Element val;
//    Position pos;
//    struct BTreeNode *lchild,*rchild;
//};

Status BTree::SetParent(BTreeNode *&N, BTreeNode *parInfo)
{
    if(N!=nullptr){
        N->parent=parInfo;
        SetParent(N->lchild,N);
        SetParent(N->rchild,N);
    }
    return OK;
}

bool BTree::InternalCreateTree(BTreeNode * &N, std::string &str, Position ParentPos)
{
    if(str.length()==0)//容错检测
        return true;

    Element ch;
    ch = str[0];
    if (ch == '#'){
        str = str.substr(1,str.length()-1);
        return true;	//	不给#建立结点
    }
    try { N = new BTreeNode; }
    catch (const bad_alloc){
        cout << "out of memory" << endl;
        return false;
    }
    N->val = ch;
    N->lchild = nullptr;
    N->rchild = nullptr;
    N->LTag = Link;
    N->RTag = Link;

    str = str.substr(1,str.length()-1);

    N->ParPos=ParentPos;//父节点信息

    N->pos.py=ParentPos.py+abs(ParentPos.factor)*MyDistanceY;
    N->pos.layer=ParentPos.layer+1;
    N->pos.px=ParentPos.px+(ParentPos.factor)*(MyDistanceX-(ParentPos.layer)*MyReductionX);

    if(N->pos.layer>=5)
        return false;

    N->pos.factor=-1;//左子树
    if(InternalCreateTree(N->lchild, str, N->pos)==false)
        return false;
    N->pos.factor=1;//右子树
    if(InternalCreateTree(N->rchild, str, N->pos)==false)
        return false;

    return true;
}

Status BTree::CloneRootForThread(BTreeNode * &N, BTreeNode * &PreN, BTreeNode * &InN, BTreeNode * &PostN)
{
    if(N!=nullptr){
        try {
            PreN = new BTreeNode;
            InN = new BTreeNode;
            PostN = new BTreeNode;
        }
        catch (const bad_alloc){
            cout << "out of memory" << endl;
            return ERROR;
        }
        (*PreN)=(*N);
        (*InN)=(*N);
        (*PostN)=(*N);
        PreN->lchild=nullptr;
        PreN->rchild=nullptr;
        InN->lchild=nullptr;
        InN->rchild=nullptr;
        PostN->lchild=nullptr;
        PostN->rchild=nullptr;

        CloneRootForThread(N->lchild, PreN->lchild, InN->lchild, PostN->lchild);
        CloneRootForThread(N->rchild, PreN->rchild, InN->rchild, PostN->rchild);
    }
    return OK;
}

bool BTree::CreateTree(QString qstr)
{
    string str = qstr.toStdString();
    Position rootPos={rootCenterX, rootCenterY, 0, 0};

//    程序容错性
    if(InternalCreateTree(root, str, rootPos)==false)
    {
        InternalDestroyTree(root);
        return false;
    }
    SetParent(root, nullptr);
    CloneRootForThread(root, PreRoot, InRoot, PostRoot);

    BTreeNode *pre = nullptr;
    SetParent(PreRoot, nullptr);
    PreThreading(PreRoot,pre);//先序线索化


    pre = nullptr;
    SetParent(InRoot, nullptr);
    InThreading(InRoot,pre);//中序线索化


    pre = nullptr;
    SetParent(PostRoot, nullptr);
    PostThreading(PostRoot,pre);//后序线索化


    return OK;
}

//----先序遍历
Status BTree::PreOrderTraverseRecur(BTreeNode *N, std::string&str)
{
    if(N!=nullptr){
        str =str+N->val+" ";
        PreOrderTraverseRecur(N->lchild,str);
        PreOrderTraverseRecur(N->rchild,str);
    }
    return OK;
}
QString BTree::PreOrderTraverse()
{
    std::string str;
    PreOrderTraverseRecur(root,str);
    QString qstr=QString::fromStdString(str);
    return qstr;
}

//----中序遍历
Status BTree::InOrderTraverseRecur(BTreeNode *N, std::string&str)
{
    if(N!=nullptr){
        InOrderTraverseRecur(N->lchild,str);
        str =str+N->val+" ";
        InOrderTraverseRecur(N->rchild,str);
    }
    return OK;
}
QString BTree::InOrderTraverse()
{
    std::string str;
    InOrderTraverseRecur(root,str);
    QString qstr=QString::fromStdString(str);
    return qstr;
}


//----后序遍历
Status BTree::PostOrderTraverseRecur(BTreeNode *N, std::string&str)
{
    if(N!=nullptr){
        PostOrderTraverseRecur(N->lchild,str);
        PostOrderTraverseRecur(N->rchild,str);
        str =str+N->val+" ";
    }
    return OK;
}
QString BTree::PostOrderTraverse()
{
    std::string str;
    PostOrderTraverseRecur(root,str);
    QString qstr=QString::fromStdString(str);
    return qstr;
}


//----计算叶子结点个数
Status BTree::InternalCountLeafNode(BTreeNode *N, int &num)
{
    if(N!=nullptr){
        if (N->lchild == nullptr && N->rchild == nullptr) {
            num += 1;
            return OK;
        }
        if (N->lchild)
            InternalCountLeafNode(N->lchild, num);
        if (N->rchild)
            InternalCountLeafNode(N->rchild, num);
   }
   return OK;
}
QString BTree::CountLeafNode()
{
    int num=0;
    InternalCountLeafNode(root, num);
    QString qstr=QString::number(num);
    return qstr;
}

BTreeNode *BTree::getRoot(int mode)
{
    BTreeNode *p=root;
    switch (mode) {
    case 1:
        p=root;
        break;
    case 2:
        p=PreRoot;
        break;
    case 3:
        p=InRoot;
        break;
    case 4:
        p=PostRoot;
        break;
    default:
        p=root;
        break;

    }
    return p;
}



//-----线索化----
Status BTree::PreOrderTagReset(BTreeNode* N)
{
    if(N!=nullptr){
        N->LTag=Link;
        N->RTag=Link;
        PreOrderTagReset(N->lchild);
        PreOrderTagReset(N->rchild);
    }
    return OK;
}

Status BTree::InThreading(BTreeNode *N, BTreeNode *&pre)
{
    if (N!=nullptr)
    {
        if (N->LTag == Link)
            InThreading(N->lchild, pre);
        if (N->lchild==nullptr)
        {
            N->LTag = Thread;
            N->lchild = pre;
        }
        if (N->rchild==nullptr)
            N->RTag = Thread;
        if (pre!=nullptr && pre->RTag == Thread)
            pre->rchild = N;
        pre = N;

        if (N->RTag == Link)
            InThreading(N->rchild, pre);
    }
    return OK;
}
QString BTree::InOrderThr()
{
    BTreeNode *p = InRoot;
    std::string str;
    while (p!=nullptr)
    {
        while (p->LTag == Link)
            p = p->lchild;

        str=str+p->val+" ";

        while (p->RTag == Thread && p->rchild!=nullptr) {
            p = p->rchild;
            str=str+p->val+" ";
        }
        p = p->rchild;
    }
    QString qstr=QString::fromStdString(str);
    return qstr;
}

Status BTree::PreThreading(BTreeNode *N, BTreeNode *&pre)
{
    if (N!=nullptr)
    {
        if (N->lchild==nullptr)
        {
            N->LTag = Thread;
            N->lchild = pre;
        }
        if (N->rchild==nullptr)
            N->RTag = Thread;
        if (pre!=nullptr && pre->RTag == Thread)
            pre->rchild = N;
        pre = N;

        if (N->LTag == Link)
            PreThreading(N->lchild, pre);
        if (N->RTag == Link)
            PreThreading(N->rchild, pre);
    }
    return OK;
}
QString BTree::PreOrderThr()
{
    std::string str;

    BTreeNode *p = PreRoot;
    str=str+p->val+" ";

    while(p->rchild!=nullptr)
    {
        if(p->LTag == Link)
            p = p->lchild;
        else
            p = p->rchild;

        str=str+p->val+" ";
    }
    QString qstr=QString::fromStdString(str);

//Debug 测试
//    std::string ssstr;
//    PreOrderTraverseRecur(PreRoot,ssstr);
//    QString qstr=QString::fromStdString(ssstr);
    return qstr;
}

Status BTree::PostThreading(BTreeNode *N, BTreeNode *&pre)
{
    if (N!=nullptr)
    {
        PostThreading(N->lchild, pre);
        PostThreading(N->rchild, pre);
        if (N->lchild==nullptr)
        {
            N->LTag = Thread;
            N->lchild = pre;
        }
        if (N->rchild==nullptr)
            N->RTag = Thread;

        if (pre!=nullptr && pre->RTag == Thread)
            pre->rchild = N;
        pre = N;
    }
    return OK;
}
QString BTree::PostOrderThr()
{
    std::string str;
    //寻找第一个结点
    BTreeNode *f, *p = PostRoot;
    do{
        while(p->LTag==Link)
            p=p->lchild;
        if(p->RTag==Link)
            p=p->rchild;
    }while(p->LTag!=Thread || p->RTag!=Thread);

    str=str+p->val+" ";

    while(p!=PostRoot){
        if (p->RTag==Link)
        {
            f=p->parent;
            if (f->RTag==Thread || p==f->rchild)
                p=f;
            else
            {
                p=f->rchild;
                do{
                    while(p->LTag==Link)
                        p=p->lchild;
                    if (p->RTag==Link) p=p->rchild;
                }while (p->LTag!=Thread || p->RTag!=Thread); //与寻找第一个结点的步骤一模一样
            }
        }
        else p=p->rchild;
        str=str+p->val+" ";
    }

    QString qstr=QString::fromStdString(str);
    return qstr;

}
