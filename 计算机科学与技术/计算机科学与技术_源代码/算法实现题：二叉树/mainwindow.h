#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QPainter>
#include <QInputDialog>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QCloseEvent>
#include <QLabel>
#include "btreewindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
//    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *event);

    //菜单栏
    QAction *actExit;  //定义Exit动作
    QMenu *menuFile;  //定义File菜单
    QMenu *menuSetFont;  //定义SetFont菜单
    QAction *actFontBig;  //定义FontBig动作
    QAction *actFontMiddle;  //定义FontMiddle动作
    QAction *actFontSmall;  //定义FontSmall动作

private:
    Ui::MainWindow *ui;
    BtreeWindow bw;
    QApplication* app;
    QLabel *questionLabel, *titleLabel, *descripLabel;


public slots:
    void EstablishSlot();
    void MenuFileExitActionSlot();
    void MenuSetFontBigActionSlot();
    void MenuSetFontMidActionSlot();
    void MenuSetFontSmaActionSlot();
    void BTreeBackSlot();


};

#endif // MAINWINDOW_H
