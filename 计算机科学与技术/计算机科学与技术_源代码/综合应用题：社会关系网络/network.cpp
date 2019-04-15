#include "network.h"
#include "ui_network.h"

NetWork::NetWork(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NetWork)
{
    ui->setupUi(this);
    //信号连接
    connect(ui->exit, SIGNAL(clicked()), this, SLOT(exitSlot()));
    connect(ui->back, SIGNAL(clicked()), this, SLOT(backSlot()));
    connect(ui->DeInfo, SIGNAL(clicked()), this, SLOT(DeInfoSlot()));

    connect(ui->tableOut, SIGNAL(clicked()), this, SLOT(tableOutSlot()));
    connect(ui->addNodeButton, SIGNAL(clicked()), this, SLOT(addNodeButtonSlot()));
    connect(&piw, &PersonInforWindow::returnNetwork, this, &NetWork::PersonInfoBackSlot);


}

NetWork::~NetWork()
{
    delete ui;
}

void NetWork::exitSlot()
{
    QApplication* app;
    app->quit();
}
void NetWork::backSlot()
{
//    bt.DestroyAllTree();
    emit returnMain();
}
void NetWork::tableOutSlot()
{
    QString qstr;
    qstr=qstr+"姓名：\n";
    qstr=qstr+mg.DisplayVextex()+"\n";
    qstr=qstr+"邻接矩阵：\n";
    qstr=qstr+mg.DisplayAdjMatrix()+"\n";
    qstr=qstr+"邻接表：\n";
    qstr=qstr+mg.DisplayAdjArc()+"\n";

    ui->testBrowser->setText(qstr);

}
void NetWork::addNodeButtonSlot()
{
    QRegistrationDialog dlg;
    dlg.exec();
    dlg.messageSet();
    dlg.hobbySet();
    dlg.friendSet();

    if(!dlg.Isvalid())
        return;


    if(mg.getVexnum()>=MAX_VERTEX_NUM){
        QString qstr="结点数目至多";
        qstr=qstr+QString::number(MAX_VERTEX_NUM)+"个！";
        QMessageBox::information(this, "Warning!",qstr);
        return;
    }

    QString **message;
    message=dlg.getQString();
    bool *hobbyMes=dlg.getHobbyMes();
    bool *friendListFromDlg=dlg.getFriendList();


    Elemtype p2=new Person {1, *(message[0]), *(message[1]),
                               *(message[2]), *(message[3]),
                               *(message[4]), *(message[5]),
                   {hobbyMes[0], hobbyMes[1], hobbyMes[2], hobbyMes[3], hobbyMes[4], hobbyMes[5], hobbyMes[6], hobbyMes[7]}};

//    Debug--------------------------------------
//    QString qqstr;
//    for(int i=0;i<8;++i){
//        if(hobbyMes[i])
//            qqstr=qqstr+"Y ";
//        else
//            qqstr=qqstr+"N ";
//    }
//    qqstr=qqstr+"\n ";
//    for(int i=0;i<10;++i){
//        if(friendListFromDlg[i])
//            qqstr=qqstr+"Y ";
//        else
//            qqstr=qqstr+"N ";
//    }

//    QMessageBox::information(this, "Warning!",qqstr);
//---------------------------------------------------


//    Elemtype p2=new Person {1,
//                   QString::fromStdString("王五"),
//                   QString::fromStdString("广州"),
//                   QString::fromStdString("人民小学"),
//                   QString::fromStdString("华夏中学"),
//                   QString::fromStdString("三峡大学"),
//                   QString::fromStdString("长城公司"),
//                   {false, true, true, false, false, false, true, true}};

    bool friendList[10]={friendListFromDlg[0], friendListFromDlg[1], friendListFromDlg[2], friendListFromDlg[3], friendListFromDlg[4],
                       friendListFromDlg[5], friendListFromDlg[6], friendListFromDlg[7], friendListFromDlg[8], friendListFromDlg[9]};

//    bool friendList[]={true, true, true, false, false, false, true, true};
    mg.addNode(p2,friendList);
    repaint();

}

void NetWork::PersonInfoBackSlot()
{
    piw.hide();
    this->show();
}

void NetWork::DeInfoSlot()
{
    QStringList NameItems;
    int vexnum=mg.getVexnum();
    for(int i=0;i<vexnum;i++){
        Person *p=mg.getVexs(i);
        NameItems.append(p->name+QString::number(p->ID));
    }


//    SexItems << tr("男") << tr("女")<< tr("中");



    bool ok;
    QString NameItem = QInputDialog::getItem(this,tr("标准条目选择对话框"),tr("请选择性别："),NameItems,0,false,&ok);

    if(ok&&!NameItem.isEmpty()){
        int idnum;
        NameItem=NameItem[NameItem.length()-1];
        idnum=NameItem.toInt();

        this->hide();
        piw.setIdNum(idnum);
        piw.SetMGraph(&mg);
        piw.setWindowTitle("个人信息");
        piw.show();
    }


}

void NetWork::paintEvent(QPaintEvent *)
{
    int MyRadius=50;

    QPainter painter(this);
    QPen pen; //画笔
    pen.setColor(QColor(0, 0, 0));
    QBrush brush(QColor(0, 255, 0, 125)); //画刷
    painter.setPen(pen); //添加画笔
    painter.setBrush(brush); //添加画刷

    int max=mg.getVexnum();
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


//        QRect rect(point[i].rx(), point[i].ry(), MyRadius, MyRadius);//构造一个矩形
        QRect rect(int(cx), int(cy), MyRadius, MyRadius);//构造一个矩形
        point[i]=rect.center();

        painter.drawEllipse(rect);
        angle+=delta;

    }



    for(int i=0;i<max-1;i++)
    {
        for(int j=1+i;j<max;j++){
            if(mg.isConnect(i,j)==1)
                painter.drawLine(point[i], point[j]);
        }
    }



    for(int i=0;i<max;i++)
    {
        Person *p=mg.getVexs(i);
        QString qstr=p->name+"_"+QString::number(p->ID);
        painter.drawText(point[i], qstr);
    }




}
