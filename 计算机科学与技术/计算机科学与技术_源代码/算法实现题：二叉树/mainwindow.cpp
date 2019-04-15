#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->establish, SIGNAL(clicked()), this, SLOT(EstablishSlot()));
    connect(&bw, &BtreeWindow::returnMain, this, &MainWindow::BTreeBackSlot);


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
                          "二叉树是n个结点的有限集合，它或为空树，或是由一个称之为根的结点加上两棵分别称为左子树和右子树的互不相交的二叉树组成。");
    descripLabel->setWordWrap(1);//设置自动换行

    questionLabel->setText("问题描述：\n"
                           "(1)建立一棵二叉树，完成先序、中序、后序遍历\n"
                           "(2)统计树中的叶子结点个数\n"
                           "(3)先序、中序、后序线索化\n"
                           "(4)先序、中序线索树的遍历\n"
                           "(5)显示原始树和线索化后的数");
    questionLabel->setWordWrap(1);//设置自动换行

    titleLabel->setText("欢迎使用二叉树构建程序");
    titleLabel->setWordWrap(1);//设置自动换行
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::paintEvent(QPaintEvent *)
//{
//    //设置字体
//    QFont font;
//    font.setPointSize(20);
//    font.setFamily("Microsoft YaHei");
//    font.setLetterSpacing(QFont::AbsoluteSpacing,0);
//    //设置Painter
//    QPainter painter(this);
//    painter.setFont(font);
//    painter.drawText(270, 100, "欢迎使用二叉树构建程序");
//    font.setPointSize(12);
//    painter.setFont(font);
//    painter.drawText(0, 200, "...");
//    painter.drawText(0, 250, ",.,.");
//}


void MainWindow::EstablishSlot()
{
    bool ok;
    QString MyString = QInputDialog::getText(this, "创建二叉树",
                         "输入先序序列，内部结点用一个字符表示，空结点用#表示:", QLineEdit::Normal,
                         "abc##d##ef###", &ok);
    if(ok){
        if(bw.TreeEst(MyString))
        {
            bw.Initial(MyString);
            this->hide();
            bw.setWindowTitle("操作界面");
            bw.show();
        }
        else{
            QMessageBox::information(this, "Warning!","输入不符合规范！\n"
                                                      "最多只可显示四层");
        }


    }

}

void MainWindow::BTreeBackSlot()
{
    bw.hide();
    this->show();
}

//退出运用程序
void MainWindow::MenuFileExitActionSlot(){
    app->quit();
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
