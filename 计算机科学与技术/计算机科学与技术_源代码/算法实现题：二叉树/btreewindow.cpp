#include "btreewindow.h"
#include "ui_btreewindow.h"


BtreeWindow::BtreeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BtreeWindow)
{
    ui->setupUi(this);
    paintMode=PreviousMode;

    //信号连接
    connect(ui->exit, SIGNAL(clicked()), this, SLOT(exitSlot()));
    connect(ui->back, SIGNAL(clicked()), this, SLOT(backSlot()));
    connect(ui->PreOrdTra, SIGNAL(clicked()), this, SLOT(PreOrdTraSlot()));
    connect(ui->InOrdTra, SIGNAL(clicked()), this, SLOT(InOrdTraSlot()));
    connect(ui->PostOrdTra, SIGNAL(clicked()), this, SLOT(PostOrdTraSlot()));
    connect(ui->CountLN, SIGNAL(clicked()), this, SLOT(CountLeafNodeSlot()));


    connect(ui->InOrdThr, SIGNAL(clicked()), this, SLOT(InOrdThrSlot()));
    connect(ui->PostOrdThr, SIGNAL(clicked()), this, SLOT(PostOrdThrSlot()));
    connect(ui->PreOrdThr, SIGNAL(clicked()), this, SLOT(PreOrdThrSlot()));



}

BtreeWindow::~BtreeWindow()
{
    delete ui;
}
void BtreeWindow::Initial(QString &iniStr)
{
    this->iniString=iniStr;
    ui->testBrowser->setText(iniString);
}


void BtreeWindow::exitSlot()
{
    QApplication* app;
    app->quit();
}
void BtreeWindow::backSlot()
{
    bt.DestroyAllTree();
    emit returnMain();
}

bool BtreeWindow::TreeEst(QString qstr)
{
    return bt.CreateTree(qstr);
}

void BtreeWindow::PreOrdTraSlot()
{
    QString qstr="先序遍历结果： \n";
    qstr+=bt.PreOrderTraverse();
    ui->testBrowser->setText(qstr);
    paintMode=PreviousMode;
    this->repaint();
}

void BtreeWindow::InOrdTraSlot()
{
    QString qstr="中序遍历结果：\n";
    qstr+=bt.InOrderTraverse();
    ui->testBrowser->setText(qstr);
    paintMode=PreviousMode;
    this->repaint();
}

void BtreeWindow::PostOrdTraSlot()
{
    QString qstr="后序遍历结果：\n";
    qstr+=bt.PostOrderTraverse();
    ui->testBrowser->setText(qstr);
    paintMode=PreviousMode;
    this->repaint();
}


void BtreeWindow::InOrdThrSlot()
{
    QString qstr="中序线索化遍历结果：\n";
    qstr+=bt.InOrderThr();
    ui->testBrowser->setText(qstr);
    paintMode=InOrderThreadMode;
    this->repaint();
}
void BtreeWindow::PostOrdThrSlot()
{
    QString qstr="后序线索化遍历结果：\n";
    qstr+=bt.PostOrderThr();
    ui->testBrowser->setText(qstr);
    paintMode=PostOrderThreadMode;
    this->repaint();
}
void BtreeWindow::PreOrdThrSlot()
{
    QString qstr="先序线索化遍历结果：\n";
    qstr+=bt.PreOrderThr();
    ui->testBrowser->setText(qstr);
    paintMode=PreOrderThreadMode;
    this->repaint();
}


void BtreeWindow::CountLeafNodeSlot()
{
    QString qstr="树中叶子结点个数：\n";
    qstr+=bt.CountLeafNode();
    ui->testBrowser->setText(qstr);
}

void BtreeWindow::MyDrawTriangle(QPainter &painter, QPoint end, QPoint arrow)
{
    int factor=10;
    double x_arr=double(arrow.rx()), y_arr=double(arrow.ry());
    double x_end=double(end.rx()), y_end=double(end.ry());
    double x_triBigOne, y_triBigOne;
    double x_triBigTwo, y_triBigTwo;
    int x_triOne, x_triTwo, y_triOne, y_triTwo;


    double length2=(x_arr-x_end)*(x_arr-x_end)+(y_arr-y_end)*(y_arr-y_end);

    if(arrow.ry()-end.ry() == 0)
    {
        x_triBigOne=x_triBigTwo=x_end;
        y_triBigOne=y_end+sqrt((length2)/3);
        y_triBigTwo=y_end-sqrt((length2)/3);
    }
    else if(arrow.rx()-end.rx() == 0)
    {
        y_triBigOne=y_triBigTwo=y_end;
        x_triBigOne=x_end+sqrt((length2)/3);
        x_triBigTwo=x_end-sqrt((length2)/3);

    }
    else{
        double declineEA=(y_arr-y_end)/(x_arr-x_end);
        double declinePerpendicular=-1/declineEA;
        x_triBigOne=x_end+sqrt(length2/(3*(1+declinePerpendicular*declinePerpendicular)));
        x_triBigTwo=x_end-sqrt(length2/(3*(1+declinePerpendicular*declinePerpendicular)));

        y_triBigOne=declinePerpendicular*(x_triBigOne-x_end)+y_end;
        y_triBigTwo=declinePerpendicular*(x_triBigTwo-x_end)+y_end;
    }
    x_triOne=int((factor*x_arr+x_triBigOne)/(factor+1));
    y_triOne=int((factor*y_arr+y_triBigOne)/(factor+1));
    x_triTwo=int((factor*x_arr+x_triBigTwo)/(factor+1));
    y_triTwo=int((factor*y_arr+y_triBigTwo)/(factor+1));


    QPoint point[3] = {
        QPoint(x_triOne,y_triOne),
        QPoint(x_triTwo,y_triTwo),
        arrow
    };
    QBrush brush(QColor(0, 0, 0)); //画刷
    painter.setBrush(brush); //添加画刷
    painter.drawPolygon(point,3);
    QBrush brush2(QColor(0, 255, 0, 125)); //画刷
    painter.setBrush(brush2); //添加画刷
}

void BtreeWindow::PreOrderTraRecurPaint(QPainter &painter, BTreeNode *N)
{
    if(N!=nullptr){
        QRect rect(N->pos.px, N->pos.py, MyRadius, MyRadius);//构造一个矩形
        if(N->ParPos.factor!=0){
            //画与父节点的连线
          QRect Parentrect(N->ParPos.px, N->ParPos.py, MyRadius, MyRadius);//构造一个矩形

          QPoint CurPoint={int((rect.topLeft().rx()+rect.topRight().rx())/2),rect.topLeft().ry()};
          QPoint ParPoint={int((Parentrect.bottomLeft().rx()+Parentrect.bottomRight().rx())/2),Parentrect.bottomLeft().ry()};
          if(N->ParPos.factor==1){
              painter.drawLine(CurPoint,ParPoint);
              MyDrawTriangle(painter, ParPoint, CurPoint);
          }
          else{
              painter.drawLine(CurPoint,ParPoint);
              MyDrawTriangle(painter, ParPoint, CurPoint);
          }
        }

        painter.drawEllipse(rect);
        QString qstr;
        qstr=qstr+N->val;
        painter.drawText(rect.center(), qstr);

        PreOrderTraRecurPaint(painter, N->lchild);
        PreOrderTraRecurPaint(painter, N->rchild);
    }
    return;
}

void BtreeWindow::PreOrderThrPaint(QPainter &painter, BTreeNode *N)
{
    BTreeNode *p = N, *f=p;
    QRect parentRect(N->pos.px, N->pos.py, MyRadius, MyRadius);//构造一个矩形
    painter.drawEllipse(parentRect);
    QString qstr;
    qstr=qstr+p->val;
    painter.drawText(parentRect.center(), qstr);

    while(p->rchild!=nullptr)
    {
        if(p->LTag == Link)
            p = p->lchild;
        else
            p = p->rchild;
        QRect rect(p->pos.px, p->pos.py, MyRadius, MyRadius);//构造一个矩形
        QPoint ParPoint;
        QPoint CurPoint;
        if(p->pos.layer<f->pos.layer)
        {
            ParPoint={int((parentRect.topLeft().rx()+parentRect.topRight().rx())/2),parentRect.topLeft().ry()};
            CurPoint={int((rect.bottomLeft().rx()+rect.bottomRight().rx())/2),rect.bottomLeft().ry()};
        }
        else if(p->pos.layer>f->pos.layer)
        {
            CurPoint={int((rect.topLeft().rx()+rect.topRight().rx())/2),rect.topLeft().ry()};
            ParPoint={int((parentRect.bottomLeft().rx()+parentRect.bottomRight().rx())/2),parentRect.bottomLeft().ry()};
        }
        else
        {
            CurPoint={rect.bottomLeft().rx(),int((rect.bottomLeft().ry()+rect.topLeft().ry())/2)};
            ParPoint={parentRect.bottomRight().rx(),int((parentRect.bottomRight().ry()+parentRect.topRight().ry())/2)};
        }

        painter.drawLine(CurPoint,ParPoint);
        MyDrawTriangle(painter, ParPoint, CurPoint);


        painter.drawEllipse(rect);
        QString qstr;
        qstr=qstr+p->val;
        painter.drawText(rect.center(), qstr);

        f=p;
        parentRect=rect;
    }

    return;
}

void BtreeWindow::InOrderThrPaint(QPainter &painter, BTreeNode *N)
{
    BTreeNode *p = N, *f=p;
    QRect parentRect(p->pos.px, p->pos.py, MyRadius, MyRadius);//构造一个矩形
    QPoint ParPoint;
    QPoint CurPoint;
    QString qstr;


    bool flag=true;
    while (p!=nullptr)
    {
        while (p->LTag == Link)
            p = p->lchild;

        QRect rect(p->pos.px, p->pos.py, MyRadius, MyRadius);//构造一个矩形
        painter.drawEllipse(rect);
        qstr=p->val;
        painter.drawText(rect.center(), qstr);

        if(flag==false){
            if(p->pos.layer<f->pos.layer)
            {
                ParPoint={int((parentRect.topLeft().rx()+parentRect.topRight().rx())/2),parentRect.topLeft().ry()};
                CurPoint={int((rect.bottomLeft().rx()+rect.bottomRight().rx())/2),rect.bottomLeft().ry()};
            }
            else if(p->pos.layer>f->pos.layer)
            {
                CurPoint={int((rect.topLeft().rx()+rect.topRight().rx())/2),rect.topLeft().ry()};
                ParPoint={int((parentRect.bottomLeft().rx()+parentRect.bottomRight().rx())/2),parentRect.bottomLeft().ry()};
            }
            else
            {
                CurPoint={rect.bottomLeft().rx(),int((rect.bottomLeft().ry()+rect.topLeft().ry())/2)};
                ParPoint={parentRect.bottomRight().rx(),int((parentRect.bottomRight().ry()+parentRect.topRight().ry())/2)};
            }

            painter.drawLine(CurPoint,ParPoint);
            MyDrawTriangle(painter, ParPoint, CurPoint);
        }
        flag=false;
        f=p;
        parentRect=rect;


        while (p->RTag == Thread && p->rchild!=nullptr) {
            p = p->rchild;

            QRect rect(p->pos.px, p->pos.py, MyRadius, MyRadius);//构造一个矩形
            painter.drawEllipse(rect);
            qstr=p->val;
            painter.drawText(rect.center(), qstr);

            if(p->pos.layer<f->pos.layer)
            {
                ParPoint={int((parentRect.topLeft().rx()+parentRect.topRight().rx())/2),parentRect.topLeft().ry()};
                CurPoint={int((rect.bottomLeft().rx()+rect.bottomRight().rx())/2),rect.bottomLeft().ry()};
            }
            else if(p->pos.layer>f->pos.layer)
            {
                CurPoint={int((rect.topLeft().rx()+rect.topRight().rx())/2),rect.topLeft().ry()};
                ParPoint={int((parentRect.bottomLeft().rx()+parentRect.bottomRight().rx())/2),parentRect.bottomLeft().ry()};
            }
            else
            {
                CurPoint={rect.bottomLeft().rx(),int((rect.bottomLeft().ry()+rect.topLeft().ry())/2)};
                ParPoint={parentRect.bottomRight().rx(),int((parentRect.bottomRight().ry()+parentRect.topRight().ry())/2)};
            }

            painter.drawLine(CurPoint,ParPoint);
            MyDrawTriangle(painter, ParPoint, CurPoint);

            f=p;
            parentRect=rect;
        }
        p = p->rchild;

    }

    return;
}

void BtreeWindow::PostOrderThrPaint(QPainter &painter, BTreeNode *N)
{
    //寻找第一个结点
    BTreeNode *f, *p = N, *prev;
    do{
        while(p->LTag==Link)
            p=p->lchild;
        if(p->RTag==Link)
            p=p->rchild;
    }while(p->LTag!=Thread || p->RTag!=Thread);


    QRect parentRect(p->pos.px, p->pos.py, MyRadius, MyRadius);//构造一个矩形
    painter.drawEllipse(parentRect);
    QString qstr;
    qstr=p->val;
    painter.drawText(parentRect.center(), qstr);
    prev=p;
//    str=str+p->val+" ";

    while(p!=N){
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
        else
            p=p->rchild;
//        str=str+p->val+" ";

        QRect rect(p->pos.px, p->pos.py, MyRadius, MyRadius);//构造一个矩形
        QPoint ParPoint;
        QPoint CurPoint;
        if(p->pos.layer<prev->pos.layer)
        {
            ParPoint={int((parentRect.topLeft().rx()+parentRect.topRight().rx())/2),parentRect.topLeft().ry()};
            CurPoint={int((rect.bottomLeft().rx()+rect.bottomRight().rx())/2),rect.bottomLeft().ry()};
        }
        else if(p->pos.layer>prev->pos.layer)
        {
            CurPoint={int((rect.topLeft().rx()+rect.topRight().rx())/2),rect.topLeft().ry()};
            ParPoint={int((parentRect.bottomLeft().rx()+parentRect.bottomRight().rx())/2),parentRect.bottomLeft().ry()};
        }
        else
        {
            CurPoint={rect.bottomLeft().rx(),int((rect.bottomLeft().ry()+rect.topLeft().ry())/2)};
            ParPoint={parentRect.bottomRight().rx(),int((parentRect.bottomRight().ry()+parentRect.topRight().ry())/2)};
        }

        painter.drawLine(CurPoint,ParPoint);
        MyDrawTriangle(painter, ParPoint, CurPoint);


        painter.drawEllipse(rect);
        qstr=p->val;
        painter.drawText(rect.center(), qstr);

        prev=p;
        parentRect=rect;
    }

    return;
}

void BtreeWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen; //画笔
    pen.setColor(QColor(0, 0, 0));
    QBrush brush(QColor(0, 255, 0, 125)); //画刷
    painter.setPen(pen); //添加画笔
    painter.setBrush(brush); //添加画刷

    switch(paintMode)
    {

    case PreOrderThreadMode:
        PreOrderThrPaint(painter, bt.getRoot(2));
        break;
    case InOrderThreadMode:
        InOrderThrPaint(painter, bt.getRoot(3));
        break;
    case PostOrderThreadMode:
        PostOrderThrPaint(painter, bt.getRoot(4));
        break;
    case PreviousMode:
    default:
        PreOrderTraRecurPaint(painter, bt.getRoot(1));
        break;

    }


//debug test
//    QPoint point[5] = {
//        QPoint(10,10),
//        QPoint(100,100),
//        QPoint(400,50),
//        QPoint(50,200),
//        QPoint(40,100)
//    };

//    MyDrawTriangle(painter,point[1],point[2]);
//    painter.drawPolyline(point,5);
//    painter.drawPolygon(point,5);

}

