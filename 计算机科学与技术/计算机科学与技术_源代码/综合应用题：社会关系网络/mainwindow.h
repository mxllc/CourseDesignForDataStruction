#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QCloseEvent>
#include <QLabel>
#include <QMessageBox>
#include "network.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QApplication* app;
    NetWork nw;
    QLabel *questionLabel, *titleLabel, *descripLabel;
    void closeEvent(QCloseEvent *event);
    //菜单栏
    QAction *actExit;  //定义Exit动作
    QMenu *menuFile;  //定义File菜单
    QMenu *menuSetFont;  //定义SetFont菜单
    QAction *actFontBig;  //定义FontBig动作
    QAction *actFontMiddle;  //定义FontMiddle动作
    QAction *actFontSmall;  //定义FontSmall动作

public slots:
    void InConsoleSlot();
    void MenuFileExitActionSlot();
    void MenuSetFontBigActionSlot();
    void MenuSetFontMidActionSlot();
    void MenuSetFontSmaActionSlot();
    void NetWorkBackSlot();
};

#endif // MAINWINDOW_H
