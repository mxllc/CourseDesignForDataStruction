#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->InConsole, SIGNAL(clicked()), this, SLOT(InConsoleSlot()));
    connect(&nw, &NetWork::returnMain, this, &MainWindow::NetWorkBackSlot);


    // 第一个菜单
    menuFile = menuBar()->addMenu(tr("File"));
    actExit = new QAction(tr("Exit"),this);  //初始化动作
    menuFile->addAction(actExit);  //将动作添加到菜单上
    //关联打开文件动作的信号和槽
    connect(actExit, SIGNAL(triggered()), this, SLOT(MenuFileExitActionSlot()));

    //第2个菜单
    menuSetFont = menuBar()->addMenu(tr("SetFont"));
    actFontBig = new QAction(tr("Large"),this);  //初始化动作
    actFontMiddle = new QAction(tr("Middle"),this);  //初始化动作
    actFontSmall = new QAction(tr("Small"),this);  //初始化动作
    menuSetFont->addAction(actFontBig);  //将动作添加到菜单上
    menuSetFont->addAction(actFontMiddle);  //将动作添加到菜单上
    menuSetFont->addAction(actFontSmall);  //将动作添加到菜单上
    //关联打开文件动作的信号和槽
    connect(actFontBig, SIGNAL(triggered()), this, SLOT(MenuSetFontBigActionSlot()));
    connect(actFontMiddle, SIGNAL(triggered()), this, SLOT(MenuSetFontMidActionSlot()));
    connect(actFontSmall, SIGNAL(triggered()), this, SLOT(MenuSetFontSmaActionSlot()));


    //用标签来输出文本
    questionLabel = ui->QuLabel;
    titleLabel = ui->TLabel;
    descripLabel = ui->DLabel;

    descripLabel->setText("性质描述：\n"
                          "在某社会关系网络系统中，一个人属性包括所在地区、就读的各级学校、工作单位等，每一个人有众多好友，并可以根据个人兴趣及社会活动加入到某些群组。"
                          "现需设计一个算法，从该社会关系网络中某一个人出发，寻找其可能认识的人。"
                          "例如根据两个人共同好友的数量及所在群组情况，来发现可能认识的人；"
                          "通过就读的学校情况发现可能认识的同学。");
    descripLabel->setWordWrap(1);//设置自动换行

    questionLabel->setText("问题描述：\n"
                           "(1)通过图形化界面，显示某一个人的社会关系网络\n"
                           "(2)寻找某一个人可能认识的人（不是其好友），并查看这些人与其关联度（共同好友数）\n"
                           "(3)根据可能认识的关联度对这些人进行排序");
    questionLabel->setWordWrap(1);//设置自动换行

    titleLabel->setText("欢迎使用社会关系网络构建程序");
    titleLabel->setWordWrap(1);//设置自动换行
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InConsoleSlot()
{
    this->hide();
    nw.setWindowTitle("演示界面");
    nw.show();

}

//关闭按钮提示
void MainWindow::closeEvent( QCloseEvent * event )
{
switch( QMessageBox::information( this, tr("exit tip"), tr("Do you really want exit?"), tr("Yes"), tr("No"), 0, 1 ) )
   {
     case 0:
          event->accept();
          break;
     case 1:
     default:
         event->ignore();
         break;
   }
}

//退出运用程序
void MainWindow::MenuFileExitActionSlot(){
    app->quit();
}

void MainWindow::MenuSetFontBigActionSlot()
{
    QFont font  = app->font();
    font.setPointSize(12);
    app->setFont(font);
}
void MainWindow::MenuSetFontMidActionSlot()
{
    QFont font  = app->font();
    font.setPointSize(10);
    app->setFont(font);
}
void MainWindow::MenuSetFontSmaActionSlot()
{
    QFont font  = app->font();
    font.setPointSize(8);
    app->setFont(font);
}

void MainWindow::NetWorkBackSlot()
{
    nw.hide();
    this->show();
}
