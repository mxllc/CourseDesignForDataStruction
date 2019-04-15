#include "personinforwindow.h"
#include "ui_personinforwindow.h"



PersonInforWindow::PersonInforWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonInforWindow)
{
    ui->setupUi(this);

    connect(ui->exit, SIGNAL(clicked()), this, SLOT(exitSlot()));
    connect(ui->back, SIGNAL(clicked()), this, SLOT(backSlot()));
}

PersonInforWindow::~PersonInforWindow()
{
    delete ui;
}

void PersonInforWindow::exitSlot()
{
    QApplication* app;
    app->quit();
}
void PersonInforWindow::backSlot()
{
    emit returnNetwork();
}

void PersonInforWindow::paintEvent(QPaintEvent *)
{
    int MyRadius=50;
    Person *ps=mg->getVexs(IdNum);

    QPainter painter(this);
    QPen pen; //画笔
    pen.setColor(QColor(0, 0, 0));
    QBrush brush(QColor(0, 255, 0, 125)); //画刷
    painter.setPen(pen); //添加画笔
    painter.setBrush(brush); //添加画刷

    //实例解析
    int examRadius=20;
    int examX=650;
    int examY=20;
    QRect rectExam1(examX, examY, examRadius, examRadius);//构造一个矩形
    painter.setBrush(QColor(255, 0, 0)); //添加画刷
    painter.drawEllipse(rectExam1);
    QString examStr="当前结点";
    QPoint pt={rectExam1.bottomRight().rx()+10, int((rectExam1.bottomRight().ry()+rectExam1.topRight().ry())/2)+5};
    painter.drawText(pt, examStr);

    QRect rectExam2(examX, examY+30, examRadius, examRadius);//构造一个矩形
    painter.setBrush(QColor(0, 0, 255)); //添加画刷
    painter.drawEllipse(rectExam2);
    examStr="好友结点";
    pt={rectExam2.bottomRight().rx()+10, int((rectExam2.bottomRight().ry()+rectExam2.topRight().ry())/2)+5};
    painter.drawText(pt, examStr);

    QRect rectExam3(examX, examY+60, examRadius, examRadius);//构造一个矩形
    painter.setBrush(QColor(0, 255, 0)); //添加画刷
    painter.drawEllipse(rectExam3);
    examStr="可能认识的结点";
    pt={rectExam3.bottomRight().rx()+10, int((rectExam3.bottomRight().ry()+rectExam3.topRight().ry())/2)+5};
    painter.drawText(pt, examStr);






    int max=mg->getVexnum();
    double angle=0;
    double delta=2*mypi/max;

    QString qstr;

    QTransform transform;
    transform.translate(300, 180); //把中心点移动到 50，50
    transform.rotate(0);
    painter.setWorldTransform(transform);



    double cx=0, cy=0;
    double px=polygonX, py=0;


    QPoint point[MAX_VERTEX_NUM];

    for(int i=0;i<max;i++){
        cx=px * cos(angle) - py * sin(angle);
        cy=px * sin(angle) + py * cos(angle);

        QRect rect(int(cx), int(cy), MyRadius, MyRadius);//构造一个矩形
        point[i]=rect.center();


        if(i==IdNum){
            QBrush brush(QColor(255, 0, 0)); //画刷
            painter.setBrush(brush); //添加画刷
        }
        else if(mg->isConnect(i,IdNum)){
            QBrush brush(QColor(0, 0, 255)); //画刷
            painter.setBrush(brush); //添加画刷
        }
        else
        {
            QBrush brush(QColor(0, 255, 0)); //画刷
            painter.setBrush(brush); //添加画刷
        }



        painter.drawEllipse(rect);
        angle+=delta;

    }



    for(int i=0;i<max-1;i++)
    {
        for(int j=1+i;j<max;j++){
            if(mg->isConnect(i,j)==1)
                painter.drawLine(point[i], point[j]);
        }
    }



    for(int i=0;i<max;i++)
    {
        Person *p=mg->getVexs(i);
        QString qstr=p->name+"_"+QString::number(p->ID);
        painter.drawText(point[i], qstr);
    }





    qstr=qstr+"姓名："+ps->name+"\n";
    qstr=qstr+"地区："+ps->region+"\n";
    qstr=qstr+"小学："+ps->primarySchool+"\n";
    qstr=qstr+"中学："+ps->middleSchool+"\n";
    qstr=qstr+"大学："+ps->highSchool+"\n";
    qstr=qstr+"工作单位："+ps->workOrginization+"\n";
    qstr=qstr+"\n\n兴趣爱好：\n";
    bool flag=false;
    if(ps->Hobby[0])
    {
        qstr=qstr+"Swimming\n";
        flag=true;
    }
    if(ps->Hobby[1])
    {
        qstr=qstr+"Basketball\n";
        flag=true;
    }
    if(ps->Hobby[2])
    {
        qstr=qstr+"Football\n";
        flag=true;
    }
    if(ps->Hobby[3])
    {
        qstr=qstr+"Taichi\n";
        flag=true;
    }
    if(ps->Hobby[4])
    {
        qstr=qstr+"Tennis\n";
        flag=true;
    }
    if(ps->Hobby[5])
    {
        qstr=qstr+"Reading\n";
        flag=true;
    }
    if(ps->Hobby[6])
    {
        qstr=qstr+"Gaming\n";
        flag=true;
    }
    if(ps->Hobby[7])
    {
        qstr=qstr+"Travelling\n";
        flag=true;
    }

    if(!flag)
        qstr=qstr+"无\n";

    qstr=qstr+"\n\n";

//    transform.rotate(45); //旋转45度
//    painter.setWorldTransform(transform);
//    painter.drawEllipse(rectZoom);
//    painter.drawEllipse(rect);

//    transform.rotate(45); //旋转45度
//    painter.setWorldTransform(transform);
//    painter.drawEllipse(rectZoom);
//    painter.drawEllipse(rect);

//    transform.translate(-50 ,-50);//把中心点设置回默认的位置


    qstr=qstr+"可能认识的人(按关联度从高到低排序)：\n";
    mg->SetAssociateExtent(IdNum);
    int *Asso=mg->getAssociateExtent();

    int AssoPos[MAX_VERTEX_NUM];//记录位置
    for(int i=0;i<MAX_VERTEX_NUM;i++){
        AssoPos[i]=i;
    }


    for(int i=0;i<max-1;i++){
        for(int j=0;j<max-i-1;j++)
        {
            if (Asso[j] < Asso[j + 1])
            {
                AssoPos[j]=AssoPos[j]^AssoPos[j+1];
                AssoPos[j+1]=AssoPos[j]^AssoPos[j+1];
                AssoPos[j]=AssoPos[j]^AssoPos[j+1];

                Asso[j]=Asso[j]^Asso[j+1];
                Asso[j+1]=Asso[j]^Asso[j+1];
                Asso[j]=Asso[j]^Asso[j+1];
            }
        }
    }

    if(Asso[0]==-1)
        qstr=qstr+"无\n";
    else
    {
        for(int i=0;i<max;i++){
            if(Asso[i]!=-1){
                Person *tp=mg->getVexs(AssoPos[i]);

                qstr=qstr+tp->name+ ",  关联度： "+QString::number(Asso[i])+"\n";
            }
        }

    }


    ui->testBrowser->setText(qstr);

}


void PersonInforWindow::SetMGraph(MGraph *MG)
{
    mg=MG;
}
void PersonInforWindow::setIdNum(int idn)
{
    IdNum=idn;
}
