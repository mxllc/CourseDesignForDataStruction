#ifndef BTREE_H
#define BTREE_H
#include <QWidget>
#include <string>

#define OK 1
#define ERROR 0
#define INFEASIBLE -1

typedef int Status;
typedef char Element;
typedef enum { Link, Thread }PointerTag;
//Link==0：指针，指向孩子结点
//Thread==1：线索，指向前驱或后继结点

#define rootCenterX 250
#define rootCenterY 20
#define MyDistanceX 150
#define MyDistanceY 70
#define MyReductionX 40

struct Position{
    int px;
    int py;
    int layer;
    int factor;//-1, 0, 1   左,  root, 右
};

struct BTreeNode
{
    Element val;
    Position pos;
    Position ParPos;
    struct BTreeNode *lchild, *rchild, *parent;
    PointerTag LTag, RTag;
};

class BTree
{
private:
    BTreeNode *root=nullptr;
    BTreeNode *PreRoot=nullptr, *InRoot=nullptr, *PostRoot=nullptr;

    bool InternalCreateTree(BTreeNode * &, std::string &, Position ParentPos);
    Status InternalCountLeafNode(BTreeNode *, int &);
    Status InternalDestroyTree(BTreeNode *&);
    Status InternalDestroyThreadTree(BTreeNode *&);


    Status PreOrderTraverseRecur(BTreeNode *, std::string &);
    Status InOrderTraverseRecur(BTreeNode *, std::string &);
    Status PostOrderTraverseRecur(BTreeNode *, std::string &);
    Status PreOrderTagReset(BTreeNode*);
    Status InThreading(BTreeNode *N, BTreeNode *&pre);
    Status PreThreading(BTreeNode *N, BTreeNode *&pre);
    Status PostThreading(BTreeNode *N, BTreeNode *&pre);
    Status CloneRootForThread(BTreeNode * &, BTreeNode * &, BTreeNode * &, BTreeNode * &);
    Status SetParent(BTreeNode *&, BTreeNode *parInfo);

public:
    BTree();
    ~BTree();
    bool CreateTree(QString);
    QString PreOrderTraverse();
    QString InOrderTraverse();
    QString PostOrderTraverse();
    QString CountLeafNode();
    BTreeNode *getRoot(int);
    QString InOrderThr();
    QString PreOrderThr();
    QString PostOrderThr();
    Status DestroyAllTree();


};

#endif // BTREE_H
